#ifndef ASR_UTIL_RESULT_H
#define ASR_UTIL_RESULT_H

#include <string>
#include <system_error>

namespace asr
{
namespace util
{
/// <summary>
/// 正常か異常か、異常のときはエラーメッセージを取得できるクラス。
/// </summary>
/// std::optional<std::string>とは意味的に逆。
/// (上記だと「エラーメッセージは有効か」という聞き方になってしまう)
/// expected<bool, std::string>と近い。
class Result
{
    bool m_result{true};          ///< 成功 or 失敗
    std::string m_error_message;  ///< 失敗時の何らかのメッセージ

public:
    /// 正常時に使うコンストラクタ
    Result() = default;

    /// 異常時に使うコンストラクタ
    explicit Result(std::string&& the_error_message);

    /// 異常時に使うコンストラクタ
    explicit Result(std::error_code&& the_error_code);

    /// 成功ならtrue, 失敗ならfalse
    bool succeed() const;

    /// エラーメッセージを返す
    const std::string& errorMessage() const;

private:
    static std::string convertErrorCodeToString(const std::error_code& the_error_code);
};
}  // namespace util
}  // namespace asr

#endif  // ASR_UTIL_RESULT_H
