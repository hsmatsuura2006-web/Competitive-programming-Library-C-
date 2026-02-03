vector<ll> optimizedSieve(const ll n) {
    vector<bool> prime(n + 1, true);
    prime[0] = prime[1] = false;
    for (ll p = 2; p * p <= n; p++) {
        if (prime[p]) {
            for (ll i = p * p; i <= n; i += p)
                prime[i] = false;
        }
    }
    vector<ll> res;
    for (int p = 2; p <= n; p++) {
        if (prime[p]) {
            res.push_back(p);
        }
    }
    return res;
}
