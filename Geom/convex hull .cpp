// O(n * log(n))

// Построение выпуклой оболочки алгоритмом Эндрю
// Точки в порядке обхода по часовой стрелке

vector<Point> build_convex_hull(vector<Point> vec) {
    sort(all(vec));
    vector<Point> ch, ch2;
    for(int i = 0; i < siz(vec); ++i) {
        Point c = vec[i];
        while(siz(ch) >= 2) {
            Point a = ch[siz(ch) - 2], b = ch.back();
            if((c - a) % (b - a) > 0) break;
            ch.pop_back();
        }
        ch.push_back(c);
    }
    for(int i = siz(vec) - 1; i >= 0; --i) {
        Point c = vec[i];
        while(siz(ch2) >= 2) {
            Point a = ch2[siz(ch2) - 2], b = ch2.back();
            if((c - a) % (b - a) > 0) break;
            ch2.pop_back();
        }
        ch2.push_back(c);
    }
    for(int i = 1; i + 1 < siz(ch2); ++i) ch.push_back(ch2[i]);
    return ch;
}
