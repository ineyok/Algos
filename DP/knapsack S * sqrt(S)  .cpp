// Если K различных весов предметов, то преобразуем веса, чтобы предметов всего стало K * log(K)
// Пусть сумма всех весов = S, тогда различных <= sqrt(S)
// O(W * K * log(k)) = O(S * sqrt(S))

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
