#pragma once

#include <string>
#include <memory>
#include <exception>

namespace Yacko {

class BAD_REQUEST: public std::runtime_error {
public:
    explicit BAD_REQUEST(const std::string& s) :
            std::runtime_error(s) {
    }
};

class INTERNAL_SERVER_ERROR: public std::runtime_error {
public:
    explicit INTERNAL_SERVER_ERROR(const std::string& s) :
            std::runtime_error(s) {
    }
};

}

