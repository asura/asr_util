#define CATCH_CONFIG_RUNNER
#include <catch2/catch.hpp>

int main(int the_argc, char* the_argv[])
{
    const int result = Catch::Session().run(the_argc, the_argv);

    return (result < 0xff ? result : 0xff);
}
