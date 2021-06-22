/*
	description :- static_range_minimum_query, uses divide and conquer
	Time :- O(1) query with O(N log N) preprocessing.
	Sources :- https://github.com/bqi343/USACO/blob/master/Implementations/content/data-structures/Static%20Range%20Queries%20(9.1)/RMQ%20(9.1).h
	verification :- https://judge.yosupo.jp/submission/51130
*/

template<class T> struct static_range_minimum_query {
	
	int level(int x) {
		return 31 - __builtin_clz(x);
	}
	
	vector<T> v;
	vector<vector<int>> jmp;
	
	int comb(int a, int b){
		return v[a] == v[b] ? min(a,b) : (v[a] < v[b] ? a : b);
	}
	
	void init(const vector<T> & _v){
		v = _v; 
		jmp = {vector<int> (int(_v.size()))};
		iota(begin(jmp[0]),end(jmp[0]),0);
		for(int j = 1; (1 << j) <= int(_v.size()); ++j){
			jmp.push_back(vector<int> (int(_v.size()) - (1 << j) + 1));
			for(int i = 0; i < int(jmp[j].size()); ++i){
				jmp[j][i] = comb(jmp[j-1][i], jmp[j-1][i + (1 << (j - 1))]);
			}
		}	
	}
	
	int index(int l, int r){
		assert(l <= r);
		int d = level(r - l + 1);
		return comb(jmp[d][l], jmp[d][r - (1 << d) + 1]);
	}
	
	T query(int l, int r){
		return v[index(l,r)];
	}
	
};


/*
 * Description: Euler Tour LCA.
	* The root points to itself.
 * Time: O(N log N) build, O(1) LCA
 * Source: https://github.com/bqi343/USACO/blob/master/Implementations/content/graphs%20(12)/Trees%20(10)/LCArmq%20(10.2).h
 * Verification: https://judge.yosupo.jp/submission/51135
*/
 
 
struct lowest_common_ancestor {
	int N;
	vector<vector<int>> adj;
	vector<int> depth, pos, par;
	vector<pair<int,int>> tmp;
	static_range_minimum_query<pair<int,int>> rmq;
	
	void init(int _N){
		N = _N;
		adj.resize(N);
		depth = pos = par = vector<int> (N);
	}
	
	void add_edge(int u,int v){
		adj[u].push_back(v);
		adj[v].push_back(u);
	}
	
	void dfs(int x){
		pos[x] = int(tmp.size());
		tmp.emplace_back(depth[x], x);
		for(auto y : adj[x]) if(y != par[x]){
			depth[y] = depth[par[y] = x] + 1;
			dfs(y);
			tmp.emplace_back(depth[x],x);
		}
	}
	
	void gen(int R = 0){
		par[R] = R;
		dfs(R);
		rmq.init(tmp);
	}
	
	int lca(int u, int v){
		u = pos[u], v = pos[v];
		if(u > v) swap(u,v);
		return rmq.query(u,v).second;
	}	
	
	int dist(int u, int v){
		return depth[u] + depth[v] - 2 * depth[lca(u,v)];
	}

};