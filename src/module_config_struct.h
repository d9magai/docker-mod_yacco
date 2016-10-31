/*
 * module_config_struct.h
 */

#ifndef MODULE_CONFIG_STRUCT_H_
#define MODULE_CONFIG_STRUCT_H_

struct yacco_config
{
    std::shared_ptr<std::string> sha256secretkey;
    std::shared_ptr<std::string> aws_accesskey_id;
    std::shared_ptr<std::string> aws_secretaccess_key;
};

#endif /* MODULE_CONFIG_STRUCT_H_ */
