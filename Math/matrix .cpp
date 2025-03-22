using matrix = vector<vector<int>>;

// Умножение матриц O(n**3)

matrix matmul(matrix &a, matrix &b) {
    int n = siz(a), k = siz(a[0]), m = siz(b);
    matrix c(n, vector<int>(m));
    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < m; ++j) {
            for(int y = 0; y < k; ++y) {
                c[i][j] += a[i][y] * b[y][j];
            }
        }
    }
    return c;
}


// Бинарное возведение матрицы (n x n) в степень O(n**3 * log(k))

matrix binpow(matrix a, int k) {
    matrix b(siz(a), vector<int>(siz(a), 0));
    for(int i = 0; i < siz(a); ++i) b[i][i] = 1;
    while(k) {
        if(k & 1) b = matmul(a, b);
        a = matmul(a, a);
        k >>= 1;
    }
    return b;
}
