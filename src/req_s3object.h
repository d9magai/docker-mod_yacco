#pragma once

#include <memory>
#include <httpd.h>
#undef OK
#undef HTTP_VERSION_NOT_SUPPORTED
#include "http_config.h"
#include "cached_s3client.h"
#include "module_config_struct.h"
#include "serverexception.h"
#include <aws/s3/S3Client.h>
#include <aws/s3/model/GetObjectRequest.h>
#include <aws/core/auth/AWSCredentialsProvider.h>

extern "C" module AP_MODULE_DECLARE_DATA yacko_module;

namespace Yacko {
extern "C" {
std::string getS3Object(request_rec *r, std::string uri);
}
}

