/*
 * module_config_struct.h
 */

#pragma once

#include <aws/s3/S3Client.h>
#include <aws/core/utils/StringUtils.h>

namespace Yacko {
    struct yacko_config
    {
        std::shared_ptr<std::string> sha256secretkey;
        std::shared_ptr<Aws::String> aws_accesskey_id;
        std::shared_ptr<Aws::String> aws_secretaccess_key;
        std::shared_ptr<Aws::S3::S3Client> s3client;
    };
}
