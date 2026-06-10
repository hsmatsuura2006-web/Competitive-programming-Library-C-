#include <iostream>
#include <vector>
#include <bit>

using namespace std;

class CoprimeCounter {
private:
    vector<int> min_prime;
    int max_val;

    // 前計算: エラトステネスの篩を用いて最小素因数テーブルを作成
    void build_sieve() {
        for (int i = 2; i <= max_val; ++i) {
            if (min_prime[i] == 0) {
                for (int j = i; j <= max_val; j += i) {
                    if (min_prime[j] == 0) min_prime[j] = i;
                }
            }
        }
    }

    // k を高速に素因数分解して異なる素因数のリストを返す
    vector<int> get_unique_primes(int k) const {
        vector<int> primes;
        while (k > 1) {
            int p = min_prime[k];
            primes.push_back(p);
            while (k % p == 0) k /= p;
        }
        return primes;
    }

public:
    // コンストラクタで最大値を指定（デフォルト 10^6）
    CoprimeCounter(int max_k = 1000000) : max_val(max_k) {
        min_prime.assign(max_val + 1, 0);
        build_sieve();
    }

    /**
     * n 以下の自然数のうち、k と互いに素なものの個数を計算する
     * @param n 範囲の上限 (10^18 まで対応)
     * @param k 対象となる数 (コンストラクタで指定した max_k まで)
     * @return 互いに素な個数
     */
    long long count(long long n, int k) const {
        if (k == 1) return n;
        if (k <= 0) return 0; // 定義外だが安全のため

        vector<int> primes = get_unique_primes(k);
        int m = primes.size();
        long long res = 0;

        // ビット全探索による包除原理
        for (int i = 0; i < (1 << m); ++i) {
            long long d = 1;
            for (int j = 0; j < m; ++j) {
                if ((i >> j) & 1) d *= primes[j];
            }

            // 選んだ素因数の数が奇数なら引き、偶数なら足す
            if (std::popcount(static_cast<unsigned int>(i)) % 2 == 1) {
                res -= n / d;
            } else {
                res += n / d;
            }
        }
        return res;
    }
};

int main() {
    // 1. クラスの初期化（前計算が走る）
    CoprimeCounter ct(1000000);

    // 2. 任意のクエリを投げる
    // 例: 100 以下の数で 30 と互いに素なものの個数
    // 30 = 2 * 3 * 5 なので、100 - (50+33+20) + (16+10+6) - 3 = 26
    cout << "n=100, k=30: " << ct.count(100, 30) << endl;

    // 大量のクエリ処理も高速
    int q;
    cout << "クエリ数を入力してください: ";
    if (cin >> q) {
        while (q--) {
            long long n;
            int k;
            cin >> n >> k;
            cout << ct.count(n, k) << "\n";
        }
    }

    return 0;
}
