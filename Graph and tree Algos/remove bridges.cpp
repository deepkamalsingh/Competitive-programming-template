/*
	*Description :- following gives bridges in a graph.
	*Graph may not be connected but graph should be simple for this to work
	*Complexity :- O(E+V);
	*Verification :- https://judge.yosupo.jp/submission/43660
*/
const int MAX_N = 4e5;
vt<int> g[MAX_N], d(MAX_N,0), par(MAX_N,-1),up(MAX_N,0), down(MAX_N,0), dp(MAX_N);
vt<bool> vis(MAX_N,false);
vt<pr<int,int>> get_bridges(int root){
	vt<int> nodes;
	vt<pr<int,int>> ans;
	function<void(int)> dfs=[&](int i){
		for(auto j : g[i]) if(!vis[j]){
			par[j] = i ;
			d[j] = d[i] + 1;
			vis[j] = 1;
			nodes.pb(j); 
			dfs(j);
		}
	};
	vis[root] = true;
	d[root] = 0 ;
	nodes.pb(root);
	dfs(root);
	for(auto i : nodes){
		for(auto j : g[i]){
			if(d[j] > d[i]){
				if(d[j] - d[i] > 1) down[i]++;
			}else if(d[j] < d[i]){
				if(d[i] - d[j] > 1) up[i]++;
			}else{
				assert(false);
			}
		}
		vis[i] = false ;
	}
	function<void(int)> dfs2=[&](int i){
		dp[i] = up[i] - down[i];
		for(auto j : g[i]) if(!vis[j]){
			vis[j] = 1; dfs2(j);
			dp[i] += dp[j];
		}
		if(i != root && dp[i] == 0){
			ans.pb({par[i],i});
		}
	};
	vis[root] = true;
	dfs2(root);
	return ans;
}