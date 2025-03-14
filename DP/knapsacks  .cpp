// Пусть сумма всех весов = S, тогда различных <= sqrt(S)
// Предметы веса X -> X, 2X, (2**k)X, ostX
// O(W * sqrt(S))
vector<int> items;
unordered_map<int, int> mp;
for(int el : items) mp[el]++;
items.clear();
for (auto [w, k] : mp) {
    int p = 1;
    while (k >= p) {
        items.push_back(w * p);
        k -= p;
        p *= 2;
    }
    if (k) items.push_back(w * k);
}



// Посчитаем кол-во способов набрать веса [0..W] всеми предметами
// Можно посмотреть результат ДП без некоторых предметов (откат дп)

// откат одного предмета w
uint64_t dp[mxN], pdp[mxN];
for (ll x = 0; x <= n; ++x) {
    pdp[x] = dp[x];
    if (x + w <= n) {
        pdp[x + w] -= pred[x];
    }
    // ответ pdp
}
