#include "stringutils.h"

namespace Yacko {
    namespace Utils {

        std::string buf2s(std::basic_streambuf<char>* buf)
        {
            std::stringstream ss;
            ss << buf;
            return ss.str();
        }

        std::string as2s(const Aws::String& as)
        {
            std::stringstream ss;
            ss << as;
            return ss.str();
        }

        std::vector<std::string> pregUri(const std::string& uri)
        {
            regex_t preg;
            if (regcomp(&preg, Yacko::LOCATION_MATCH_REGEX.c_str(), REG_EXTENDED|REG_NEWLINE) != 0) {
                throw Yacko::INTERNAL_SERVER_ERROR("regex compile failed.");
            }

            const char *str = uri.c_str();
            size_t nmatch = 3;
            regmatch_t pmatch[3];
            if (regexec(&preg, str, nmatch, pmatch, 0) != 0) {
                throw Yacko::BAD_REQUEST("no match.");
            }

            std::vector<std::string> vec;
            for (size_t i = 0; i < nmatch; i++) {
                std::stringstream ss;
                if (pmatch[i].rm_so >= 0 && pmatch[i].rm_eo >= 0) {
                    for (int j = pmatch[i].rm_so; j < pmatch[i].rm_eo; j++) {
                        ss << str[j];
                    }
                }
                vec.push_back(ss.str());
            }
            regfree(&preg);

            return vec;
        }

        std::map<std::string, std::string> str2map(std::map<std::string, std::string> map, const std::string& str, const char delimiter)
        {

            std::stringstream source(str);
            std::string param, key, buf;
            while (std::getline(source, param, delimiter)) {
                std::stringstream paramss(param);
                std::getline(paramss, buf, '=');
                key = buf;
                std::getline(paramss, buf);
                map[key] = buf;
            }
            return map;
        }


        std::map<std::string, std::string> parseUri(std::string uri)
        {

            std::vector<std::string> vec = Yacko::Utils::pregUri(uri);
            std::string path = vec[2];
            int slashpos = path.find_first_of('/');
            std::map<std::string, std::string> map;
            map["bucket"] = path.substr(0, slashpos);
            map["objectkey"] = path.substr(slashpos + 1);
            if (vec[1] == "") {
                return map;
            }

            return Yacko::Utils::str2map(map, vec[1].substr(1, vec[1].length() - 2), ',');
        }

        std::map<std::string, std::string> parseArgs(std::string args)
        {

            std::map<std::string, std::string> map;
            return Yacko::Utils::str2map(map, args, '&');
        }

        std::string sha256(std::string str)
        {

            std::basic_stringstream<unsigned char> bss;
            bss << reinterpret_cast<const unsigned char*>(str.c_str());
            unsigned char hash[SHA256_DIGEST_LENGTH];
            SHA256(bss.str().c_str(), bss.str().length(), hash);
            std::stringstream ss;
            for (size_t i = 0; i < SHA256_DIGEST_LENGTH; i++) {
                ss << std::setfill('0') << std::setw(2) << std::hex << static_cast<int>(hash[i]);
            }
            return ss.str();
        }

        bool isEnabledImgType(const std::string &type)
        {

            return Yacko::Utils::enabledTypeSet.find(type) != Yacko::Utils::enabledTypeSet.end();
        }
    }
}
