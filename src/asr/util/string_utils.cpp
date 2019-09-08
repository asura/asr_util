#include "asr/util/string_utils.h"

#include <sstream>

namespace asr
{
namespace util
{
std::string
join(
    const std::vector<std::string>& the_strings,
    const char the_delimiter)
{
    if (the_strings.empty())
    {
        return "";
    }

    std::size_t whole_length = 0;
    for (auto p = the_strings.cbegin(),
              q = the_strings.cend();
         p != q;
         ++p)
    {
        if (p != the_strings.begin())
        {
            ++whole_length;
        }
        whole_length += p->length() + sizeof(the_delimiter);
    }

    std::string result;
    result.reserve(whole_length);
    for (auto p = the_strings.cbegin(),
              q = the_strings.cend();
         p != q;
         ++p)
    {
        if ((the_delimiter != 0x00) && (p != the_strings.cbegin()))
        {
            result += the_delimiter;
        }
        result += *p;
    }
    return result;
}

std::vector<std::string>
split(
    const std::string& the_string,
    const char the_delimiter)
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

}  // namespace util
}  // namespace asr
