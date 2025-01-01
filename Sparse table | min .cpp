// ? min на отрезке (можно любую идемпотентную операцию)

struct Sparse {
    int n;
    vector<vector<int>> table;
    Sparse(vector<int> & ar) {
        n = size(ar);
        table.resize(32 - __builtin_clz(n), vector<int>(n));
        table[0] = ar;
        for(int i = 1; i < size(table); ++i) {
            for(int j = 0; j + (1 << i) - 1 < n; ++j) {
                table[i][j] = min(table[i - 1][j], table[i - 1][j + (1 << (i - 1))]);
            }
        }
    }

    int query(int l, int r) {
        int i = 31 - __builtin_clz(r - l + 1);
        return min(table[i][l], table[i][r - (1 << i) + 1]);
    }
};
