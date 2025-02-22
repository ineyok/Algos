struct Line {
    double A, B, C;
    Point p1, p2, n, r;

    void recalc_vecs() {
        n = {A, B};
        r = {-B, A};
    }

    Line() {}
    Line(Point a, Point b) : A(a.y - b.y), B(b.x - a.x), C(a % b), p1(a), p2(b) {
        recalc_vecs();
    }
    Line(const Line &ref) = default;

    Line norm() const {
        Line ans(*this);
        double k = sqrt(A * A + B * B);
        if (C > 0) k *= -1;
        ans.A /= k, ans.B /= k, ans.C /= k;
        if (ans.A < 0 || (ans.A == 0 && ans.B < 0)) ans.A *= -1, ans.B *= -1, ans.C *= -1;
        ans.recalc_vecs();
        return ans;
    }
};
