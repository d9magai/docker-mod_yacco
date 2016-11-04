#pragma once

#include <sstream>
#include <map>
#include <aws/core/utils/StringUtils.h>
#include "common.h"

namespace Yacko {
    namespace Utils {

        std::string buf2s(std::basic_streambuf<char>* buf);
        Aws::String buf2as(const char *buf);
        std::string as2s(const Aws::String& as);
        std::map<std::string, std::string> parseUri(std::string uri);
        std::map<std::string, std::string> parseArgs(std::string args);
    }
}

