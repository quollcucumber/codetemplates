// #pragma GCC optimize("Ofast,unroll-loops")
#include <bits/stdc++.h>
// #pragma GCC target("avx2")
#define int long long
using namespace std;
struct treap {
     int subsum;
     int prioriy;
     int element;
     treap * l;
     treap * r;
     void fix() {
          subsum = 1;
          if(l!=NULL) subsum += l->subsum;
          if(r!=NULL) subsum += r->subsum;
     }
};
treap * merge(treap * a, treap * b) {
     if(a == NULL) return b;
     if(b == NULL) return a;
     if(a->prioriy > b->prioriy) {
          if(a->r == NULL) a->r = b;
          else a->r = merge(a->r, b);
          a-> fix();
          return a;
     }else {
          if(b->l == NULL) b->l = a;
          else b->l = merge(a, b->l);
          b->fix();
          return b;
     }
}
pair<treap *, treap *> split(treap * a, int subsum) {
     if(subsum == 0) return {NULL, a};
     if(a == NULL) return {NULL, NULL};
     int leftsize = 0;
     if(a -> l != NULL) leftsize = a->l->subsum;
     if(subsum <= leftsize) {
          pair<treap *, treap *> b = split(a->l, subsum);
          a->l = b.second;
          a->fix();
          return {b.first, a};
     }else {
          pair<treap *, treap *> b = split(a->r, subsum - leftsize - 1);
          a->r = b.first;
          a->fix();
          return {a, b.second};
     }
}
const int MAXN = 500005;
treap arr[MAXN];
mt19937 Rand(random_device{}());
int n;
treap * tree = NULL;
int query(int pos) {
     pair<treap *, treap *> a = split(tree, pos);
     pair<treap *, treap *> b = split(a.second, 1);
     int ans = b.first->element;
     tree = merge(a.first, merge(b.first, b.second));
     return ans;
}
signed main() {
     cin >> n;
     int q;
     cin >> q;
     for(int i = 0; i < n; i++) {
          char c;
          cin >> c;
          treap * val = &arr[i];
          val->subsum = 1; val->prioriy = Rand(); val -> element = c; val ->l = NULL; val ->r = NULL;
          tree = merge(tree, val);
     }
     for(int i = 0; i < q; i++) {
          int l, r;
          cin >> l >> r;
          l--, r--;
          pair<treap *, treap *> a = split(tree, l);
          pair<treap *, treap *> b = split(a.second, (r - l + 1));
          tree = merge(a.first, merge(b.second, b.first));
     }
     for(int i = 0; i < n; i++) {
          cout<<(char)query(i);
     }
     cout<<'\n';
     return 0;
}
