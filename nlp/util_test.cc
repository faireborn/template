#include "util.h"

#include <catch2/catch_test_macros.hpp>

TEST_CASE("return length of a single UTF-8 source character",
          "lenght of UTF-8") {
  REQUIRE(1 == string_util::OneCharLen("abc"));
  REQUIRE(3 == string_util::OneCharLen("テスト"));
}
