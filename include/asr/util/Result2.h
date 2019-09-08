#ifndef ASR_UTIL_RESULT2_H
#define ASR_UTIL_RESULT2_H

#include <string>
#include <system_error>

namespace asr
{
namespace util
{
/// @brief 正常か異常か、正常のときは何らかの値を、異常のときはエラーメッセージを、それぞれ取得できるクラス。
/// @note Tとして std::unique_ptr のようにコピー不可なクラスを用いる場合、構築時に std::move により右辺値を作り、右辺値用コンストラクタを使う必要がある。
template <typename T>
class Result2
{
    bool m_result{true};          ///< 成功 or 失敗
    T m_value;                    ///< 成功時の返却値
    std::string m_error_message;  ///< 失敗時の何らかのメッセージ

public:
    Result2() = delete;

    /// 正常時に使うコンストラクタ(左辺値用)
    explicit Result2(const T& the_value)  // NOLINT(modernize-pass-by-value)
        : m_value(the_value)
    {
    }

    /// 正常時に使うコンストラクタ(右辺値用)
    explicit Result2(T&& the_value)
        : m_value(std::move(the_value))
    {
    }

    /// 異常時に使うコンストラクタ(左辺値用)
    explicit Result2(const T& the_value, const std::string& the_error_message)  // NOLINT(modernize-pass-by-value)
        : m_result(false)
        , m_value(the_value)
        , m_error_message(the_error_message)
    {
    }

    /// 異常時に使うコンストラクタ(右辺値用)
    explicit Result2(T&& the_value, const std::string& the_error_message)  // NOLINT(modernize-pass-by-value)
        : m_result(false)
        , m_value(std::move(the_value))
        , m_error_message(the_error_message)
    {
    }

    /// 成功ならtrue, 失敗ならfalse
    bool succeed() const
    {
        return m_result;
    }

    /// 値を返す
    const T& value() const
    {
        return m_value;
    }

    /// エラーメッセージを返す
    const std::string& errorMessage() const
    {
        return m_error_message;
    }
};
}  // namespace util
}  // namespace asr

#endif  // ASR_UTIL_RESULT2_H
