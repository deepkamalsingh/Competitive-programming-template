struct LCA {
  int N, timer, LOG; 
  vector< vector<int> > up;
  vector< vector<array<int,2> > > adj;
  vector<int> tin, tout, depth;
 
  void init(int _N) { 
    N = _N ; LOG = log2(N) + 1; 
    adj.resize(N); 
    up.resize(N, vector<int> (LOG));
    tin = tout = depth = vector<int> (N); 
  }
 
  void ae(int x, int y,int w = 1) { // add edge
    adj[x].push_back({y,w}), adj[y].push_back({x,w}); 
  }
 
  void dfs(int v, int p, int w){
    tin[v] = ++timer;
    up[v][0] = p;
    for(int i = 1; i < LOG; i++){
      up[v][i] = up[up[v][i-1]][i-1];
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
	
  int kth_ancestor(int i,int k){
    if(depth[i] < k) return int(-1);
    for(int j = LOG - 1; j >= 0; --j){
      if( (int(1) << j) <= k ){
        k -= (int(1) << j) ; i = up[i][j]; 
      }
    }
    return i;
  }
  
};