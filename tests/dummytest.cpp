#include <catch2/catch_all.hpp>

bool trueFunction(){
    return true;
}

TEST_CASE("Dummy test", "[dummy]") {
    REQUIRE(trueFunction());
}
