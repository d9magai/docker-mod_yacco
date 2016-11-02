#include "stringutils.h"

namespace Yacko {
    namespace Utils {

        std::string buf2s(const char *buf)
        {
            std::stringstream ss;
            ss << buf;
            return ss.str();
        }

        std::string buf2s(std::basic_streambuf<char>* buf)
        {
            std::stringstream ss;
            ss << buf;
            return ss.str();
        }

        Aws::String buf2as(const char *buf)
        {
            Aws::StringStream ass;
            ass << buf;
            return ass.str();
        }

        std::string as2s(const Aws::String& as)
        {
            std::stringstream ss;
            ss << as;
            return ss.str();
        }
    }
}

