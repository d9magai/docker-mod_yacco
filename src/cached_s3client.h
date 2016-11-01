#pragma once

#include <memory>
#include <httpd.h>
#undef OK
#undef HTTP_VERSION_NOT_SUPPORTED
#include "http_config.h"
#include "module_config_struct.h"
#include "serverexception.h"
#include <aws/s3/S3Client.h>
#include <aws/core/auth/AWSCredentialsProvider.h>

extern "C" module AP_MODULE_DECLARE_DATA yacko_module;

static const char* ALLOCATION_TAG = "yacko";

namespace Yacko {
extern "C" {
std::shared_ptr<Aws::S3::S3Client> getS3Client(request_rec *r);
}
}

