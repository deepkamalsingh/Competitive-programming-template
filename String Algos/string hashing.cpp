/**
 * Description: Polynomial hash for substrings with two bases.
 * Source:
  * BENQ, own modifications
	* KACTL
	* https://codeforces.com/contest/1207/submission/59309672
 * Verification: https://codeforces.com/contest/835/submission/102412420
 */
#define int int64_t // this is imp
template<int MOD> struct mint {
  static const int mod = MOD ;
  int v; explicit operator int() const { return v; } 
  mint() { v = 0; }
  mint(long long _v) { v = int((-MOD < _v && _v < MOD) ? _v : _v % MOD);
    if (v < 0) v += MOD; }
  friend bool operator==(const mint& a, const mint& b) { 
    return a.v == b.v; }
  friend bool operator!=(const mint& a, const mint& b) { 
    return !(a == b); }
  friend bool operator<(const mint& a, const mint& b) { 
    return a.v < b.v; }
   
  mint& operator+=(const mint& m) { 
    if ((v += m.v) >= MOD) v -= MOD; 
    return *this; }
  mint& operator-=(const mint& m) { 
    if ((v -= m.v) < 0) v += MOD; 
    return *this; }
  mint& operator*=(const mint& m) { 
    v = int((long long)v*m.v%MOD); return *this; }
  mint& operator/=(const mint& m) { return (*this) *= inv(m); }
  friend mint power(mint a, long long p) {
    mint ans = 1; assert(p >= 0);
    for (; p; p /= 2, a *= a) if (p&1) ans *= a;
    return ans; }
  friend mint inv(const mint& a) { assert(a.v != 0); 
    return power(a,MOD-2); }
    
  mint operator-() const { return mint(-v); }
  mint& operator++() { return *this += 1; }
  mint& operator--() { return *this -= 1; }
  friend mint operator+(mint a, const mint& b) { return a += b; }
  friend mint operator-(mint a, const mint& b) { return a -= b; }
  friend mint operator*(mint a, const mint& b) { return a *= b; }
  friend mint operator/(mint a, const mint& b) { return a /= b; }
  
  friend ostream& operator<<(ostream &stream, const mint &m) {
  	return stream << m.v;}
  friend istream& operator>>(istream &stream, mint &m) {
    return stream >> m.v;}
};
const int MOD = 1e9 + 9 ;
typedef mint<MOD> mi; 

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
uniform_int_distribution<int> BDIST(0.1*MOD,0.9*MOD);
const array<int,2> __base = {BDIST(rng), BDIST(rng)};
const array<mi,2> base = {__base[0], __base[1]};

  
vector<array<mi,2>> pows = {{1,1}};
struct HashRange {
	 string S; 
   vector< array<mi,2> > cum = {{0,0}};
	 void add(char c) { 
     S += c; 
     cum.push_back({base[0] * cum.back()[0] + c, base[1] * cum.back()[1] + c}); 
   }
	 void add(string s) { 
     for(auto c:s) add(c); 
   }
	 void extend(int len) { 
     while ((int)(pows.size()) <= len) {
       pows.push_back({base[0] * pows.back()[0], base[1] * pows.back()[1]});
     } 
   }
	 array<mi,2> hash(int l, int r) { // 0 based indexing
     int len = r+1-l; extend(len);
		 return {cum[r+1][0] - pows[len][0] * cum[l][0],  cum[r+1][1] - pows[len][1] * cum[l][1]}; 
   }
};










/*
  old version
// 
//   Description: Polynomial hash for substrings with two bases.
//   Source:
//   BENQ, own modifications
// 	 KACTL
// 	 https://codeforces.com/contest/1207/submission/59309672
//   Verification: https://codeforces.com/contest/835/submission/102412420
//  
#define int int64_t // this is imp
const int MOD = 1e9 + 9 ;
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
uniform_int_distribution<int> BDIST(0.1*MOD,0.9*MOD);
const array<int,2> base = {BDIST(rng), BDIST(rng)};
 
vector<array<int,2>> pows = {{1,1}};
struct HashRange {
	string S; 
  vector< array<int,2> > cum = {{0,0}};
	void add(char c) { 
    S += c; 
    cum.push_back( { (base[0] * cum.back()[0] + c )%MOD, (base[1] * cum.back()[1] + c )%MOD } ); 
  }
	void add(string s) { 
    for(auto c:s) add(c); 
  }
	void extend(int len) { 
    while ((int)(pows.size()) <= len) {
      pows.push_back({ (base[0] * pows.back()[0])%MOD, (base[1] * pows.back()[1])%MOD });
    } 
  }
	array<int,2> hash(int l, int r) { // 0 based indexing
    int len = r+1-l; extend(len);
		return { ((cum[r+1][0] - pows[len][0] * cum[l][0])%MOD + MOD)%MOD,  ((cum[r+1][1] - pows[len][1] * cum[l][1])%MOD + MOD)%MOD }; 
  }
};

*/