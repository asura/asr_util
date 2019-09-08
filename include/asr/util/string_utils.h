#ifndef ASR_UTIL_STRING_UTILS_H
#define ASR_UTIL_STRING_UTILS_H

#include <string>
#include <vector>

namespace asr
{
namespace util
{
/// @brief vectorに格納された複数のstringを、指定デリミタで接続し、1つの文字列を生成する
/// @return 生成した文字列
/// @param [in] the_strings 対象文字列群
/// @param [in] the_delimiter 接続時に挿入するデリミタ文字
std::string join(const std::vector<std::string>& the_strings, const char the_delimiter);

/// @brief 指定文字列を指定デリミタで区切り、複数の文字列を生成する
/// @return 分解した文字列群
/// @param [in] the_string 対象文字列
/// @param [in] the_delimiter デリミタ文字
std::vector<std::string> split(const std::string& the_string, const char the_delimiter);
}  // namespace util
}  // namespace asr

#endif  // ASR_UTIL_STRING_UTILS_H
