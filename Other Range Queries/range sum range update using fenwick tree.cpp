/**
 * Description: $D$-dimensional range increment and sum query with $2^D$ BITs, case $D=1$
 * Source: https://www.geeksforgeeks.org/binary-indexed-tree-range-update-range-queries/
 * 1-based indexing
 * Verification: https://www.spoj.com/status/HORRIBLE,deepkamal/
 * Time: O(\log N)
 */
 
template <class T, int ...Ns> struct BIT {
	T val = 0; void upd(T v) { val += v; }
	T query() { return val; }
};

template <class T, int N, int... Ns> struct BIT<T, N, Ns...> {
	BIT<T,Ns...> bit[N+1];
	template<typename... Args> void upd(int pos, Args... args) { assert(pos > 0);
		for (; pos<=N; pos+=pos&-pos) bit[pos].upd(args...); }
	template<typename... Args> T sum(int r, Args... args) {
		T res=0; for (;r;r-=r&-r) res += bit[r].query(args...); 
		return res; }
	template<typename... Args> T query(int l, int r, Args... 
		args) { return sum(r,args...)-sum(l-1,args...); }
}; 

template<class T, int SZ> struct BITrange {
	BIT<T,SZ> bit[2];
	
	void upd(int hi, T val) { 
		bit[1].upd(1,val), bit[1].upd(hi+1,-val); 
		bit[0].upd(hi+1,hi*val); 
	}
	
	void upd(int lo,int hi,T val){
		upd(lo-1,-val),upd(hi,val);
	}
	
	T sum(int x) { 
		return bit[1].sum(x) * x + bit[0].sum(x); 
	} 
	
	T query(int x, int y) { 
		return sum(y) - sum(x-1); 
	}
}; 