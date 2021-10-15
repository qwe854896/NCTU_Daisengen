/* Find the maximum number of matchings in bipartite */
int match[V], vis[V], rnd;
vi g[V];
bool dfs(int id) {
    vis[id] = rnd;
    for (auto &x : g[id]) {
        if (match[x] == 0) {
            match[id] = x;
            match[x] = id;
            return true;
        } else {
            if (vis[match[x]] == rnd) continue;
            if (dfs(match[x])) {
                match[id] = x;
                match[x] = id;
                return true;
            }
        }
    }
    return false;
}
int hungary() {
    for(int i = 0; i <= n; ++i) vis[i] = match[i] = -1;
    rnd = 0;
    // iterate first set
    int ans = 0;
    for (int i = 1; i <= u; ++i) {
        if (match[i] == 0) {
            ++rnd;
            if (dfs(i)) ++ans;
        }
    }
    return ans;
}