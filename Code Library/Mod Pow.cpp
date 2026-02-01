long long mod_pow(long long a, long long b, long long n) {
    __int128_t res = 1;
    __int128_t base = a % n;
    while (b > 0) {
        if (b & 1) res = (res * base) % n;
        base = (base * base) % n;
        b >>= 1;
    }
    return (long long)res;
}
//逆元
long long mod_inv(long long n) {
    return mod_pow(n, MOD - 2);
}
