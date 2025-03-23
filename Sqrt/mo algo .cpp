// O(n * sqrt(n))

// Оффлайн алгоритм МО

vector<vector<int>> zap(t);
vector<ll> ans(t);
for(int i = 0; i < t; ++i) {
    int l, r;
    cin >> l >> r, l--, r--;
    zap[i] = {l, r, i};
}
sort(all(zap), [&](vector<int>& a, vector<int>& b) {
    if(a[0] / K != b[0] / K) return a[0] / K < b[0] / K;
    return a[1] < b[1];
});
int l = 0, r = -1;
ll sum = 0;
for(auto & el : zap) {
    int nl = el[0], nr = el[1], ind = el[2];
    while(nl < l) {
        l--;
        sum -= 1ll * cnt[a[l]] * cnt[a[l]] * a[l];
        cnt[a[l]]++;
        sum += 1ll * cnt[a[l]] * cnt[a[l]] * a[l];
    }
    while(r < nr) {
        r++;
        sum -= 1ll * cnt[a[r]] * cnt[a[r]] * a[r];
        cnt[a[r]]++;
        sum += 1ll * cnt[a[r]] * cnt[a[r]] * a[r];
    }
    while(l < nl) {
        sum -= 1ll * cnt[a[l]] * cnt[a[l]] * a[l];
        cnt[a[l]]--;
        sum += 1ll * cnt[a[l]] * cnt[a[l]] * a[l];
        l++;
    }
    while(nr < r) {
        sum -= 1ll * cnt[a[r]] * cnt[a[r]] * a[r];
        cnt[a[r]]--;
        sum += 1ll * cnt[a[r]] * cnt[a[r]] * a[r];
        r--;
    }
    ans[ind] = sum;
}
