template<typename T>
struct LineT {
    T A, B, C;
    Point p1, p2, n, r;

    void help() {
        if (C > 0) A *= -1, B *= -1, C *= -1;
        if (A < 0 || (A == 0 && B < 0)) A *= -1, B *= -1, C *= -1;
        n = {A, B};
        r = {-B, A};
    }

    LineT() {}
    LineT(Point a, Point b) : A(a.y - b.y), B(b.x - a.x), C(a % b), p1(a), p2(b) {
        help();
    }
    LineT(T A, T B, T C) : A(A), B(B), C(C) {
        help();
    }
    LineT(const LineT &ref) = default;

    LineT norm() const {
        LineT ans(*this);
        double k = sqrt(A * A + B * B);
        ans.A /= k, ans.B /= k, ans.C /= k;
        ans.help();
        return ans;
    }
};

using Line = LineT<ll>;
