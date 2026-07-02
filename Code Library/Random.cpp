#include <iostream>
#include <chrono>
#include <random>
#include <numeric>
#include <vector>
#include <algorithm>

// ==================== RANDOM TEMPLATE ====================
struct Random {
    std::mt19937_64 rng;
    
    // 実行ごとにシードを変える（ハッキング・Anti-Testcase 対策）
    Random() {
        long long seed = std::chrono::steady_clock::now().time_since_epoch().count();
        // ローカルデバッグ用に固定シードにしたい場合は下を有効化
        // seed = 42; 
        rng.seed(seed);
    }

    // [l, r] の閉区間から整数を一様ランダムに抽出
    long long randint(long long l, long long r) {
        std::uniform_int_distribution<long long> dist(l, r);
        return dist(rng);
    }

    // [l, r) の半開区間から実数を一様ランダムに抽出
    double randdouble(double l, double r) {
        std::uniform_real_distribution<double> dist(l, r);
        return dist(rng);
    }

    // コンテナ（vectorなど）をランダムにシャッフル
    template<typename T>
    void shuffle(std::vector<T>& v) {
        std::shuffle(v.begin(), v.end(), rng);
    }
} rng;
// ==============================================================

int main() {
    // 1. 範囲内のランダムな整数
    std::cout << "Dice (1-6): " << rng.randint(1, 6) << "\n";

    // 2. 配列のシャッフル（乱択アルゴリズムの前処理に必須）
    std::vector<int> a(10);
    std::iota(a.begin(), a.end(), 1); // 1から10を詰める
    rng.shuffle(a);
    
    std::cout << "Shuffled: ";
    for(int x : a) std::cout << x << " ";
    std::cout << "\n";

    return 0;
}
