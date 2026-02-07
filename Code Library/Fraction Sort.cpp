#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    // std::pair<分子, 分母>
    std::vector<std::pair<long long, long long>> fractions = {
        {1, 3}, {2, 5}, {1, 2}, {2, 7}
    };

    // ソート用ラムダ式
    auto fractionComparator = [](const auto& a, const auto& b) {
        // a.first/a.second < b.first/b.second  <=>  a.first * b.second < b.first * a.second
        return a.first * b.second < b.first * a.second;
    };

    std::sort(fractions.begin(), fractions.end(), fractionComparator);

    // 結果表示
    for (const auto& f : fractions) {
        std::cout << f.first << "/" << f.second << " ";
    }
    return 0;
}
