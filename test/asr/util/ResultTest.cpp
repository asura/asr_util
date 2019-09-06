#include "asr/util/Result.h"

#include <catch2/catch.hpp>

TEST_CASE("Result::Result(正常系)", "[unit][asr::util::Result]")
{
    asr::util::Result sut;

    CHECK(sut.succeed() == true);
    CHECK(sut.error_message().empty());
}

TEST_CASE("Result::Result(異常系)", "[unit][asr::util::Result]")
{
    asr::util::Result sut("異常発生");

    CHECK(sut.succeed() == false);
    CHECK(sut.error_message() == "異常発生");
}

TEST_CASE("Result::Result(コピー)", "[unit][asr::util::Result]")
{
    WHEN("正常系インスタンスのコピー")
    {
        asr::util::Result other;
        asr::util::Result sut(other);

        CHECK(sut.succeed() == true);
        CHECK(sut.error_message().empty());
    }

    WHEN("異常系インスタンスのコピー")
    {
        asr::util::Result other("異常発生");
        asr::util::Result sut(other);

        CHECK(sut.succeed() == false);
        CHECK(sut.error_message() == other.error_message());
        CHECK(&sut.error_message() != &other.error_message());
    }
}
