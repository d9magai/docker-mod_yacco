#pragma once

#include <sstream>
#include <map>
#include <set>
#include <algorithm>
#include <iomanip>
#include <openssl/sha.h>
#include <aws/core/utils/StringUtils.h>
#include <regex.h>
#include "yacko/common.h"
#include "yacko/serverexception.h"

namespace Yacko {
    namespace Utils {

        const std::set<std::string> enabledTypeSet
            {
            "JPEG",
            "GIF",
            "PNG",
            "BMP"
            };

        std::string buf2s(std::basic_streambuf<char>* buf);
        std::string as2s(const Aws::String& as);
        std::vector<std::string> pregUri(const std::string& uri);
        std::map<std::string, std::string> parseUri(std::string uri);
        std::map<std::string, std::string> parseArgs(std::string args);
        std::string sha256(std::string str);
        bool isEnabledImgType(const std::string &type);
    }
}

