#include "asr/util/Result.h"

namespace asr
{
namespace util
{
Result::Result()
    : m_result(true)
{
}

Result::Result(const std::string& error_message)
    : m_result(false)
    , m_error_message(error_message)
{
}

bool Result::succeed() const
{
    return m_result;
}

const std::string& Result::error_message() const
{
    return m_error_message;
}
}  // namespace util
}  // namespace asr
