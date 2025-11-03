//code templates
#include <bits/stdc++.h>
#define int long long
using namespace std;

//Fast input

int rdint(); // reads in an int
void prtint(int num); //prints an int
string rdstring(); // reads in a string
void prtstr(string s); // prints a string

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

//add big numbers
string sum(string a, string b);


signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    return 0;
}

//fast input
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




//add big numbers
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
