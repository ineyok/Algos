// Найти кратчайший путь от S до всех остальных
// Ребра неотрицательного веса
// O(n * log(n))

vector<ll> dist(n, LINF);
dist[S] = 0;
set<pair<ll, int>> st;
st.insert({0, S});
while(siz(st)) {
  int v = st.begin()->second; st.erase(st.begin());
  for(auto & [to, w] : g[v]) {
    if(dist[to] > dist[v] + w) {
      st.erase({dist[to], to});
      dist[to] = dist[v] + w;
      st.insert({dist[to], to});
    }
  }
}
