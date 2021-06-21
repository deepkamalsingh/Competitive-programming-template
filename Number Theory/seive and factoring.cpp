/*
	* Description :- sieve and factoring.
	* source :- https://codeforces.com/contest/1516/submission/113767955.
	* verification :- https://cses.fi/problemset/result/2360665/
*/



template <int N> struct sieve {
	array<int, N + 1> spf;
	constexpr sieve() {
		spf.fill(0);
		for (int i = 2; i * i <= N; i++) {
			if (spf[i] == 0) {
				for (int j = i * i; j <= N; j += i) {
					if (spf[j] == 0) spf[j] = i;
				}
			}
		}
		for (int i = 2; i <= N; i++) {
			if (spf[i] == 0) {
				spf[i] = i;
			}
		}
	}
 
	bool is_prime(int x) const {
		return spf[x] == x;
	}
 
	vector<int> primes() const {
		vector<int> primes;
		for (int i = 1; i <= N; i++) {
			if (spf[i] == i) {
				primes.push_back(i);
			}
		}
		return primes;
	}
 
	vector<pair<int, int>> prime_factors(int x) const {
		vector<pair<int, int>> factors;
		while (x != 1) {
			if (factors.empty() || factors.back().first != spf[x]) {
				factors.emplace_back(spf[x], 0);
			}
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
		if (x == 1)	return {1};
		int c = 0, n = x;
		for (; spf[x] == spf[n]; n /= spf[x], c++);
		vector<int> d = divisors(n);
		vector<int> res((c + 1) * d.size());
		for (int i = 0, j = 0, p = 1; i <= c; i++, p *= spf[x]) {
			for (int item : d) {
				res[j++] = p * item;
			}
		}
		return res;
	}
};