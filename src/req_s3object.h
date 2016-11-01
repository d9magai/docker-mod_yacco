#pragma once

#include <memory>
#include <map>
#include <httpd.h>
#undef OK
#undef HTTP_VERSION_NOT_SUPPORTED
#include "http_config.h"
#include "module_config_struct.h"
#include "serverexception.h"
#include "common.h"
#include <aws/s3/S3Client.h>
#include <aws/s3/model/GetObjectRequest.h>
#include <aws/core/auth/AWSCredentialsProvider.h>

extern "C" module AP_MODULE_DECLARE_DATA yacko_module;

namespace Yacko {

    static const char* const ALLOCATION_TAG = "yacko";

    extern "C" {
        std::string getS3Object(request_rec *r);

        std::shared_ptr<Aws::S3::S3Client> getS3Client(request_rec *r);

        std::map<std::string, std::string> parseUri(std::string uri);
    }
}

