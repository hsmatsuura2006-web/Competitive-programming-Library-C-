#include <iostream>
#include <concepts>
#include <functional>

/**
 * @brief 整数範囲に対する三分探索
 * @tparam T 整数の型 (int, long long など)
 * @tparam Func 評価関数の型
 * @tparam Compare 比較関数の型 (デフォルトは std::less = 谷型の最小値探索)
 * @param left 探索範囲の左端 (閉区間 [left, right])
 * @param right 探索範囲の右端
 * @param f 評価関数
 * @param comp 比較関数。comp(f(m1), f(m2)) が true のとき、m1 の方を「より最適ではない」と判断して範囲を狭める
 * @return 最適値を与える T 型のインデックス
 */
template <std::integral T, typename Func, typename Compare = std::less<>>
T ternary_search_integer(T left, T right, Func f, Compare comp = Compare{}) {
    while (right - left >= 3) {
        T m1 = left + (right - left) / 3;
        T m2 = right - (right - left) / 3;
        
        // comp(f(m1), f(m2)) が true ならば、m1 は m2 より「最適解から遠い」と判定
        if (comp(f(m1), f(m2))) {
            left = m1;  // 左側を切り捨てる
        } else {
            right = m2; // 右側を切り捨てる
        }
    }
    
    // 残った高々3要素の中から、最も最適なものを線形探索
    T best_x = left;
    auto best_val = f(left);
    for (T x = left + 1; x <= right; ++x) {
        auto val = f(x);
        // comp(best_val, val) が true ならば、val の方が「より最適」
        if (comp(best_val, val)) {
            best_val = val;
            best_x = x;
        }
    }
    
    return best_x;
}

int main() {
    // 例1: 谷型の関数 (x=42 で最小値をとる)
    // std::less を使うと f(m1) < f(m2) のときに left = m1 となり、最小値へ収束します
    auto valley_func = [](long long x) {
        return (x - 42) * (x - 42) + 10;
    };
    
    long long min_x = ternary_search_integer(0LL, 100LL, valley_func, std::less<>{});
    std::cout << "谷型の最小値をとるx: " << min_x << " (f(x) = " << valley_func(min_x) << ")\n";

    // 例2: 山型の関数 (x=73 で最大値をとる)
    // std::greater を使うと f(m1) > f(m2) のときに left = m1 となり、最大値へ収束します
    auto mountain_func = [](long long x) {
        return 100 - (x - 73) * (x - 73);
    };
    
    long long max_x = ternary_search_integer(0LL, 100LL, mountain_func, std::greater<>{});
    std::cout << "山型の最大値をとるx: " << max_x << " (f(x) = " << mountain_func(max_x) << ")\n";

    return 0;
}
