#include "yacko/utils/stringutils.h"
#include "Catch/include/catch.hpp"

TEST_CASE("pregUri Test", "[utils][stringutils]") {

    std::vector<std::string> vec = Yacko::Utils::pregUri(std::string("/yacko(w=100,h=200)/bucket/path/to/object"));
    CHECK(vec[0] == "/yacko(w=100,h=200)/bucket/path/to/object");
    CHECK(vec[1] == "(w=100,h=200)");
    CHECK(vec[2] == "bucket/path/to/object");
    vec = Yacko::Utils::pregUri(std::string("/yacko()/bucket/path/to/object"));
    CHECK(vec[0] == "/yacko()/bucket/path/to/object");
    CHECK(vec[1] == "()");
    CHECK(vec[2] == "bucket/path/to/object");
    vec = Yacko::Utils::pregUri(std::string("/yacko/bucket/path/to/object"));
    CHECK(vec[0] == "/yacko/bucket/path/to/object");
    CHECK(vec[1] == "");
    CHECK(vec[2] == "bucket/path/to/object");
}

TEST_CASE("parseUri Test", "[utils][stringutils]") {

    std::map<std::string, std::string> map = Yacko::Utils::parseUri(std::string("/yacko/bucket/path/to/object"));
    REQUIRE(map["bucket"] == "bucket");
    REQUIRE(map["objectkey"] == "path/to/object");
}

TEST_CASE("parseArgs Test", "[utils][stringutils]") {

    std::map<std::string, std::string> map = Yacko::Utils::parseArgs(std::string("a=b&cde=fgh&i=123"));
    CHECK(map["a"] == "b");
    CHECK(map["cde"] == "fgh");
    CHECK(map["i"] == "123");
}

TEST_CASE("buf2s Test", "[utils][stringutils]") {

    std::stringstream ss("hoge");
    CHECK("hoge" == Yacko::Utils::buf2s(ss.rdbuf()));
}

TEST_CASE("as2s Test", "[utils][stringutils]") {

    Aws::String as("hoge");
    std::string s("hoge");
    CHECK(s == Yacko::Utils::as2s(as));
}

TEST_CASE("sha256 Test", "[utils][stringutils]") {

    std::string str = "The quick brown fox jumps over the lazy dog";
    CHECK("d7a8fbb307d7809469ca9abcb0082e4f8d5651e46d3cdb762d02d0bf37c9e592" == Yacko::Utils::sha256(str));
}

TEST_CASE("isEnabledImgType Test", "[utils][stringutils]") {

    CHECK(Yacko::Utils::isEnabledImgType("JPEG"));
    CHECK(Yacko::Utils::isEnabledImgType("GIF"));
    CHECK(Yacko::Utils::isEnabledImgType("PNG"));
    CHECK(Yacko::Utils::isEnabledImgType("BMP"));
    CHECK(!Yacko::Utils::isEnabledImgType("TIF"));
    CHECK(!Yacko::Utils::isEnabledImgType("SVG"));
}
