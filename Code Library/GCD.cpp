lll gcd_lll(lll a, lll b) {
    while (b != 0) {
        lll t = b;
        b = a % b;
        a = t;
    }
    return a;
}
