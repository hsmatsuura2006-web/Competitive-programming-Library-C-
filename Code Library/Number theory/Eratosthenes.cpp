#include <iostream>
#include <vector>
using namespace std;

// エラトステネスの篩
struct Eratosthenes {
    vector<bool> isprime;
    vector<int> minfactor;
    Eratosthenes(int N) : isprime(N+1, true),
                          minfactor(N+1, -1) {
        isprime[1] = false;
        minfactor[1] = 1;

        for (int p = 2; p <= N; ++p) {
            if (!isprime[p]) continue;
            minfactor[p] = p;
            for (int q = p * 2; q <= N; q += p) {
                isprime[q] = false;
                if (minfactor[q] == -1) minfactor[q] = p;
            }
        }
    }
    vector<pair<int,int>> factorize(int n) {
        vector<pair<int,int>> res;
        while (n > 1) {
            int p = minfactor[n];
            int exp = 0;
            while (minfactor[n] == p) {
                n /= p;
                ++exp;
            }
            res.emplace_back(p, exp);
        }
        return res;
    }  
};

int main() {
    // エラトステネスの篩
    Eratosthenes er(50);

    // 結果表示
    for (int n = 2; n <= 50; ++n) {
        auto pf = er.factorize(n);
        cout << n << ": ";
        for (int i = 0; i < pf.size(); ++i) {
            if (i > 0) cout << " * ";
            cout << pf[i].first << "^" << pf[i].second;
        }
        cout << endl;
    }
}
