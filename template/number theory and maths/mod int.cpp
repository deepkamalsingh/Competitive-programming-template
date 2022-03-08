/**
 * Description :- modular arithmetic operations
 * Source :- https://codeforces.com/contest/1342/submission/78409946
 * Verification:- https://open.kattis.com/problems/modulararithmetic
 */

#ifdef int
  static_assert(false,"Do not define int.");
#endif




template<const unsigned &MOD>
struct _m_uint {
  unsigned val;
 
  _m_uint(int64_t v = 0){
    if(v < 0) v = v % MOD + MOD;
    if(v >= MOD) v %= MOD;
    val = unsigned(v);
  }
 
  _m_uint(uint64_t v){
    if(v >= MOD) v %= MOD;
    val = unsigned(v);
  }
 
  _m_uint(int v) : _m_uint(int64_t(v)) {}
  _m_uint(unsigned v) : _m_uint(uint64_t(v)) {}
 
  explicit operator unsigned() const { return val; }
  explicit operator int64_t() const { return val; }
  explicit operator uint64_t() const { return val; }
  explicit operator double() const { return val; }
  explicit operator long double() const { return val; }
 
  _m_uint& operator+=(const _m_uint &other){
    val = val < MOD - other.val ? val + other.val : val - (MOD - other.val);
    return *this;
  }
 
  _m_uint& operator-=(const _m_uint &other){
    val = val < other.val ? val + (MOD - other.val) : val - other.val;
    return *this;
  }
 
  static unsigned fast_mod(uint64_t x, unsigned m = MOD){
    return unsigned(x % m);
  }
 
  _m_uint& operator*=(const _m_uint &other){
    val = fast_mod(uint64_t(val) * other.val);
    return *this;
  }
 
  _m_uint& operator/=(const _m_uint &other){
    return *this *= other.inv();
  }
 
  friend _m_uint operator+(const _m_uint &a, const _m_uint &b){ return _m_uint(a) += b; }
  friend _m_uint operator-(const _m_uint &a, const _m_uint &b){ return _m_uint(a) -= b; }
  friend _m_uint operator*(const _m_uint &a, const _m_uint &b){ return _m_uint(a) *= b; }
  friend _m_uint operator/(const _m_uint &a, const _m_uint &b){ return _m_uint(a) /= b; }
 
  _m_uint& operator++(){
    val = val == MOD - 1 ? 0 : val + 1;
    return *this;
  }
 
  _m_uint& operator--(){
    val = val == 0 ? MOD - 1 : val - 1;
    return *this;
  }
    
  _m_uint operator++(int){ _m_uint before = *this; ++*this; return before; }
  _m_uint operator--(int){ _m_uint before = *this; --*this; return before; }
      
  _m_uint operator-() const {
    return val == 0 ? 0 : MOD - val;
  }
 
  friend bool operator==(const _m_uint &a, const _m_uint &b) { return a.val == b.val; }
  friend bool operator!=(const _m_uint &a, const _m_uint &b) { return a.val != b.val; }
  friend bool operator<(const _m_uint &a, const _m_uint &b) { return a.val < b.val; }
  friend bool operator>(const _m_uint &a, const _m_uint &b) { return a.val > b.val; }
  friend bool operator<=(const _m_uint &a, const _m_uint &b) { return a.val <= b.val; }
  friend bool operator>=(const _m_uint &a, const _m_uint &b) { return a.val >= b.val; }
 
  static const int SAVE_INV = int(1e6) + 5;
  static _m_uint save_inv[SAVE_INV];
 
  static void prepare_inv(){
    // Make sure MOD is prime, which is necessary for the inverse algorithm below.
    for(int64_t p = 2; p * p <= MOD; p += p % 2 + 1){
      assert(MOD % p != 0);
    } 
      
    save_inv[0] = 0;
    save_inv[1] = 1;
 
    for (int i = 2; i < SAVE_INV; i++){
      save_inv[i] = save_inv[MOD % i] * (MOD - MOD / i);
    }
  }
 
  _m_uint inv() const {
    if(save_inv[1] == 0)  
      prepare_inv();
 
    if(val < SAVE_INV)  
      return save_inv[val];
 
    _m_uint product = 1;
    unsigned v = val;
 
    while(v >= SAVE_INV){
      product *= MOD - MOD / v;
      v = MOD % v;
    }
    return product * save_inv[v];
  }
 
  _m_uint pow(int64_t p) const {
    if(p < 0)  
      return inv().pow(-p);
    _m_uint a = *this, result = 1;
    while(p > 0){
      if(p & 1) 
        result *= a;
      p >>= 1;
      if(p > 0) 
        a *= a;
    }
    return result;
  }
 
  friend ostream& operator<<(ostream &os, const _m_uint &m){
    return os << m.val;
  }
};
 
template<const unsigned &MOD> _m_uint<MOD> _m_uint<MOD>::save_inv[_m_uint<MOD>::SAVE_INV];

const unsigned MOD = unsigned(1e9) + 7;
using mint = _m_uint<MOD>;



vector<mint> factorial, inv_factorial;
 
void prepare(int n){
  factorial = inv_factorial = {1, 1};
 
  factorial.resize(n + 1);
  inv_factorial.resize(n + 1);
  
  for(int i = 2; i <= n; i++)
    factorial[i] = i * factorial[i - 1];

  inv_factorial[n] = 1 / factorial[n];
  for(int i = n - 1; i >= 0; --i)
  	inv_factorial[i] = (i + 1) * inv_factorial[i + 1];
}
 
mint choose(int n, int r){
  if (r < 0 || r > n) return 0;
  return factorial[n] * inv_factorial[r] * inv_factorial[n - r];
}
 
/*

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
  
// sterling numbers of second kind
  
  
mint S[N][K];
for(int i = 0; i <= N; ++i){
  for(int j = 0; j <= K; ++j){
    if(i == 0 && j == 0){
      S[i][j] = 1; 
    }else if(i == 0 || j == 0){
      S[i][j] = 0; 
    }else{
    	S[i][j] = j * S[i-1][j] + S[i-1][j-1];
    }
  }
}


*/



































