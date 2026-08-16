#include <bits/stdc++.h>
#define int long long
using namespace std;

vector<int> neighbors[200005];
vector<pair<int, bool>> children[200005]; // true is heavy, false is light
bool seenroot[200005];
int subsum[200005];
pair<int, bool> parent[200005];
void root(int node) {
     seenroot[node] = true;
     subsum[node] = 1;
     for(int i : neighbors[node]) {
          if(!seenroot[i]) {
               children[node].push_back({i, 67});
               root(i);
               parent[i] = {node, 67};
               subsum[node] += subsum[i];
          }
     }
}
const int MAXN= 200005;
int tree[MAXN * 2];
void upd(int node, int val) {
     tree[node += MAXN] = val;
     for(node /= 2; node > 0; node /= 2) tree[node] = max(tree[node * 2], tree[node * 2 + 1]);
}
int query(int left, int right) {
     int maxval = 0;
     left += MAXN;
     right += MAXN;
     while(left < right) {
          if(left & 1) maxval = max(maxval, tree[left ++]);
          if(right & 1) maxval = max(maxval, tree[--right]);
          left /=2;
          right /= 2;
     }
     return maxval;
}
void change(int node, int val) {

}
int querynode(int a, int b) {

}
signed main() {
     int n, q;
     cin >> n >> q;
     vector<int> arr(n);
     for(int i = 0; i < n; i++) cin >> arr[i];
     for(int i = 0; i < n-1; i++) {
          int a,b;
          cin >> a >> b;
          neighbors[a].push_back(b);
          neighbors[b].push_back(a);
     }
     root(1);
     for(int i = 1; i <= n; i++) {
          for(int j = 0; j < children[i].size(); j++) {
               if(subsum[children[i][j].first] > subsum[i]/2) {
                    children[i][j].second = true;
                    parent[children[i][j].first].second = true;
               }else {
                    children[i][j].second = false;
                    parent[children[i][j].first].second = false;
               }
          }
     }
     vector<vector<int>> hldpaths;
     set<int> nodes;
     for(int i = 1; i <= n; i++) {
          if(children[i].empty())nodes.insert(i);
     }
     vector<pair<int, int>> loc(n + 1);
     vector<int> numchildren(n+1);
     for(int i = 1; i <= n; i++) numchildren[i] = children[i].size();
     vector<pair<int, int>> hldranges;
     while(!nodes.empty()) {
          int node = *nodes.begin();
          nodes.erase(nodes.begin());
          vector<int> path;
          path.push_back(node);
          loc[node] = {hldpaths.size(), 0};
          while(node != 1 && parent[node].second) {
               node = parent[node].first;
               numchildren[node]--;
               loc[node] = {hldpaths.size(), path.size()};
               path.push_back(node);
          }
          if(node != 1) {
               node = parent[node].first;
               numchildren[node]--;
               if(numchildren[node] == 0) {
                    nodes.insert(node);
               }
          }
          hldpaths.push_back(path);
          if(hldranges.empty()) {
               hldranges.push_back({0, path.size()});
          }else {
               hldranges.push_back({hldranges[hldranges.size() -1].second, hldranges[hldranges.size() -1].second + path.size()});
          }
     }
     for(int i = 0; i < n; i++) {
          change(i+1, arr[i]);
     }
     for(int i = 0; i < q; i++) {

     }
     return 0;
}
