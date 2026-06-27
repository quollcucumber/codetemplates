struct node {
    int lazyadd;
    int total;
};
 
const int MAXN = 100005;
node tree[MAXN * 4];
 
void prop(int node, int l, int r) {
    if(l + 1 != r) {
        tree[node * 2].lazyadd += tree[node].lazyadd;
        tree[node * 2 + 1].lazyadd += tree[node].lazyadd;
    }
    tree[node].total += (r-l) * tree[node].lazyadd;
    tree[node].lazyadd = 0;
}
void upd(int left, int right, int val, int pos = 1, int l = 0, int r = MAXN) {
    prop(pos,l,r);
    if(left <= l && right >= r) {
        tree[pos].lazyadd += val;
        prop(pos, l, r);
        return;
    }
    int mid = (l + r) / 2;
    if(left < mid) {
        upd(left, right, val, pos * 2, l, mid);
    }
    if(right > mid) {
        upd(left, right, val, pos * 2 + 1, mid, r);
    }
    prop(pos, l, r);
    prop(pos * 2, l, mid);
    prop(pos * 2 + 1, mid, r);
    tree[pos].total = tree[pos * 2].total + tree[pos *  2+ 1].total;
}
int query(int left, int right, int pos = 1, int l = 0, int r = MAXN) {
    prop(pos, l, r);
    if(left <= l && right >= r) {
        return tree[pos].total;
    }
    int mid = (l + r) / 2;
    int total = 0;
    if(left < mid) {
        total += query(left, right, pos * 2, l, mid);
    }
    if(right > mid) {
        total += query(left, right, pos * 2 + 1, mid, r);
    }
    return total;
}
