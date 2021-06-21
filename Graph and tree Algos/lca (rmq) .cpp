/**
 * Description: 1D range minimum query. Can also do queries 
 	* for any associative operation in $O(1)$ with D\&C
 * Source: KACTL
 * Verification: 
	* https://cses.fi/problemset/stats/1647/
	* http://wcipeg.com/problem/ioi1223
	* https://pastebin.com/ChpniVZL
 * Memory: O(N\log N)
 * Time: O(1)
 * Zero based indexing 
 * gives ans for [l, r]
 */
template<class T> struct RMQ { // floor(log_2(x))
	int level(int x) { 
    return 31 - __builtin_clz(x); 
  }
   
	vector<T> v ; 
  vector<vector<int>> jmp;
	int comb(int a, int b) { // index of min
		return v[a] == v[b] ? min(a,b) : (v[a] < v[b] ? a : b) ; 
  }
   
	void init(const vector<T>& _v) {
		v = _v; 
		jmp = { vector<int> (int(v.size())) }; 
    iota(begin(jmp[0]), end(jmp[0]), 0) ;
		for (int j = 1; (1<<j) <= int(v.size()); ++j) {
			jmp.push_back(vector<int>(int((v).size()) - (1<<j) + 1));
			for(int i = 0; i < int(jmp[j].size()); ++i){
        jmp[j][i] = comb(jmp[j-1][i], jmp[j-1][i + (1<<(j-1))]) ;
      } 
		}
	}
	
	int index(int l, int r) { // get index of min element
		assert(l <= r); 
    int d = level(r-l+1);
		return comb(jmp[d][l], jmp[d][r-(1<<d)+1]); 
  }
  
	T query(int l, int r) { 
    return v[index(l,r)]; 
  }
};
/**
 * Description: Euler Tour LCA.
	* pairwise LCAs.
	* The root points to itself.
	* include RMQ for this
 * Time: O(N\log N) build, O(1) LCA, O(|S|\log |S|) compress
 * Source: USACO, Simon Lindholm (KACTL)
 * Verification: USACO Debug the Bugs
 	* https: ??
 */
struct LCA {
	int N; vector<vector<int>> adj;
	vector<int> depth, pos, par; 
	vector<pair<int,int>> tmp; 
  RMQ<pair<int,int>> rmq;
  
	void init(int _N) { 
    N = _N ; 
    adj.resize(N) ; 
		depth = pos = par = vector<int> (N) ; 
  }
  
	void ae(int x, int y) { 
    adj[x].push_back(y), adj[y].push_back(x); 
  }
  
	void dfs(int x) {
		pos[x] = int(tmp.size()); 
    tmp.emplace_back(depth[x], x) ; 
		for(auto y:adj[x]) if (y != par[x]) {
			depth[y] = depth[par[y] = x] + 1;
      dfs(y);
			tmp.emplace_back(depth[x],x); 
    }
	}
	
	void gen(int R = 0) { 
    par[R] = R; 
    dfs(R); 
    rmq.init(tmp); 
  }
  
	int lca(int u, int v){
		u = pos[u], v = pos[v]; 
    if (u > v) swap(u,v);
		return rmq.query(u,v).second ; 
  }
  
	int dist(int u, int v) {
		return depth[u] + depth[v] - 2 * depth[lca(u,v)]; 
  }
};

