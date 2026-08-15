const int MAXN = 500005;
vector<int> neighbors[MAXN];
vector<int> children[MAXN];
bool seen[MAXN];
int parents[MAXN];
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
int dist[MAXN];
void distroot(int node) {
    //Remember to set dist of node 1 to 0;
    for(int i : children[node]) {
        dist[i] = dist[node] + 1;
        distroot(i);
    }
}

int jmppoint[MAXN][30];
void jump() {
    parents[1] = 1;
    for(int i = 0; i < MAXN;i++) {
        jmppoint[i][0] = parents[i];
    }
    for(int i = 1; i < 30; i++) {
        for(int j = 0; j < MAXN; j++) {
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
