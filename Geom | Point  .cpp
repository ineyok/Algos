struct Point {
    double x, y;

    Point() {}
    Point(double x, double y) : x(x), y(y) {}

    double len() const { return sqrt(x * x + y * y); }
    Point norm() const { return (len() ? Point(x / len(), y / len()) : *this); }

    Point operator*(double k) const { return Point(x * k, y * k); }
    Point operator/(double k) const { return Point(x / k, y / k); }
    Point operator+(Point b) const { return Point(x + b.x, y + b.y); }
    Point operator-(Point b) const { return Point(x - b.x, y - b.y); }

    Point &operator*=(double k) { x *= k, y *= k; return *this; }
    Point &operator/=(double k) { x /= k, y /= k; return *this; }
    Point &operator+=(Point b) { x += b.x, y += b.y; return *this; }
    Point &operator-=(Point b) { x -= b.x, y -= b.y; return *this; }

    double operator*(Point b) const { return x * b.x + y * b.y; }
    double operator%(Point b) const { return x * b.y - y * b.x; }

    friend bool operator<(const Point &a, const Point &b) { return (a.x == b.x ? a.y < b.y : a.x < b.x); }
    friend bool operator<=(const Point &a, const Point &b) { return (a.x == b.x ? a.y <= b.y : a.x < b.x); }
    friend bool operator>(const Point &a, const Point &b) { return (a.x == b.x ? a.y > b.y : a.x > b.x); }
    friend bool operator>=(const Point &a, const Point &b) { return (a.x == b.x ? a.y >= b.y : a.x > b.x); }
    friend bool operator==(const Point &a, const Point &b) { return a.x == b.x && a.y == b.y; }
    friend bool operator!=(const Point &a, const Point &b) { return a.x != b.x || a.y != b.y; }

    double polar_angle() const { return (y >= 0 ? acos(x / len()) : 2 * PI - acos(x / len())); }
};
istream &operator>>(istream &is, Point &p) {
    return is >> p.x >> p.y;
}
ostream &operator<<(ostream &os, Point p) {
    return os << p.x << ' ' << p.y;
}
