#pragma once

namespace Yacko {

    const std::string HANDLER_NAME = "yacko";
    const std::string LOCATION_MATCH_REGEX = "^/" + Yacko::HANDLER_NAME + "(\\(.*?\\))?/(.*)";
    const int LOCATION_PARAMETERS_NUM = 1;
    const int S3_OBJECT_PATH_NUM = 2;
}

