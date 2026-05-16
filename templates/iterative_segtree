const int MAXN = 500005;
int segtree[MAXN * 2];
int query(int left, int right){
    left += MAXN;
    right += MAXN;
    int total = 0;
    while(right > left) {
        if(left & 1) total += segtree[left++];
        if(right & 1) total += segtree[--right];
        left /= 2;
        right /= 2;
    }
    return total;
}
void update(int index, int val) {
    segtree[index + MAXN] = val;
    for(int i  = (index + MAXN) / 2; i > 0; i/=2) {
        // can replace this with any comparison
        segtree[i] = segtree[i * 2] + segtree[i * 2 + 1];
    }
}
