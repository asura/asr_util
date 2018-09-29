#define CATCH_CONFIG_RUNNER
#include <fmt/format.h>
#include <plog/Log.h>
#include <catch.hpp>

int main(int argc, char* argv[])
{
    plog::init(plog::info, "Tester.log");

    LOGI << "START";
    const int result = Catch::Session().run(argc, argv);

    LOGI << fmt::format("END({})", result);
    return (result < 0xff ? result : 0xff);
}
