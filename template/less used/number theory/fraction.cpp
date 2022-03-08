// source :- https://atcoder.jp/contests/abc229/submissions/27756683
// verify :- https://atcoder.jp/contests/abc229/submissions/27881183

// namespace fast_gcd {
//   using u64 = uint64_t;
//   using u32 = uint32_t;
 
//   __attribute__((target("bmi"))) constexpr u64 binary_gcd(u64 a, u64 b) {
//     if(a == 0 || b == 0) return a + b;
//     int n = __builtin_ctzll(a);
//     int m = __builtin_ctzll(b);
//     a >>= n;
//     b >>= m;
//     while(a != b) {
//       int m = __builtin_ctzll(a - b);
//       bool f = a > b;
//       u64 c = f ? a : b;
//       b = f ? b : a;
//       a = (c - b) >> m;
//     }
//     return a << min(n, m);
//   }
// } // namespace fast_gcd
 
// using fast_gcd::binary_gcd;

// q / p
struct frac {
  using ll = long long;
  template <typename T> 
  static constexpr inline T gcd(const T a, const T b) { return (b == 0) ? a : gcd(b, a % b); }
  // fraction of form q/p, p > 0, gcd(p,q) = 1.
  ll q, p;
  inline constexpr void simplify() {
    if(p < 0) {
      p *= -1;
      q *= -1;
    }
    ll g = gcd(q < 0 ? -q : q, p);
    if(g) {
      p /= g;
      q /= g;
      if(p == 0 and q < 0) q = 1;
    }
  }
  constexpr frac(ll q = 0, ll p = 1) noexcept : q(q), p(p) { simplify(); }

  constexpr ll ciel() noexcept { return q/p + ((q^p) > 0 && q%p); }
  constexpr ll floor() noexcept { return q/p - ((q^p) < 0 && q%p); }

  constexpr bool operator<(const frac &r) const { return q * r.p < p * r.q; }
  constexpr bool operator>(const frac &r) const { return q * r.p > p * r.q; }
  constexpr bool operator<=(const frac &r) const { return q * r.p <= p * r.q; }
  constexpr bool operator>=(const frac &r) const { return q * r.p >= p * r.q; }
  template <class T> constexpr bool operator<(const T &r) const { return *this < frac(r); }
  template <class T> constexpr bool operator>(const T &r) const { return *this > frac(r); }
  constexpr bool operator==(const frac &r) const { return q * r.p == p * r.q; }
  constexpr bool operator!=(const frac &r) const { return !((*this) == r); }
  constexpr frac operator+() const noexcept { return *this; }
  constexpr frac operator-() const noexcept { return frac(-q, p); }
  constexpr frac operator+(const frac r) const noexcept { return frac(*this) += r; }
  constexpr frac operator-(const frac r) const noexcept { return frac(*this) -= r; }
  constexpr frac operator*(const frac r) const noexcept { return frac(*this) *= r; }
  constexpr frac operator/(const frac r) const noexcept { return frac(*this) /= r; }
  constexpr frac &operator+=(const frac &r) noexcept {
    ll g = gcd(p, r.p);
    q = r.p / g * q + p / g * r.q;
    p = p / g * r.p;
    (*this).simplify();
    return *this;
  }
  constexpr frac &operator-=(const frac &r) noexcept {
    ll g = gcd(p, r.p);
    q = r.p / g * q - p / g * r.q;
    p = p / g * r.p;
    (*this).simplify();
    return *this;
  }
  constexpr frac &operator*=(const frac &r) noexcept {
    q *= r.q;
    p *= r.p;
    (*this).simplify();
    return *this;
  }
  constexpr frac &operator/=(const frac &r) noexcept {
    q *= r.p;
    p *= r.q;
    (*this).simplify();
    return *this;
  }
 
  void print() {
    long double tmp = (long double)q / (long double)p;
    cout << tmp;
  }
};
istream &operator>>(istream &is, frac &p) {
  long long a;
  is >> a;
  p = frac(a, 1);
  return is;
}
ostream &operator<<(ostream &os, const frac &r) { return os << 1.0 * r.q / r.p; }