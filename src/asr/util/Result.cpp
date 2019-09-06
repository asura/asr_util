#include "asr/util/Result.h"

#include <sstream>

namespace asr
{
namespace util
{
Result::Result(std::string&& the_error_message)
    : m_result(false)
    , m_error_message(the_error_message)
{
}

Result::Result(std::error_code&& the_error_code)
    : m_result(false)
    , m_error_message(convertErrorCodeToString(the_error_code))
{
}

bool Result::succeed() const
{
    return m_result;
}

const std::string& Result::errorMessage() const
{
    return m_error_message;
}

std::string Result::convertErrorCodeToString(const std::error_code& the_error_code)
{
    std::ostringstream oss;
    oss << "["
        << the_error_code.category().name()
        << "] "
        << the_error_code.message();
    return oss.str();
}
}  // namespace util
}  // namespace asr
