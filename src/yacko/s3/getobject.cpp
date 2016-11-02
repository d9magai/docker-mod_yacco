#include "getobject.h"

namespace Yacko {
    namespace S3 {

        std::string getObject(request_rec *r, std::string bucket, std::string objectkey)
        {

            Aws::S3::Model::GetObjectRequest getObjectRequest;
            getObjectRequest.SetBucket(bucket.c_str());
            getObjectRequest.SetKey(objectkey.c_str());

            auto getObjectOutcome = Yacko::S3::getS3Client(r)->GetObject(getObjectRequest);
            if (!getObjectOutcome.IsSuccess()) {
                std::string message = "File download failed from s3 with error: " + Yacko::Utils::as2s(getObjectOutcome.GetError().GetMessage());
                throw Yacko::internal_server_error(message);
            }

            return Yacko::Utils::buf2s(getObjectOutcome.GetResult().GetBody().rdbuf());
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
}

