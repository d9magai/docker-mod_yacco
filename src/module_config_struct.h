/*
 * module_config_struct.h
 */

#ifndef MODULE_CONFIG_STRUCT_H_
#define MODULE_CONFIG_STRUCT_H_

#include <aws/s3/S3Client.h>
#include <aws/core/utils/StringUtils.h>

struct yacko_config
{
    std::shared_ptr<std::string> sha256secretkey;
    std::shared_ptr<Aws::String> aws_accesskey_id;
    std::shared_ptr<Aws::String> aws_secretaccess_key;
    std::shared_ptr<Aws::S3::S3Client> s3client;
};

#endif /* MODULE_CONFIG_STRUCT_H_ */
