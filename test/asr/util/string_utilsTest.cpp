#include "asr/util/string_utils.h"

#include <catch2/catch.hpp>
#include <sstream>

TEST_CASE(
    "asr::util::join",
    "[string_utils]")
{
    std::vector<std::string> doc;

    WHEN("結合元が空")
    {
        const std::string result = asr::util::join(doc, 'A');

        CHECK(result.empty());
    }

    WHEN("結合元が1件のみ")
    {
        doc.emplace_back("abcde");

        const std::string result = asr::util::join(doc, 'A');

        CHECK(result == "abcde");
    }

    WHEN("結合元が2件")
    {
        doc.emplace_back("abc");
        doc.emplace_back("def");

        AND_WHEN("結合文字が空文字")
        {
            const std::string result = asr::util::join(doc, 0x00);

            CHECK(result == "abcdef");
        }

        AND_WHEN("結合文字が非空文字")
        {
            const std::string result = asr::util::join(doc, ',');

            CHECK(result == "abc,def");
        }
    }

    WHEN("結合元が3件")
    {
        doc.emplace_back("abc");
        doc.emplace_back("def");
        doc.emplace_back("ghi");

        const std::string result = asr::util::join(doc, ',');

        CHECK(result == "abc,def,ghi");
    }
}

TEST_CASE(
    "asr::util::split",
    "[string_utils]")
{
    SECTION("空文字列")
    {
        const auto result = asr::util::split("", ',');

        REQUIRE(result.empty());
    }

    SECTION("指定されたデリミタ文字を含まない")
    {
        const auto result = asr::util::split("AaBb", ',');

        REQUIRE(result.size() == 1);
        CHECK(result[0] == "AaBb");
    }

    SECTION("指定されたデリミタ文字を1つ含む")
    {
        SECTION("デリミタ文字が先頭にある")
        {
            const auto result = asr::util::split(",aaa", ',');

            REQUIRE(result.size() == 2);
            CHECK(result[0].empty());
            CHECK(result[1] == "aaa");
        }

        SECTION("デリミタ文字が中間にある")
        {
            const auto result = asr::util::split("Aa,Bb", ',');

            REQUIRE(result.size() == 2);
            CHECK(result[0] == "Aa");
            CHECK(result[1] == "Bb");
        }

        SECTION("デリミタ文字が最後尾にある")
        {
            const auto result = asr::util::split("aaa,", ',');

            REQUIRE(result.size() == 2);
            CHECK(result[0] == "aaa");
            CHECK(result[1].empty());
        }
    }

    SECTION("指定されたデリミタ文字を2つ含む")
    {
        const auto result = asr::util::split("a,b,c", ',');

        REQUIRE(result.size() == 3);
        CHECK(result[0] == "a");
        CHECK(result[1] == "b");
        CHECK(result[2] == "c");
    }
}

std::vector<std::string>
splitByGetline(
    const std::string& the_string,
    const char the_delimiter)
{
    std::vector<std::string> result;

    if (the_string.empty())
    {
        return result;
    }

    std::stringstream iss(the_string);
    std::string line;

    while (std::getline(iss, line, the_delimiter))
    {
        result.emplace_back(line);
    }

    if (line.empty())
    {
        result.emplace_back("");
    }

    return result;
}

std::vector<std::string> splitByFindFirstOf(const std::string& the_string, char the_delimiter)
{
    std::vector<std::string> result;

    // 空文字列のケース
    if (the_string.empty())
    {
        return result;
    }

    std::size_t first = 0;
    std::size_t last;
    const std::size_t length = the_string.length();

    while (first < length + 1)
    {
        last = the_string.find_first_of(the_delimiter, first);
        if (last == std::string::npos)
        {
            last = length;
        }

        if (last == first)
        {
            result.emplace_back("");
        }
        else
        {
            result.emplace_back(std::string{the_string.data() + first, last - first});
        }

        first = last + 1;
    }

    return result;
}

std::vector<std::string> splitByFind(const std::string& the_str, char the_del)
{
    std::size_t first = 0;
    std::size_t last = the_str.find(the_del);

    std::vector<std::string> result;

    while (first < the_str.size())
    {
        std::string sub_str(the_str, first, last - first);

        result.push_back(sub_str);

        first = last + 1;
        last = the_str.find(the_del, first);

        if (last == std::string::npos)
        {
            last = the_str.size();
        }
    }

    return result;
}

std::vector<std::string> splitFor(std::string the_str, char the_del)
{
    std::vector<std::string> result;
    std::string sub_str;

    for (const char c : the_str)
    {
        if (c == the_del)
        {
            result.push_back(sub_str);
            sub_str.clear();
        }
        else
        {
            sub_str += c;
        }
    }

    result.push_back(sub_str);
    return result;
}

#ifdef CATCH_CONFIG_ENABLE_BENCHMARKING
TEST_CASE(
    "asr::util::splitの性能",
    "[string_utils]")
{
    const char delimiter = ',';

    SECTION("1文字ごとにデリミタ")
    {
        std::ostringstream oss;
        for (size_t i = 0; i < 10000; ++i)
        {
            if (i != 0)
            {
                oss << delimiter;
            }
            oss << "a";
        }
        const std::string target(oss.str());

        BENCHMARK("production")
        {
            const auto result = asr::util::split(target, delimiter);
        };
        BENCHMARK("getline")
        {
            const auto result = splitByGetline(target, delimiter);
        };
        BENCHMARK("find_first_of")
        {
            const auto result = splitByFindFirstOf(target, delimiter);
        };
        BENCHMARK("find")
        {
            const auto result = splitByFind(target, delimiter);
        };
        BENCHMARK("find_for")
        {
            const auto result = splitFor(target, delimiter);
        };
    }

    SECTION("100文字ごとにデリミタ")
    {
        std::ostringstream oss;
        for (size_t i = 0; i < 100; ++i)
        {
            if (i != 0)
            {
                oss << delimiter;
            }
            for (size_t j = 0; j < 100; ++j)
            {
                oss << "a";
            }
        }
        const std::string target(oss.str());

        BENCHMARK("production")
        {
            const auto result = asr::util::split(target, delimiter);
        };
        BENCHMARK("getline")
        {
            const auto result = splitByGetline(target, delimiter);
        };
        BENCHMARK("find_first_of")
        {
            const auto result = splitByFindFirstOf(target, delimiter);
        };
        BENCHMARK("find")
        {
            const auto result = splitByFind(target, delimiter);
        };
        BENCHMARK("find_for")
        {
            const auto result = splitFor(target, delimiter);
        };
    }
}
#endif
