#include "util.h"

#include <catch2/catch_test_macros.hpp>

constexpr int kMaxUnicode = 0x10FFFF;

TEST_CASE("return length of a single UTF-8 source character",
          "[OneCharLenTest]") {
  REQUIRE(1 == string_util::OneCharLen("abc"));
  REQUIRE(3 == string_util::OneCharLen("テスト"));
}

TEST_CASE("Return the length of the UTF-8 character in bytes",
          "[UTF8LengthTest]") {}

TEST_CASE("decode UTF-8", "[DecodeUTF8Test]") {
  size_t mblen = 0;

  {
    const std::string input = "";
    REQUIRE(0 == string_util::DecodeUTF8(input, &mblen));
    REQUIRE(1 == mblen);  // mblen always returns >= 1
  }

  {
    REQUIRE(1 == string_util::DecodeUTF8("\x01", &mblen));
    REQUIRE(1 == mblen);
  }

  {
    REQUIRE(0x7F == string_util::DecodeUTF8("\x7F", &mblen));
    REQUIRE(1 == mblen);
  }

  {
    REQUIRE(0x80 == string_util::DecodeUTF8("\xC2\x80 ", &mblen));
    REQUIRE(2 == mblen);
  }

  {
    REQUIRE(0x7FF == string_util::DecodeUTF8("\xDF\xBF ", &mblen));
    REQUIRE(2 == mblen);
  }

  {
    REQUIRE(0x800 == string_util::DecodeUTF8("\xE0\xA0\x80 ", &mblen));
    REQUIRE(3 == mblen);
  }

  {
    REQUIRE(0x10000 == string_util::DecodeUTF8("\xF0\x90\x80\x80 ", &mblen));
    REQUIRE(4 == mblen);
  }

  // Invalid UTF8
  {
    REQUIRE(kUnicodeError ==
            string_util::DecodeUTF8("\xF7\xBF\xBF\xBF ", &mblen));
    REQUIRE(1 == mblen);
  }

  {
    REQUIRE(kUnicodeError ==
            string_util::DecodeUTF8("\xF8\x88\x80\x80\x80 ", &mblen));
    REQUIRE(1 == mblen);
  }

  {
    REQUIRE(kUnicodeError ==
            string_util::DecodeUTF8("\xFC\x84\x80\x80\x80\x80 ", &mblen));
    REQUIRE(1 == mblen);
  }

  {
    const char *kInvalidData[] = {
        "\xC2",      // must be 2byte.
        "\xE0\xE0",  // must be 3byte.
        "\xFF",      // BOM
        "\xFE"       // BOM
    };

    for (size_t i = 0; i < 4; ++i) {
      // return values of string_util::DecodeUTF8 is not defined.
      // TODO(taku) implement an workaround.
      REQUIRE(kUnicodeError ==
              string_util::DecodeUTF8(kInvalidData[i],
                                      kInvalidData[i] + strlen(kInvalidData[i]),
                                      &mblen));
      REQUIRE_FALSE(string_util::IsStructurallyValid(kInvalidData[i]));
      REQUIRE(1 == mblen);
    }
  }

  {
    REQUIRE(kUnicodeError == string_util::DecodeUTF8("\xDF\xDF ", &mblen));
    REQUIRE(1 == mblen);
  }

  {
    REQUIRE(kUnicodeError == string_util::DecodeUTF8("\xE0\xE0\xE0 ", &mblen));
    REQUIRE(1 == mblen);
  }

  {
    REQUIRE(kUnicodeError ==
            string_util::DecodeUTF8("\xF0\xF0\xF0\xFF ", &mblen));
    REQUIRE(1 == mblen);
  }
}

TEST_CASE("encode UTF-8", "[EncodeUTF8Test]") {
  char buf[16];
  for (char32 cp = 1; cp <= kMaxUnicode; ++cp) {
    if (!string_util::IsValidCodepoint(cp)) continue;
    const size_t mblen = string_util::EncodeUTF8(cp, buf);
    REQUIRE(mblen == string_util::UTF8Length(cp));
    size_t mblen2;
    const char32 c = string_util::DecodeUTF8(buf, buf + 16, &mblen2);
    REQUIRE(mblen2 == mblen);
    REQUIRE(cp == c);
  }

  // test case of codepoint = 0
  REQUIRE(1 == string_util::EncodeUTF8(0, buf));
  REQUIRE(1 == string_util::UTF8Length(0));
  REQUIRE('\0' == buf[0]);

  // non UCS4
  size_t mblen;
  REQUIRE(3 == string_util::EncodeUTF8(0x7000000, buf));
  REQUIRE(3 == string_util::UTF8Length(0x7000000));
  REQUIRE(kUnicodeError == string_util::DecodeUTF8(buf, buf + 16, &mblen));
  REQUIRE(3 == mblen);

  REQUIRE(3 == string_util::EncodeUTF8(0x8000001, buf));
  REQUIRE(3 == string_util::UTF8Length(0x8000001));
  REQUIRE(kUnicodeError == string_util::DecodeUTF8(buf, buf + 16, &mblen));
  REQUIRE(3 == mblen);
}
