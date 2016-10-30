#include <sstream>
#include <memory>
#include <httpd.h>
#include "http_config.h"
#include <http_protocol.h>
#include <ap_config.h>
#include "module_config_struct.h"

extern "C" module AP_MODULE_DECLARE_DATA yacco_module;

/* 設定情報の生成・初期化(追加) */
static void *create_per_server_config(apr_pool_t *pool, server_rec *s)
{
    yacco_config *cfg = reinterpret_cast<yacco_config*>(apr_pcalloc(pool, sizeof(yacco_config)));

    // default value
    cfg->sha256secretkey = nullptr;
    return cfg;
}

/* The sample content handler */
static int yacco_handler(request_rec *r)
{
    if (strcmp(r->handler, "yacco")) {
        return DECLINED;
    }
    r->content_type = "text/html";

    yacco_config *conf = reinterpret_cast<yacco_config*>(ap_get_module_config(r->server->module_config, &yacco_module));
    if (!r->header_only)
        ap_rputs(conf->sha256secretkey->c_str(), r);

    return OK;
}

static void yacco_register_hooks(apr_pool_t *p)
{
    ap_hook_handler(yacco_handler, NULL, NULL, APR_HOOK_MIDDLE);
}

static const char *set_sha256secretkey(cmd_parms *parms, void *mconfig, const char *arg)
{
    if (strlen(arg) == 0) {
        return "sha256 secretket must be a string";
    }

    yacco_config *cfg = reinterpret_cast<yacco_config*>(ap_get_module_config(parms->server->module_config, &yacco_module));
    cfg->sha256secretkey = std::make_shared < std::string > (arg);
    return NULL;
}

/* 設定情報フック定義(追加) */
static const command_rec yacco_cmds[] =
    {
        {
        "SHA256_SECRET_KEY", set_sha256secretkey, 0, RSRC_CONF, TAKE1, "sha256 secretkey"
        },
        {
        0
        },
    };

/* Dispatch list for API hooks */
module AP_MODULE_DECLARE_DATA yacco_module =
    {
    STANDARD20_MODULE_STUFF,
    NULL,                     /* create per-dir    config structures */
    NULL,                     /* merge  per-dir    config structures */
    create_per_server_config, /* create per-server config structures */
    NULL,                     /* merge  per-server config structures */
    yacco_cmds,               /* table of config file commands       */
    yacco_register_hooks      /* register hooks                      */
    };

