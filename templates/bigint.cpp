string sum(string a, string b) {
    string ans;
    reverse(a.begin(),a.end());
    reverse(b.begin(), b.end());
    int carry = 0;
    for(int i = 0; i < max(a.size(), b.size()); i++) {
        int total = carry;
        if(i < a.size()) {
            total += a[i] - '0';
        }
        if(i < b.size()) {
            total += b[i] - '0';
        }
        ans += total % 10 + '0';
        carry = total / 10;
    }
    if(carry == 1) ans += '1';
    reverse(ans.begin(), ans.end());
    return ans;
}


string times(string a, string b) {
    string total;
    for(int i = 0; i < a.size(); i++) {
        string s = b;
        for(int j = 0; j < a.size() - i - 1; j++) {
            s += '0';
        }
        for(int j = 0; j < a[i] - '0'; j++) {
            total = sum(total, s);
        }
    }
    return total;
}
