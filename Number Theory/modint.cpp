/**
 * Description :- modular arithmetic operations
 * Source :- https://codeforces.com/contest/1342/submission/78409946
 * Verification:- https://open.kattis.com/problems/modulararithmetic
 */
 
template<const int &MOD>
struct _m_int {
  int val;
 
  _m_int(int64_t v = 0) {
    if(v < 0) v = v % MOD + MOD;
    if(v >= MOD) v %= MOD;
    val = v;
  }
 
  static int inv_mod(int a, int m = MOD) {
  	// https://en.wikipedia.org/wiki/Extended_Euclidean_algorithm#Example
    int g = m, r = a, x = 0, y = 1;
 
    while(r != 0) {
      int q = g / r;
      g %= r; swap(g, r);
      x -= q * y; swap(x, y);
    }
		return x < 0 ? x + m : x;
  }
 	// wont work if we use #define int int64_t
  // explicit operator int() const { return val; }
  explicit operator int64_t() const { return val; }
 
  _m_int& operator+=(const _m_int &other) {
    val -= MOD - other.val;
    if(val < 0) val += MOD;
    return *this;
  }
 
  _m_int& operator-=(const _m_int &other) {
  	val -= other.val;
    if(val < 0) val += MOD;
    return *this;
  }
 
  static unsigned fast_mod(uint64_t x, unsigned m = MOD) {
#if !defined(_WIN32) || defined(_WIN64)
    return x % m;
#endif
    // Optimized mod for Codeforces 32-bit machines.
    // x must be less than 2^32 * m for this to work, so that x / m fits in a 32-bit unsigned int.
    unsigned x_high = x >> 32, x_low = (unsigned) x;
    unsigned quot, rem;
    asm("divl %4\n"
      : "=a" (quot), "=d" (rem)
      : "d" (x_high), "a" (x_low), "r" (m));
    return rem;
  }
 
  _m_int& operator*=(const _m_int &other) {
    val = fast_mod((uint64_t) val * other.val);
    return *this;
  }
 
  _m_int& operator/=(const _m_int &other) {
    return *this *= other.inv();
  }
 
  friend _m_int operator+(const _m_int &a, const _m_int &b) { return _m_int(a) += b; }
  friend _m_int operator-(const _m_int &a, const _m_int &b) { return _m_int(a) -= b; }
  friend _m_int operator*(const _m_int &a, const _m_int &b) { return _m_int(a) *= b; }
  friend _m_int operator/(const _m_int &a, const _m_int &b) { return _m_int(a) /= b; }
 
  _m_int& operator++() {
    val = val == MOD - 1 ? 0 : val + 1;
    return *this;
  }
 
  _m_int& operator--() {
    val = val == 0 ? MOD - 1 : val - 1;
    return *this;
  }
 	
 	// wont work if we use #define int int64_t
  // _m_int operator++(int) { _m_int before = *this; ++*this; return before; }
  // _m_int operator--(int) { _m_int before = *this; --*this; return before; }
 
  _m_int operator-() const {
    return val == 0 ? 0 : MOD - val;
  }
 
  bool operator==(const _m_int &other) const { return val == other.val; }
  bool operator!=(const _m_int &other) const { return val != other.val; }
 
  _m_int inv() const {
    return inv_mod(val);
  }
 
  _m_int pow(int64_t p) const {
  	if(p < 0)	return inv().pow(-p);
    _m_int a = *this, result = 1;
    while(p > 0) {
      if(p & 1)	result *= a;
      a *= a;
      p >>= 1;
    }
    return result;
  }
 
  friend ostream& operator<<(ostream &os, const _m_int &m) {
    return os << m.val;
  }
};
 
extern const int MOD = int(1e9) + 7;
using mint = _m_int<MOD>;
 
vector<mint> inv, factorial, inv_factorial, sub_factorial;
 
void prepare_factorials(int maximum) {
	// Make sure MOD is prime, which is necessary for the inverse algorithm below.
  for(int p = 2; p * p <= MOD; p += p % 2 + 1){
    assert(MOD % p != 0);
  }
 
  inv = {0, 1};
  factorial = inv_factorial = {1, 1};
 	sub_factorial = {1, 0};
 	
  maximum = max(maximum, 1);
  inv.resize(maximum + 1);
  factorial.resize(maximum + 1);
  inv_factorial.resize(maximum + 1);
 	sub_factorial.resize(maximum + 1);
 	
  for(int i = 2; i <= maximum; i++) {
    inv[i] = inv[MOD % i] * (MOD - MOD / i);
    factorial[i] = i * factorial[i - 1];
    inv_factorial[i] = inv[i] * inv_factorial[i - 1];
    sub_factorial[i] = i * sub_factorial[i-1] + ((i&1) ? -1 : 1);
  }
}
 
mint choose(int n, int r) {
  if (r < 0 || r > n) return 0;
  return factorial[n] * inv_factorial[r] * inv_factorial[n - r];
}
 
mint inv_choose(int n, int r) {
  assert(0 <= r && r <= n);
  return inv_factorial[n] * factorial[r] * factorial[n - r];
}
 
mint permute(int n, int r) {
  if (r < 0 || r > n) return 0;
  return factorial[n] * inv_factorial[n - r];
}
 
mint inv_permute(int n, int r) {
  assert(0 <= r && r <= n);
  return inv_factorial[n] * factorial[n - r];
}

mint catalan(int n) {
	return C(2*n, n) / (n+1);
}
 
mint stirling_second(int n, int k) {
  mint answer = 0;
  for(int x = 0; x <= k; x++){
    answer += ((k - x) % 2 == 0 ? +1 : -1) * choose(k, x) * mint(x).pow(n);
 	}
  return answer;
}

/*
	sterling numbers of second kind
mint S[N][K];
f(i,0,N+1){
  	f(j,0,K+1){
  		if(i == 0 && j == 0){
  			S[i][j] = 1; continue;
  		}else if(i == 0 or j == 0){
  			S[i][j] = 0; continue;
  		}
  		S[i][j] = j * S[i-1][j] + S[i-1][j-1];
  	}
  }


*/


































