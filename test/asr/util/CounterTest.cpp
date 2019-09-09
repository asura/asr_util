#include "asr/util/Counter.h"

#include <catch2/catch.hpp>

TEST_CASE("util::Counterの利用(整数値、1up)", "[small][util::Counter]")
{
    asr::util::Counter<int> sut;

    WHEN("存在しないキーを指定")
    {
        REQUIRE(sut.keys().empty());

        auto result = sut[1];

        CHECK(result == 0);

        REQUIRE(sut.keys().empty());
    }

    WHEN("存在するキーを指定")
    {
        sut.add(2);
        REQUIRE(sut.keys().size() == 1);

        auto result = sut[2];

        CHECK(result == 1);

        AND_THEN("既存キーを追加カウント")
        {
            sut.add(2);
            REQUIRE(sut.keys().size() == 1);

            auto result = sut[2];

            CHECK(result == 2);
        }
    }
}

TEST_CASE("util::Counterの利用(実数)", "[small][util::Counter]")
{
    asr::util::Counter<int, double> sut;

    WHEN("存在しないキーを指定")
    {
        REQUIRE(sut.keys().empty());

        auto result = sut[1];

        CHECK(result == 0.0);

        REQUIRE(sut.keys().empty());
    }

    WHEN("存在するキーを指定")
    {
        sut.add(2, 0.5);
        REQUIRE(sut.keys().size() == 1);

        auto result = sut[2];

        CHECK(result == 0.5);

        AND_THEN("既存キーを追加カウント")
        {
            sut.add(2, 1.8);
            REQUIRE(sut.keys().size() == 1);

            auto result = sut[2];

            CHECK(result == 2.3);
        }
    }
}
