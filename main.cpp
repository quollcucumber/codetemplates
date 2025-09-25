//code templates
#include <bits/stdc++.h>
#define int long long
using namespace std;


//number theory
int numfactors(int node);
int gcd(int a, int b);
int lcm(int a, int b) ;
bool isprime(int num);
//tree stuff
void root(int node);
void distroot(int node);
int lca(int a, int b);
void jump();
int moveup(int node, int dist);

//segtree
int query(int left, int right) ;
void update(int index, int val) ;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    return 0;
}

//number theory
int numfactors(int node) {
    int total = 0;
    for(int i = 2; i <= sqrt(node); i++) total += node % i == 0;
    return total;
}
bool isprime(int num) {
    if(num == 1) return false;
    for(int i = 2; i<= sqrt(num); i++) if(num % i == 0) return false;
    return true;
}
int gcd(int a, int b) {
    if(b == 0) return a;
    return gcd(b, a % b);
}
int lcm(int a, int b) {
    return a * b / gcd(a, b);
}
//trees

//To do LCA, copy all of these.

vector<int> neighbors[500005];
vector<int> children[500005];
bool seen[500005];
int parents[500005];
void root(int node) {
    seen[node] = true;
    for(int i : neighbors[node]) {
        if(!seen[i]) {
            root(i);
            children[node].push_back(i);
            parents[i] = node;
        }
    }
}
int dist[500005];
void distroot(int node) {
    //Remember to set dist of node 1 to 0;
    for(int i : children[node]) {
        dist[i] = dist[node] + 1;
        distroot(i);
    }
}

int jmppoint[500005][30];
void jump() {
    parents[1] = 1;
    for(int i = 0; i < 500005;i++) {
        jmppoint[i][0] = parents[i];
    }
    for(int i = 1; i < 30; i++) {
        for(int j = 0; j < 500005; j++) {
            jmppoint[j][i] = jmppoint[jmppoint[j][i-1]][i-1];
        }
    }
}

int moveup(int node, int dist) {
    for(int i = 0; i < 30; i++) {
        if(dist % 2 == 1) node = jmppoint[node][i];
        dist /= 2;
    }
    return node;
}

int lca(int a, int b) {
    //before doing lca, root once and dist root once, and jump once, in that order.
    if(dist[a] > dist[b]) {
        a = moveup(a, dist[a] - dist[b]);
    }else if (dist[b] > dist[a]) {
        b = moveup(b, dist[b] - dist[a]);
    }
    if(a == b) {
        return a;
    }
    for(int i = 29; i >= 0; i--) {
        if(jmppoint[a][i] != jmppoint[b][i]) {
            a = jmppoint[a][i];
            b = jmppoint[b][i];
        }
    }
    return parents[a];
}

//iterative segment tree
int segtree[1000015];
int query(int left, int right){
    left += 500005;
    right += 500006;
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
    segtree[index + 500005] = val;
    for(int i  = (index + 500005) / 2; i > 0; i--) {
        // can replace this with any comparison
        segtree[i] = segtree[i * 2] + segtree[i * 2 + 1];
    }
}


//graph stuff

