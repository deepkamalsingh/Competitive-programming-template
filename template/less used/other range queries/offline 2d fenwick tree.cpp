/**
 * Description: point update and rectangle sum with offline 2D BIT. 
	* For each of the points to be updated, x in (0,SZ) and y != 0.
	* This doesn't require knowing the queries beforehand
	* but updates should be known
 * Time: O(N * log^2 N)
 * Memory: O(N * log N)
 * Source: https://github.com/bqi343/USACO/blob/master/Implementations/content/data-structures/2D%20Range%20Queries%20(15.2)/BIT2DOff%20(15.2).h
 * Verification: to be done by me.
 	* https://dmoj.ca/submission/3659229
 * practice problems :-
	* https://dmoj.ca/problem/occ19g4
 	* http://www.usaco.org/index.php?page=viewproblem2&cpid=722 (753 ms)
 	* http://www.usaco.org/index.php?page=viewproblem2&cpid=601 (679 ms)
 */

template<class T, int SZ> struct offline_2d_binary_indexed_tree { 
	bool mode = 0; // mode = 1 -> initialized
	vector<pair<int,int>> todo; // locations of updates to process
	int cnt[SZ], st[SZ];
	vector<int> val; vector<T> bit; // store all BITs in single vector
	void init() { 
		assert(!mode); mode = 1;
		int lst[SZ]; 
		for(int i = 0; i < SZ; ++i) lst[i] = cnt[i] = 0;
		sort(todo.begin(),todo.end(),[&](const auto &a, const auto &b) { 
			return a.second < b.second; 
		});
		for(auto t : todo){
			for (int x = t.first; x < SZ; x += x&-x){ 
				if (lst[x] != t.second){
					lst[x] = t.second, cnt[x]++;
				}
			}
		}
		int sum = 0; 
		for(int i = 0; i < SZ; ++i) lst[i] = 0, st[i] = (sum += cnt[i]);
		val.resize(sum); 
		bit.resize(sum); 
		reverse(todo.begin(),todo.end());
		for(auto t : todo){
			for (int x = t.first; x < SZ; x += x&-x){ 
				if (lst[x] != t.second){
					lst[x] = t.second, val[--st[x]] = t.second;
				}
			}
		}
	}
	int rank(int y, int l, int r) {
		return upper_bound(begin(val)+l,begin(val)+r,y)-begin(val)-l; 
	}
	void UPD(int x, int y, T t) {
		for (y = rank(y,st[x],st[x]+cnt[x]); y <= cnt[x]; y += y&-y){
			bit[st[x]+y-1] += t; 
		}
	}
	void upd(int x, int y, T t) { 
		if (!mode) todo.push_back({x,y});
		else{
			for(;x<SZ;x+=x&-x) UPD(x,y,t); 
		}
	}
	int QUERY(int x, int y) { 
		T res = 0;
		for (y = rank(y,st[x],st[x]+cnt[x]); y; y -= y&-y){
			res += bit[st[x]+y-1];
		}
		return res; 
	}
	T query(int x, int y) { 
		assert(mode);
		T res = 0; 
		for (;x;x-=x&-x){
			res += QUERY(x,y);
		}
		return res; 
	}
	T query(int xl, int xr, int yl, int yr) { 
		return query(xr,yr) - query(xl-1,yr) - query(xr,yl-1) + query(xl-1,yl-1);
	}
};
