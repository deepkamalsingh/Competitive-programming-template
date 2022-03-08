/**
 * Description: Range queries for any associative operation on static array
 * If you get TLE, try declaring everything globally.
 * Time: O(n log n) build, O(1) query
 * Source: Benq
 * Verification: https://www.codechef.com/viewsolution/47401581
 */ 
 
template<class T> struct static_range_query {
	int N;
	const T ID = 1;
	vector<vector<T>> store; // comb(ID,x) = x.
	vector<T> a;
	T comb (T a, T b) { // associative operation.
		return (a * b); 
	} 
	void fill(int l, int r, int ind) {
		if (ind < 0) return;
		int m = (l+r)/2 ;
		T val = ID; 
		for(int i = m-1; i >= l; --i){
			store[i][ind] = val = comb(a[i],val);
		}
		val = ID; 
		for(int i = m; i < r; ++i){
			store[i][ind] = val = comb(val,a[i]);
		}
		fill(l,m,ind-1); 
		fill(m,r,ind-1);
	}
	void init(const vector<T> _a) {
		a = _a;
		for(N = 1; (1<<N) < int(a.size()); ++N);
		store = vector<vector<T>> (1<<N,vector<T>(N,ID));
		while(int(a.size()) < (1<<N)) a.push_back(ID);
		fill(0,(1<<N),N-1);
	}
	T query(int l, int r) {
		if (l == r) return a[l];
		int level = 31 - __builtin_clz(r^l);
		return comb(store[l][level], store[r][level]);
	}
};

