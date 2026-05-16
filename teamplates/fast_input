int rdint() {
    bool isneg = false;
    char c = getchar();
    while((c < '0' || c > '9')) {
        if(c == '-') {
            isneg = true;
        }
        c = getchar();
    }
    int a = 0;
    while(true) {
        a*=10;
        a+= c-'0';
        c = getchar();
        if(c < '0' || c > '9') break;
    }
    if(isneg) a *= -1;
    return a;
}
void prtint(int num) {
    if(num == 0) {
        putchar('0');
        putchar('\n');
        return;
    }
    if(num < 0) {
        num *= -1;
        putchar('-');
    }
    int val = 1000000000;
    while(num < val) {
        val /= 10;
    }
    while(val >= 1) {
        putchar('0' + (num / val) % 10);
        val /= 10;
    }
}
string rdstring() {
    string s;
    char c = getchar();
    while(isspace(c)) c = getchar();
    while(true) {
        s.push_back(c);
        if(isspace(c)) break;
        c = getchar();
    }
    return s;
}
void prtstr(string s) {
    for(char i : s) {
        putchar(i);
    }
}
