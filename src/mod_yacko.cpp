#include <httpd/httpd.h>
#include "http_config.h"
#include <httpd/http_protocol.h>
#include <httpd/http_log.h>
#include "yacko/s3/getobject.h"
#include "yacko/mod_config.h"
#include "yacko/serverexception.h"
#include "yacko/common.h"
#include "yacko/utils/stringutils.h"
#include "yacko/image/convert.h"
#include <aws/core/Aws.h>
#include <ImageMagick/Magick++.h> 

extern "C" module AP_MODULE_DECLARE_DATA yacko_module;

#ifdef APLOG_USE_MODULE
APLOG_USE_MODULE(yacko);
#endif

/* 設定情報の生成・初期化(追加) */
static void *create_per_server_config(apr_pool_t *pool, server_rec *s)
{
    Yacko::mod_config *conf = reinterpret_cast<Yacko::mod_config*>(apr_pcalloc(pool, sizeof(Yacko::mod_config)));

    // default value
    conf->sha256secretkey = nullptr;
    conf->aws_accesskey_id = nullptr;
    conf->aws_secretaccess_key = nullptr;
    conf->s3client = nullptr;

    Aws::SDKOptions options;
    Aws::InitAPI(options);

    return conf;
}

/* The sample content handler */
static int yacko_handler(request_rec *r)
{
    if (strcmp(r->handler, Yacko::HANDLER_NAME.c_str())) {
        return DECLINED;
    }

    try {
        Yacko::mod_config *conf = reinterpret_cast<Yacko::mod_config*>(ap_get_module_config(r->server->module_config, &yacko_module));
        std::map<std::string, std::string> map = Yacko::Utils::parseUri(std::string(r->uri));
        std::map<std::string, std::string> params = Yacko::Utils::parseArgs(std::string(r->args));
        if (Yacko::Utils::sha256(std::string(r->uri) + *(conf->sha256secretkey)) != params["checksum"]) {
            throw Yacko::BAD_REQUEST("invalid checksum");
        }

        std::string data = Yacko::S3::getObject(r, map["bucket"], map["objectkey"]);
        Magick::Image image(Magick::Blob(data.c_str(), data.length())); 
        std::string basetype = image.magick();
        if (!Yacko::Utils::isEnabledImgType(basetype)) {
            throw Yacko::BAD_REQUEST("unenabled image type");
        }

        Magick::Blob blob = Yacko::Image::resize(map, image, basetype);

        apr_bucket *bucket = apr_bucket_pool_create(reinterpret_cast<const char*>(blob.data()), blob.length(), r->pool, r->connection->bucket_alloc);
        apr_bucket_brigade *bucket_brigate = apr_brigade_create(r->pool, r->connection->bucket_alloc);
        APR_BRIGADE_INSERT_TAIL(bucket_brigate, bucket);
        ap_set_content_type(r, Yacko::Utils::getMimetype(Yacko::Image::getOutputFormat(map, basetype)).c_str());
        ap_set_content_length(r, blob.length());
        ap_pass_brigade(r->output_filters, bucket_brigate);

    } catch (const Yacko::BAD_REQUEST& e) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, APLOG_MODULE_INDEX, r, e.what());
        return HTTP_BAD_REQUEST;
    } catch (const Yacko::INTERNAL_SERVER_ERROR& e) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, APLOG_MODULE_INDEX, r, e.what());
        return HTTP_INTERNAL_SERVER_ERROR;
    } catch (const std::exception& e) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, APLOG_MODULE_INDEX, r, e.what());
        return HTTP_INTERNAL_SERVER_ERROR;
    }

    return 0;//OK;
}

static void yacko_register_hooks(apr_pool_t *p)
{
    ap_hook_handler(yacko_handler, NULL, NULL, APR_HOOK_MIDDLE);
}

static const char *set_sha256secretkey(cmd_parms *parms, void *mconfig, const char *arg)
{
    if (strlen(arg) == 0) {
        return "sha256 secretket must be a string";
    }

    Yacko::mod_config *conf = reinterpret_cast<Yacko::mod_config*>(ap_get_module_config(parms->server->module_config, &yacko_module));
    conf->sha256secretkey = std::make_shared < std::string > (arg);
    return NULL;
}

static const char *set_aws_accesskey_id(cmd_parms *parms, void *mconfig, const char *arg)
{
    if (strlen(arg) == 0) {
        return "aws accesskey id must be a string";
    }

    Yacko::mod_config *conf = reinterpret_cast<Yacko::mod_config*>(ap_get_module_config(parms->server->module_config, &yacko_module));
    conf->aws_accesskey_id = std::make_shared < Aws::String > (Aws::String(arg));
    return NULL;
}

static const char *set_aws_secretaccess_key(cmd_parms *parms, void *mconfig, const char *arg)
{
    if (strlen(arg) == 0) {
        return "aws secretaccess ked must be a string";
    }

    Yacko::mod_config *conf = reinterpret_cast<Yacko::mod_config*>(ap_get_module_config(parms->server->module_config, &yacko_module));
    conf->aws_secretaccess_key = std::make_shared < Aws::String > (Aws::String(arg));
    return NULL;
}

/* 設定情報フック定義(追加) */
static const command_rec yacko_cmds[] =
    {
        {
        "SHA256_SECRET_KEY", set_sha256secretkey, 0, RSRC_CONF, TAKE1, "sha256 secretkey"
        },
        {
        "AWS_ACCESSKEY_ID", set_aws_accesskey_id, 0, RSRC_CONF, TAKE1, "aws accesskey id"
        },
        {
        "AWS_SECRETACCESS_KEY", set_aws_secretaccess_key, 0, RSRC_CONF, TAKE1, "aws secretaccess key"
        },
        {
        0
        },
    };

/* Dispatch list for API hooks */
module AP_MODULE_DECLARE_DATA yacko_module =
    {
    STANDARD20_MODULE_STUFF,
    NULL,                     /* create per-dir    config structures */
    NULL,                     /* merge  per-dir    config structures */
    create_per_server_config, /* create per-server config structures */
    NULL,                     /* merge  per-server config structures */
    yacko_cmds,               /* table of config file commands       */
    yacko_register_hooks      /* register hooks                      */
    };

