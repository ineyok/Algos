auto f = [&](int a, int b) {
    return a < b;
};

auto dfs = [&](auto &&self, int v, int p, int lvl) -> void {
    self(self, to, v, lvl + 1);
    // ...
};
dfs(dfs, 0, 0, 0);
