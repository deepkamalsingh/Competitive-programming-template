/**
 * Description: Tarjan's, DFS once to generate
	* strongly connected components in topological order. $a,b$
	* in same component if both $a\to b$ and $b\to a$ exist.
	* Uses less memory than Kosaraju b/c doesn't store reverse edges.
 * Time: O(N+M)
 * Source: KACTL
	* https://github.com/kth-competitive-programming/kactl/blob/master/content/graph/SCC.h
 * Verification: https://cses.fi/problemset/result/1937935/
 * comp[i] gives node it is connected to as part of its SSC, each node of SCC has same value
 * comps is topo sort of graph
*/
struct SCC {
	int N, ti = 0; vector<vector<int>> adj;
	vector<int> disc, comp, st, comps;
	void init(int N_){
		N = N_;
		adj.resize(N), disc.resize(N), comp = vector<int>(N,-1);
	}
	void add_edge(int x, int y){
		adj[x].push_back(y);
	}
	int dfs(int x){
		int low = disc[x] = ++ti; st.push_back(x); // disc[y] != 0 -> in stack
		for(int y : adj[x]) 
			if(comp[y] == -1) 
				low = min(low, disc[y]?:dfs(y));
		if(low == disc[x]){ // make new SCC, pop off stack until you find x
			comps.push_back(x); 
			for(int y = -1; y != x;){
				comp[y = st.back()] = x, st.pop_back();
			}
		}
		return low;
	}
	void gen(){
		for(int i = 0; i < N; ++i)
		 if(!disc[i]) 
		 	dfs(i);
		reverse(begin(comps), end(comps));
	}
};