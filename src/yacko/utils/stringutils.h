#pragma once

#include <sstream>
#include <map>
#include <iomanip>
#include <openssl/sha.h>
#include <aws/core/utils/StringUtils.h>
#include "common.h"

namespace Yacko {
    namespace Utils {

        std::string buf2s(std::basic_streambuf<char>* buf);
        std::string as2s(const Aws::String& as);
        std::map<std::string, std::string> parseUri(std::string uri);
        std::map<std::string, std::string> parseArgs(std::string args);
        std::string sha256(std::basic_string<unsigned char> str);
    }
}

