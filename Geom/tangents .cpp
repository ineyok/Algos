// O(log(n))

// Поиск касательных к выпуклому многоугольнику (возвращает индексы 2-х точек многоугольника)
// Идея прыжки на степень 2

// Касательные из точки
pair<int, int> targents_by_point(Point p, vector<Point> &vec) {
    pair<int, int> ans;
    int v = 0, n = siz(vec);
    for (int k = 20; k >= 0; --k) {
        int u = (v + (1 << k)) % n, w = (v - (1 << k) % n + n) % n;
        if ((p - vec[u]) % (p - vec[v]) < 0) v = u;
        if ((p - vec[w]) % (p - vec[v]) < 0) v = w;
    }
    ans.first = v;
    for (int k = 20; k >= 0; --k) {
        int u = (v + (1 << k)) % n, w = (v - (1 << k) % n + n) % n;
        if ((p - vec[u]) % (p - vec[v]) > 0) v = u;
        if ((p - vec[w]) % (p - vec[v]) > 0) v = w;
    }
    ans.second = v;
    return ans;
}

// Касательные, параллельные прямой
pair<int, int> tangents_by_line(Line ln, vector<Point> & vec) {
    pair<int, int> ans;
    int v = 0, n = siz(vec);
    for(int k = 20; k >= 0; --k) {
        int u = (v + (1 << k)) % n, w = (v - (1 << k) % n + n) % n;
        if(Line(vec[u], vec[u] + ln.r).C < Line(vec[v], vec[v] + ln.r).C) v = u;
        if(Line(vec[w], vec[w] + ln.r).C < Line(vec[v], vec[v] + ln.r).C) v = w;
    }
    ans.first = v;
    for(int k = 20; k >= 0; --k) {
        int u = (v + (1 << k)) % n, w = (v - (1 << k) % n + n) % n;
        if(Line(vec[u], vec[u] + ln.r).C > Line(vec[v], vec[v] + ln.r).C) v = u;
        if(Line(vec[w], vec[w] + ln.r).C > Line(vec[v], vec[v] + ln.r).C) v = w;
    }
    ans.second = v;
    return ans;
}
