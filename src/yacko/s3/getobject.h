#pragma once

#include <memory>
#include <map>
#include <httpd.h>
#undef OK
#undef HTTP_VERSION_NOT_SUPPORTED
#include "http_config.h"
#include "module_config_struct.h"
#include "yacko/serverexception.h"
#include "common.h"
#include "yacko/utils/stringutils.h"
#include <aws/s3/S3Client.h>
#include <aws/s3/model/GetObjectRequest.h>
#include <aws/core/auth/AWSCredentialsProvider.h>

extern "C" module AP_MODULE_DECLARE_DATA yacko_module;

namespace Yacko {
    namespace S3 {

        static const char* const ALLOCATION_TAG = "yacko";

        extern "C" {
            std::string getObject(request_rec *r, std::string bucket, std::string objectkey);

            std::shared_ptr<Aws::S3::S3Client> getS3Client(request_rec *r);
        }
    }
}

