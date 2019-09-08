#include "asr/util/Result2.h"

#include <catch2/catch.hpp>
#include <memory>  // unique_ptr

TEST_CASE("Result2::Result2(正常系)", "[small][asr::util::Result2]")
{
    WHEN("組込み型の場合")
    {
        asr::util::Result2<int> sut(-1);

        CHECK(sut.succeed() == true);
        CHECK(sut.value() == -1);
        CHECK(sut.errorMessage().empty());
    }

    WHEN("クラスの場合")
    {
        SECTION("constオブジェクトの場合")
        {
            const std::string s("FooBar");
            asr::util::Result2<std::string> sut(s);

            CHECK(sut.succeed() == true);
            CHECK(sut.value() == "FooBar");
            CHECK(sut.errorMessage().empty());
        }

        SECTION("一時オブジェクトの場合")
        {
            asr::util::Result2<std::string> sut(std::string("FooBar"));

            CHECK(sut.succeed() == true);
            CHECK(sut.value() == "FooBar");
            CHECK(sut.errorMessage().empty());
        }

        SECTION("非constオブジェクトの場合")
        {
            std::string s("FooBar");
            asr::util::Result2<std::string> sut(s);

            CHECK(sut.succeed() == true);
            CHECK(sut.value() == "FooBar");
            CHECK(sut.errorMessage().empty());
            CHECK(s == "FooBar");
        }

        SECTION("コピー不可クラスの場合、moveを明示的に使う必要あり")
        {
            using value_type = std::unique_ptr<std::string>;
            value_type s(new std::string{"FooBar"});
            asr::util::Result2<value_type> sut(std::move(s));

            CHECK(sut.succeed() == true);
            REQUIRE(sut.value());
            CHECK(*sut.value() == "FooBar");
            CHECK(sut.errorMessage().empty());
        }
    }
}

TEST_CASE("Result2::Result2(異常系)", "[small][util::Result2]")
{
    WHEN("組込み型の場合")
    {
        asr::util::Result2<int> sut(1, "異常発生");

        CHECK(sut.succeed() == false);
        CHECK(sut.value() == 1);
        CHECK(sut.errorMessage() == "異常発生");
    }

    WHEN("クラスの場合")
    {
        SECTION("コピー不可クラスの場合、moveを明示的に使う必要あり")
        {
            std::string s("FooBar");
            asr::util::Result2<std::string> sut(s, "異常発生");

            CHECK(sut.succeed() == false);
            CHECK(sut.value() == s);
            CHECK(sut.errorMessage() == "異常発生");
        }

        SECTION("コピー不可クラスの場合、moveを明示的に使う必要あり")
        {
            using value_type = std::unique_ptr<std::string>;
            value_type s;
            asr::util::Result2<value_type> sut(std::move(s), "異常発生");

            CHECK(sut.succeed() == false);
            CHECK(!sut.value());
            CHECK(sut.errorMessage() == "異常発生");
        }
    }
}

TEST_CASE("Result2::Result2(コピー)", "[small][util::Result2]")
{
    WHEN("正常系インスタンスのコピー")
    {
        asr::util::Result2<int> other(2);
        asr::util::Result2<int> sut(other);  // NOLINT(performance-unnecessary-copy-initialization)

        CHECK(sut.succeed() == true);
        CHECK(sut.value() == 2);
        CHECK(sut.errorMessage().empty());
    }

    WHEN("異常系インスタンスのコピー")
    {
        asr::util::Result2<int> other(3, "異常発生");
        asr::util::Result2<int> sut(other);  // NOLINT(performance-unnecessary-copy-initialization)

        CHECK(sut.succeed() == false);
        CHECK(sut.value() == 3);
        CHECK(sut.errorMessage() == other.errorMessage());
        CHECK(&sut.errorMessage() != &other.errorMessage());
    }
}
