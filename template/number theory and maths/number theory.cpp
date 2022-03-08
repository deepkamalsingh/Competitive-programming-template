/*
	* Description :- basic number theroy.
	* source :- https://codeforces.com/contest/1516/submission/113767955.
	* verf :- various.
*/

namespace NT{

  template<int N> 
  struct sieve{
    array<int, N + 1> spf;
    constexpr sieve(){
      spf.fill(0);
      for(int i = 2; i * i <= N; i++)
        if(spf[i] == 0)
          for(int j = i * i; j <= N; j += i)
            if(spf[j] == 0) 
              spf[j] = i;

      for(int i = 2; i <= N; i++)
        if(spf[i] == 0)
          spf[i] = i;
    }
   
    bool is_prime(int x) const {
      return spf[x] == x;
    }
   
    vector<int> primes() const {
      vector<int> primes;
      for(int i = 1; i <= N; i++)
        if(spf[i] == i)
          primes.push_back(i);

      return primes;
    }
   
    vector<pair<int,int>> prime_factors(int x) const {
      vector<pair<int, int>> factors;
      while(x != 1){
        if(factors.empty() || factors.back().first != spf[x])
          factors.emplace_back(spf[x], 0);
        factors.back().second++;
        x /= spf[x];
      }
      return factors;
    }
    
    int normalize(int x) const {
      int normal = 1;
      while (x != 1) {
        int p = spf[x]; normal *= p;
        while(spf[x] == p) x /= p;
      }
      return normal;
    }
    
    vector<int> divisors(int x) const {
      if(x == 1)  return {1};
      int c = 0, n = x;
      for (; spf[x] == spf[n]; n /= spf[x], c++);
      vector<int> d = divisors(n);
      vector<int> res((c + 1) * d.size());
      for(int i = 0, j = 0, p = 1; i <= c; i++, p *= spf[x]) 
        for(int item : d) 
          res[j++] = p * item;
      return res;
    }
  };

  // divide a by b rounded up
  template<typename T>
  T cdiv(T a,T b){ 
    return a/b + ((a^b) > 0 && a%b); 
  } 

  // divide a by b rounded down
  template<typename T>
  T fdiv(T a,T b){ 
    return a/b - ((a^b) < 0 && a%b); 
  }

  template<typename T>
  T safe_mod(T x,T m){
    x %= m;
    if(x < 0)
      x += m;
    return x;
  }

  template<typename T>
  pair<T,T> inv_gcd(T a,T b){
    a = safe_mod(a, b);
    if(a == 0) 
      return {b, 0};

    T s = b, t = a;
    T m0 = 0, m1 = 1;
      
    while(t){
      T u = s / t;
      s -= t * u, m0 -= m1 * u;
      auto tmp = s;
      s = t, t = tmp, tmp = m0, m0 = m1, m1 = tmp;
    }
   
    if(m0 < 0) 
      m0 += b / s;
    return {s, m0};
  }

  template<typename T> 
  T inv_mod(T x,T m){
    assert(1 <= m);
    auto z = inv_gcd(x, m);
    assert(z.first == 1);
    return z.second;
  }

  template<typename T> 
  T gcd(T a,T b,T& x,T& y){
    if(b == 0){
      x = 1, y = 0;
      return a;
    }
    T x1, y1;
    T d = gcd(b, a % b, x1, y1);
    x = y1;
    y = x1 - y1 * (a / b);
    return d;
  }

  template<typename T> 
  bool find_any_solution(T a,T b,T c,T &x0,T &y0){
    T g = gcd(abs(a), abs(b), x0, y0);
    if(c%g) 
      return false;
    x0 *= c/g;
    y0 *= c/g;
    if(a < 0) 
      x0=(-x0);
    if(b < 0)
     y0=(-y0);
    return true;
  }

  template<typename T>
  T totient(T n){
  	T result = n;
  	for(T i = 2; i * i <= n; ++i){
  		if(n%i == 0){
  			while(n%i == 0)
  				n /= i;
  			result -= result/i;
  		}
  	}
  	if(n > 1)
  		result -= result / n;
  	return result;
  }

  template<int N> 
  array<int,N+1> totient_all(){
  	array<int,N+1> f;
  	f[0] = 0;
  	f[1] = 1;
  	for(int i = 2; i <= N; ++i)
  		f[i] = i - 1;

  	for(int i = 2; i <= N; ++i)
  		for(int j = 2 * i; j <= N; j += i)
  			f[j] -= f[i];

  	return f;
  }

  // Returns a number that is a1 mod m1 and a2 mod m2. Assumes m1 and m2 are relatively prime.
	template<typename T>
	T crt(T a1, T m1, T a2, T m2){
	  T k = (a2 - a1) % m2 * inv_mod(m1, m2) % m2;
	  T result = a1 + k * m1;
	 
	  if(result < 0)
	    result += m1 * m2;
	 
	  assert(0 <= result && result < m1 * m2);
	  assert(result % m1 == a1 && result % m2 == a2);
	  return result;
	}
}