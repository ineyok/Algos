// O(n * log(n)) на построение

// Сортируем суффиксы строки

s += '$';
int n = siz(s);
vector<int> p(n), c(n);
vector<pair<int, int>> a(n);
for(int i = 0; i < n; ++i) a[i] = {s[i], i};
sort(all(a));
for(int i = 0; i < n; ++i) p[i] = a[i].second;
for(int i = 1; i < n; ++i) {
    c[p[i]] = c[p[i - 1]] + (a[i].first != a[i - 1].first);
}
for(int k = 0; (1 << k) < n; ++k) {
    vector<pair<pair<int, int>, int>> a(n), new_a(n);
    vector<int> cnt(n), start(n);
    for(int i = 0; i < n; ++i) {
        int j = (p[i] - (1 << k) + n) % n;
        a[i] = {{c[j], c[p[i]]}, j};
        cnt[c[j]]++;
    }
    for(int i = 1; i < n; ++i) start[i] = start[i - 1] + cnt[i - 1];
    for(auto & el : a) new_a[start[el.first.first]++] = el;
    a = new_a;
    for(int i = 0; i < n; ++i) p[i] = a[i].second;
    c[p[0]] = 0;
    for(int i = 1; i < n; ++i) {
        c[p[i]] = c[p[i - 1]] + (a[i].first != a[i - 1].first);
    }
}
// порядок в P
