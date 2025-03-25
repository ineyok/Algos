// O(log(n) * log(m))

// Двумерное дерево Фенвика
// ? Сумма в префиксном прямоугольнике
// ! Изменение в точке

struct Fenwick_2D {
    int n, m;
    vector<vector<int>> tree;

    Fenwick_2D(int n, int m) : n(n), m(m), tree(n, vector<int>(m)) {}

    int query(int i, int j_) {
        int ans = 0;
        for(; i >= 0; i = (i & (i + 1)) - 1) {
            for(int j = j_; j >= 0; j = (j & (j + 1)) - 1) {
                ans += tree[i][j];
            }
        }
        return ans;
    }

    void update(int i, int j_) {
        for(; i < n; i |= i + 1) {
            for(int j = j_; j < m; j |= j + 1) {
                tree[i][j]++;
            }
        }
    }
};
