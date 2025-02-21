template<typename T>
struct PointT {
    T x, y;

    PointT() {}
    PointT(T x, T y) : x(x), y(y) {}

    double len() const { return sqrt(x * x + y * y); }
    PointT norm() const { return (len() ? PointT(x / len(), y / len()) : *this); }

    PointT operator*(T k) const { return PointT(x * k, y * k); }
    PointT operator/(T k) const { return PointT(x / k, y / k); }
    PointT operator+(PointT b) const { return PointT(x + b.x, y + b.y); }
    PointT operator-(PointT b) const { return PointT(x - b.x, y - b.y); }

    PointT &operator*=(T k) { x *= k, y *= k; return *this; }
    PointT &operator/=(T k) { x /= k, y /= k; return *this; }
    PointT &operator+=(PointT b) { x += b.x, y += b.y; return *this; }
    PointT &operator-=(PointT b) { x -= b.x, y -= b.y; return *this; }

    T operator*(PointT b) const { return x * b.x + y * b.y; }
    T operator%(PointT b) const { return x * b.y - y * b.x; }

    friend bool operator<(const PointT &a, const PointT &b) { return (a.x == b.x ? a.y < b.y : a.x < b.x); }
    friend bool operator<=(const PointT &a, const PointT &b) { return (a.x == b.x ? a.y <= b.y : a.x < b.x); }
    friend bool operator>(const PointT &a, const PointT &b) { return (a.x == b.x ? a.y > b.y : a.x > b.x); }
    friend bool operator>=(const PointT &a, const PointT &b) { return (a.x == b.x ? a.y >= b.y : a.x > b.x); }
    friend bool operator==(const PointT &a, const PointT &b) { return a.x == b.x && a.y == b.y; }
    friend bool operator!=(const PointT &a, const PointT &b) { return a.x != b.x || a.y != b.y; }

    double polar_angle() const { return (y >= 0 ? acos(x / len()) : 2 * PI - acos(x / len())); }
};
template<typename T>
istream &operator>>(istream &is, PointT<T> &p) {
    return is >> p.x >> p.y;
}
template<typename T>
ostream &operator<<(ostream &os, PointT<T> p) {
    return os << p.x << ' ' << p.y;
}

using Point = PointT<X_type>;
