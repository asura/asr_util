#ifndef ASR_UTIL_COUNTER_H
#define ASR_UTIL_COUNTER_H

#include <unordered_map>
#include <vector>

namespace asr
{
namespace util
{
/// 指定キーの発生回数をカウントするクラス
template <typename T, typename U = std::size_t>
class Counter
{
    std::unordered_map<T, U> m_counter;

public:
    /// 指定キーのカウントを1upする
    void add(const T& the_key)
    {
        auto p = m_counter.find(the_key);
        if (p == m_counter.end())
        {
            m_counter[the_key] = 1;
            return;
        }

        ++(p->second);
    }

    /// 指定キーのカウントをvalueぶん加算する
    void add(const T& the_key, const U& the_value)
    {
        auto p = m_counter.find(the_key);
        if (p == m_counter.end())
        {
            m_counter[the_key] = the_value;
            return;
        }

        p->second += the_value;
    }

    /// 指定キーのカウントを取得
    U operator[](const T& the_key) const
    {
        auto p = m_counter.find(the_key);
        return (p == m_counter.end()) ? 0 : p->second;
    }

    std::vector<T> keys() const
    {
        std::vector<T> result;
        result.reserve(m_counter.size());

        for (const auto& item : m_counter)
        {
            result.push_back(item.first);
        }

        return result;
    }
};
}  // namespace util
}  // namespace asr

#endif  // ASR_UTIL_COUNTER_H
