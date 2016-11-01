#include "req_s3object.h"

namespace Yacko {

    std::string getS3Object(request_rec *r)
    {
        std::string uri(r->uri);
        std::string path = std::string(uri).substr(Yacko::HANDLER_NAME.length() + 2);
        int slashpos = path.find_first_of('/');
        std::string bucket = path.substr(0, slashpos);
        std::string objectkey = path.substr(slashpos + 1);

        std::shared_ptr < Aws::S3::S3Client > s3client = Yacko::getS3Client(r);
        Aws::S3::Model::GetObjectRequest getObjectRequest;
        getObjectRequest.SetBucket(bucket.c_str());
        getObjectRequest.SetKey(objectkey.c_str());

        auto getObjectOutcome = s3client->GetObject(getObjectRequest);
        if (!getObjectOutcome.IsSuccess()) {
            std::stringstream ss;
            ss << "File download failed from s3 with error " << getObjectOutcome.GetError().GetMessage();
            throw Yacko::internal_server_error(ss.str());
        }

        std::stringstream ss;
        ss << getObjectOutcome.GetResult().GetBody().rdbuf();
        return ss.str();
    }

    std::shared_ptr<Aws::S3::S3Client> getS3Client(request_rec *r)
    {

        yacko_config *conf = reinterpret_cast<yacko_config*>(ap_get_module_config(r->server->module_config, &yacko_module));
        if (conf->s3client) {
            return conf->s3client;
        }

        Aws::Client::ClientConfiguration config;
        config.scheme = Aws::Http::Scheme::HTTPS;
        config.connectTimeoutMs = 30000;
        config.requestTimeoutMs = 30000;
        config.region = Aws::Region::AP_NORTHEAST_1;

        conf->s3client = Aws::MakeShared < Aws::S3::S3Client > (ALLOCATION_TAG, Aws::Auth::AWSCredentials(*(conf->aws_accesskey_id), *(conf->aws_secretaccess_key)), config);
        if (!(conf->s3client)) {
            throw Yacko::internal_server_error("init S3Client failed");
        }
        return conf->s3client;
    }
}
