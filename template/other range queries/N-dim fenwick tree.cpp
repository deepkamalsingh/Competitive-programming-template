/**
 * Description: range sum queries and point updates for D dimensions
 * Source: https://codeforces.com/blog/entry/64914
 * Verification: SPOJ matsum
 * Usage: BIT<int,10,10> gives 2D BIT
 * Time: O((log N)^D)
 * 1-based indexing
 * answer is given for [l,r]
 * here delta is added.
 */

template <class T, int ...Ns> 
struct BIT{
	T val = 0;
	void upd(T v){ val += v; }
	T query(){ return val; }
};

template <class T, int N, int... Ns> 
struct BIT<T, N, Ns...> {
	BIT<T,Ns...> bit[N+1];
	template<typename... Args> 
	void upd(int pos, Args... args){ 
		assert(pos > 0);
		for(; pos <= N; pos += pos&-pos) 
			bit[pos].upd(args...); 
	}
	template<typename... Args> 
	T sum(int r, Args... args){
		T res = 0; 
		for(; r; r -= r&-r) 
			res += bit[r].query(args...); 
		return res; 
	}
	template<typename... Args>
	T query(int l, int r, Args... args){ 
		return sum(r,args...) - sum(l-1,args...); 
	}
}; 



