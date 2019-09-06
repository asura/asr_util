#include "asr/util/Result.h"

namespace asr
{
namespace util
{
Result::Result(std::string&& the_error_message)
    : m_result(false)
    , m_error_message(the_error_message)
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
}  // namespace util
}  // namespace asr
