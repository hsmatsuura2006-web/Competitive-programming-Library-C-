//文字列　to 数値
string t;
for (char c : t) {
        ans = (ans << 1) | (c - '0');
    }

//数値 to 文字列
string t = "";
  ll temp_x = x;
    while (temp_x > 0) {
        t += static_cast<char>('0' + (temp_x % 2));
        temp_x /= 2;
    }
