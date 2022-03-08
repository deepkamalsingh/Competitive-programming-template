/*
	description :- static_range_minimum_query, uses divide and conquer
	Time :- O(1) query with O(N log N) preprocessing.
	Sources :- https://github.com/bqi343/USACO/blob/master/Implementations/content/data-structures/Static%20Range%20Queries%20(9.1)/RMQ%20(9.1).h
	verification :- https://judge.yosupo.jp/submission/58893
*/

template<class T> 
struct RMQ {
	static int level(int x){
		return 31 - __builtin_clz(x);
	}
	
	vector<T> v;
	vector<vector<int>> jmp;
	
	int comb(int a, int b){
		return v[a] == v[b] ? min(a,b) : (v[a] < v[b] ? a : b);
	}
	
	void init(const vector<T> & v_){
		v = v_; 
		jmp = {vector<int> (int(v_.size()))};
		iota(jmp[0].begin(),jmp[0].end(),0);
		for(int j = 1; (1 << j) <= int(v_.size()); ++j){
			jmp.push_back(vector<int> (int(v_.size()) - (1 << j) + 1));
			for(int i = 0; i < int(jmp[j].size()); ++i)
				jmp[j][i] = comb(jmp[j-1][i], jmp[j-1][i + (1 << (j - 1))]);
		}	
	}
	
	int index(int l, int r){
		assert(l <= r);
		int d = level(r - l + 1);
		return comb(jmp[d][l], jmp[d][r-(1<<d)+1]);
	}
	
	T query(int l, int r){
		return v[index(l,r)];
	}
};



















