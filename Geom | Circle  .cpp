// структура окружности / круга
// Point предпологается double

struct Circle {
    Point o;
    double r;

    Circle() {}
    Circle(Point o, double r) : o(o), r(r) {}
    Circle(Circle & ref) = default;

    Circle(Point o) : o(o), r(0) {}
    Circle(Point a, Point b) {
        o = (a + b) / 2;
        r = (o - a).len();
    }
    Circle(Point a, Point b, Point c) {
        Line ln(a, b);
        if(abs(ln.A * c.x + ln.B * c.y + ln.C) < EPS) {
            double d = (a - b).len();
            Point p1 = a, p2 = b;
            if((a - c).len() > d) d = (a - c).len(), p2 = c;
            if((b - c).len() > d) d = (b - c).len(), p1 = b;
            o = (p1 + p2) / 2;
            r = d / 2;
            return;
        }
        Point mab = (a + b) / 2, mac = (a + c) / 2;
        Line lab(a, b), lac(a, c);
        Line l1(mab, mab + lab.n), l2(mac, mac + lac.n);
        o = inter_line_line(l1, l2);
        r = (o - a).len();
    }
};
