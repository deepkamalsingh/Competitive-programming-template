/**
 * Description: Euler Tour, LCA,  kth_ancestor
 * source: cp-algorithm, BENQ, own
  * The root points to itself.
  * 0 based indexing
 * Time: O(N * log N) build, O(log N) LCA
 * Verification: 
  * for kth_ancestor : https://cses.fi/problemset/result/1573131/
  * for lca : https://cses.fi/problemset/result/1573158/
  * for both: https://oj.uz/submission/354781
  * for weighted part: https://codeforces.com/contest/609/submission/108079099
 */
struct LCA {
  int N, timer, LOG; 
  vector< vector<int> > up, dis, max_edge;
  vector< vector<array<int,2> > > adj;
  vector<int> tin, tout, depth;
 
  void init(int _N) { 
    N = _N ; LOG = log2(N) + 5; 
    adj.resize(N); 
    up.resize(N, vector<int> (LOG));
    dis.resize(N, vector<int> (LOG));
    max_edge.resize(N, vector<int> (LOG));
    tin = tout = depth = vector<int> (N); 
  }
 
  void ae(int x, int y,int w = 1) { // add edge
    adj[x].push_back({y,w}), adj[y].push_back({x,w}); 
  }
 
  void dfs(int v, int p, int w){
    tin[v] = ++timer;
    up[v][0] = p;
    dis[v][0] = w;
    max_edge[v][0] = w;
    for(int i = 1; i < LOG; i++){
      up[v][i] = up[up[v][i-1]][i-1];
      dis[v][i] = dis[v][i-1] + dis[up[v][i-1]][i-1];
      max_edge[v][i] = max(max_edge[v][i-1],max_edge[up[v][i-1]][i-1]);
    } 
    for(auto [u,w] : adj[v])  if(u != p){
      depth[u] = depth[v] + 1; dfs(u,v,w);
    }
    tout[v] = ++timer;
  }
 
  void gen(int R = 0) { 
    depth[R] = timer = 0;
    dfs(R,R,0); 
  }
 
  bool is_ancestor(int u, int v){
    return tin[u] <= tin[v] && tout[u] >= tout[v];
  }
 
  int lca(int u, int v){
    if(is_ancestor(u,v))  return u;
    if(is_ancestor(v,u))  return v;
    for(int i = LOG - 1; i >= 0; --i) {
      if(!is_ancestor(up[u][i],v)){
        u = up[u][i] ;
      } 
    }
    return up[u][0];
  }
 
  int dist(int u, int v) {
    return depth[u] + depth[v] - 2*depth[lca(u,v)]; 
  }
	
	int weighted_dist(int u,int v){
		int temp = lca(u,v);
		int x1 = kth_ancestor_weighted_dist(u,depth[u] - depth[temp]);
		int x2 = kth_ancestor_weighted_dist(v,depth[v] - depth[temp]);
		return x1 + x2 ;
	}
	
	int weighted_max_edge(int u,int v){
		int temp = lca(u,v);
		int x1 = kth_ancestor_weighted_max_edge(u,depth[u] - depth[temp]);
		int x2 = kth_ancestor_weighted_max_edge(v,depth[v] - depth[temp]);
		return max(x1, x2) ;
	}
  int kth_ancestor(int i,int k){
    if(depth[i] < k) return int(-1);
    for(int j = LOG - 1; j >= 0; --j){
      if( (int(1) << j) <= k ){
        k -= (int(1) << j) ; i = up[i][j]; 
      }
    }
    return i;
  }
  int kth_ancestor_weighted_dist(int i,int k){
  	if(depth[i] < k) return int(-1);
  	int ans = 0;
    for(int j = LOG - 1; j >= 0; --j){
      if( (int(1) << j) <= k ){
        k -= (int(1) << j);
        ans += dis[i][j];
        i = up[i][j]; 
      }
    }
    return ans ;
  }
  int kth_ancestor_weighted_max_edge(int i,int k){
  	if(depth[i] < k) return int(-1);
  	int ans = 0;
    for(int j = LOG - 1; j >= 0; --j){
      if( (int(1) << j) <= k ){
        k -= (int(1) << j) ;
        ckmax(ans,max_edge[i][j]);
        i = up[i][j]; 
      }
    }
    return ans;
  }
};

























