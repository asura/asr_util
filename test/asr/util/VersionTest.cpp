#include "asr/util/config.h"

#include <catch2/catch.hpp>

TEST_CASE("asr::util::VERSION", "[asr::util]")
{
    CHECK(asr::util::kVersionMajor == 0);
    CHECK(asr::util::kVersionMinor == 1);
}
