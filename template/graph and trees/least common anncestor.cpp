/*
 * Description: Euler Tour LCA.
	* The root points to itself.
 * Time: O(N log N) build, O(1) LCA
 * Source: https://github.com/bqi343/USACO/blob/master/Implementations/content/graphs%20(12)/Trees%20(10)/LCArmq%20(10.2).h
 * Verification: https://judge.yosupo.jp/submission/51135
*/

// #include <RMQ>

struct LCA {
	int N;
	vector<vector<int>> adj;
	vector<int> depth, pos, par;
	vector<pair<int,int>> tmp;
	RMQ<pair<int,int>> rmq;
	
	void init(int _N){
		N = _N;
		adj.resize(N);
		depth = pos = par = vector<int> (N, 0);
		iota(par.begin(),par.end(),0);
	}
	
	void add_edge(int u,int v){
		adj[u].push_back(v);
		adj[v].push_back(u);
	}
	
	void dfs(int x){
		pos[x] = int(tmp.size());
		tmp.emplace_back(depth[x], x);
		for(auto y : adj[x]) 
			if(y != par[x]){
				depth[y] = depth[par[y] = x] + 1;
				dfs(y);
				tmp.emplace_back(depth[x],x);
			}
	}
	
	void gen(int R = 0){
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