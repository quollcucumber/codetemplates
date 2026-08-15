int MOD = 1e9 + 7;
bool seen[1005][1005];
int cached[1005][1005];
int choose(int a, int b) {
    if(a == b) return 1;
    if(a == 0) return 1;
    if(b == 0) return 1;
    if(seen[a][b]) return cached[a][b];
    seen[a][b] = true;
    return cached[a][b] = (choose(a-1, b-1) + choose(a-1, b)) % MOD;
}
