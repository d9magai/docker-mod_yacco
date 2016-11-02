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

        std::map<std::string, std::string> parseUri(std::string uri)
        {

            std::string path = std::string(uri).substr(Yacko::HANDLER_NAME.length() + 2);
            int slashpos = path.find_first_of('/');
            std::map<std::string, std::string> map;
            map["bucket"] = path.substr(0, slashpos);
            map["objectkey"] = path.substr(slashpos + 1);

            return map;
        }
    }
}

