#include <catch2/catch.hpp>
#include "asr/util/config.h"

TEST_CASE("asr::util::VERSION", "[asr::util]")
{
    CHECK(asr::util::kVersionMajor == 0);
    CHECK(asr::util::kVersionMinor == 1);
}
