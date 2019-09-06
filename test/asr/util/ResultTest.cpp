#include "asr/util/Result.h"

#include <catch2/catch.hpp>

TEST_CASE("Result::Result(正常系)", "[unit][asr::util::Result]")
{
    asr::util::Result sut;

    CHECK(sut.succeed() == true);
    CHECK(sut.errorMessage().empty());
}

TEST_CASE("Result::Result(異常系)", "[unit][asr::util::Result]")
{
    asr::util::Result sut("異常発生");

    CHECK(sut.succeed() == false);
    CHECK(sut.errorMessage() == "異常発生");
}

TEST_CASE("Result::Result(異常系・error_code版)", "[unit][asr::util::Result]")
{
    asr::util::Result sut(std::make_error_code(std::errc::invalid_argument));

    CHECK(sut.succeed() == false);
    CHECK(sut.errorMessage() == "[generic] Invalid argument");
}

TEST_CASE("Result::Result(コピー)", "[unit][asr::util::Result]")
{
    WHEN("正常系インスタンスのコピー")
    {
        asr::util::Result other;
        asr::util::Result sut(other);  // NOLINT(performance-unnecessary-copy-initialization)

        CHECK(sut.succeed() == true);
        CHECK(sut.errorMessage().empty());
    }

    WHEN("異常系インスタンスのコピー")
    {
        asr::util::Result other("異常発生");
        asr::util::Result sut(other);  // NOLINT(performance-unnecessary-copy-initialization

        CHECK(sut.succeed() == false);
        CHECK(sut.errorMessage() == other.errorMessage());
        CHECK(&sut.errorMessage() != &other.errorMessage());
    }
}
