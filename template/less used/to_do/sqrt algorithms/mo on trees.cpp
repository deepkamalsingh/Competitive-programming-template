#include <bits/stdc++.h>
 
using namespace std ;
 
#define int int64_t //be careful about this 
#define endl "\n"
#define f(i,a,b) for(int i=int(a);i<int(b);++i)
 
#define pr pair
#define ar array
#define fr first
#define sc second
#define vt vector
#define pb push_back
#define eb emplace_back
#define LB lower_bound  
#define UB upper_bound
#define PQ priority_queue
 
#define sz(x) ((int)(x).size())
#define all(a) (a).begin(),(a).end()
#define allr(a) (a).rbegin(),(a).rend()
#define mem(a,b) memset(a, b, sizeof(a))
 
template<class A> void rd(vt<A>& v);
template<class T> void rd(T& x){ cin >> x; }
template<class H, class... T> void rd(H& h, T&... t) { rd(h) ; rd(t...) ;}
template<class A> void rd(vt<A>& x) { for(auto& a : x) rd(a) ;}
 
template<class T> bool ckmin(T& a, const T& b) { return b < a ? a = b, 1 : 0; }
template<class T> bool ckmax(T& a, const T& b) { return a < b ? a = b, 1 : 0; }
 
template<typename T>
void __p(T a) {
  cout<<a; 
}
template<typename T, typename F>
void __p(pair<T, F> a) {
  cout<<"{";
  __p(a.first);
  cout<<",";
  __p(a.second);
  cout<<"}\n"; 
}
template<typename T>
void __p(std::vector<T> a) {
  cout<<"{";
  for(auto it=a.begin(); it<a.end(); it++)
    __p(*it),cout<<",}\n"[it+1==a.end()]; 
}
template<typename T, typename ...Arg>
void __p(T a1, Arg ...a) {
  __p(a1);
  __p(a...);
}
template<typename Arg1>
void __f(const char *name, Arg1 &&arg1) {
  cout<<name<<" : ";
  __p(arg1);
  cout<<endl;
}
template<typename Arg1, typename ... Args>
void __f(const char *names, Arg1 &&arg1, Args &&... args) {
  int bracket=0,i=0;
  for(;; i++)
    if(names[i]==','&&bracket==0)
      break;
    else if(names[i]=='(')
      bracket++;
    else if(names[i]==')')
      bracket--;
  const char *comma=names+i;
  cout.write(names,comma-names)<<" : ";
  __p(arg1);
  cout<<" | ";
  __f(comma+1,args...);
}
 
void setIO(string s = "") {
  ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0); 
  cin.exceptions(cin.failbit); 
	cout.precision(15);	cout << fixed;
  #ifdef ONLINE_JUDGE
  if(sz(s)){
  	freopen((s+".in").c_str(),"r",stdin);
  	freopen((s+".out").c_str(),"w",stdout);
  }
  #define __f(...) 0
  #endif
}
struct LCA {
  int N, timer = 0, LOG ; 
  vector< vector<int> > up, dis, max_edge ;
  vector< vector<array<int,2> > > adj ;
  vector<int> tin, tout, depth ;
 
  void init(int _N) { 
    N = _N ; LOG = log2(N) + 5 ; 
    adj.resize(N) ; 
    up.resize(N, vector<int> (LOG)) ;
    dis.resize(N, vector<int> (LOG)) ;
    max_edge.resize(N, vector<int> (LOG)) ;
    tin = tout = depth = vector<int> (N) ; 
  }
 
  void ae(int x, int y,int w = 1) { // add edge
    adj[x].push_back({y,w}), adj[y].push_back({x,w}); 
  }
 
  void dfs(int v, int p, int w){
    tin[v] = ++timer;
    up[v][0] = p;
    dis[v][0] = w ;
    max_edge[v][0] = w ;
    for(int i = 1; i < LOG; i++){
      up[v][i] = up[up[v][i-1]][i-1] ;
      dis[v][i] = dis[v][i-1] + dis[up[v][i-1]][i-1] ;
      max_edge[v][i] = max(max_edge[v][i-1],max_edge[up[v][i-1]][i-1]) ;
    } 
    for(auto arr:adj[v]){
    	int u = arr[0], w = arr[1];
    	if(u != p){
      	depth[u] = depth[v] + 1 ; dfs(u,v,w) ;
      }
    }
    tout[v] = ++timer;
  }
 
  void gen(int R = 0) { 
    depth[R] = 0 ;
    dfs(R,R,0); 
  }
 
  bool is_ancestor(int u, int v){
    return tin[u] <= tin[v] && tout[u] >= tout[v];
  }
 
  int lca(int u, int v){
    if( is_ancestor(u,v) )  return u;
    if( is_ancestor(v,u) )  return v;
    for(int i=LOG-1;i>=0;--i) {
      if( !is_ancestor(up[u][i],v) ){
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
    if(depth[i] < k) return int(-1) ;
    for(int j = LOG - 1; j >= 0; --j){
      if( (int(1) << j) <= k ){
        k -= (int(1) << j) ; i = up[i][j] ; 
      }
    }
    return i ;
  }
  int kth_ancestor_weighted_dist(int i,int k){
  	if(depth[i] < k) return int(-1) ;
  	int ans = 0 ;
    for(int j = LOG - 1; j >= 0; --j){
      if( (int(1) << j) <= k ){
        k -= (int(1) << j) ;
        ans += dis[i][j] ;
        i = up[i][j] ; 
      }
    }
    return ans ;
  }
  int kth_ancestor_weighted_max_edge(int i,int k){
  	if(depth[i] < k) return int(-1) ;
  	int ans = 0 ;
    for(int j = LOG - 1; j >= 0; --j){
      if( (int(1) << j) <= k ){
        k -= (int(1) << j) ;
        ckmax(ans,max_edge[i][j]) ;
        i = up[i][j] ; 
      }
    }
    return ans ;
  }
};
 
 
struct compress_1d_co_ordinates {
	vector<int> values;
  void add(int x){
  	values.push_back(x);
  }
  void gen(){
  	sort(values.begin(),values.end());
  	values.erase(unique(values.begin(),values.end()),values.end());
  }
  int get(int x){
  	int j = lower_bound(values.begin(),values.end(),x) - values.begin();
  	assert(values[j] == x); return j;
  }
}compress;
 
signed main(){
  setIO() ;
  int N,M; rd(N,M);
  vt<int> a(N);
  f(i,0,N){
  	rd(a[i]);
  	compress.add(a[i]);
  }
  compress.gen();
  for(auto& i : a) i = compress.get(i);
  
  vt<int> g[N];
  LCA tree;
  tree.init(N);
  f(_,0,N-1){
  	int u,v; rd(u,v); --u,--v;
  	g[u].pb(v);
  	g[v].pb(u);
  	tree.ae(u,v);
  }
  
  tree.gen();
  
  vt<int> ST(N), EN(N), A(2*N);
  int timer = 1;
  
  function<void(int,int)> dfs = [&](int i,int p){
  	ST[i] = timer++; A[--ST[i]] = i;
  	for(auto j : g[i]) if(j != p) dfs(j,i);
  	EN[i] = timer++; A[--EN[i]] = i;
  };
  dfs(0,0);
  
  
  vt<ar<int,4>> queries;
  vt<int> output(M);
  f(i,0,M){
  	int u,v; rd(u,v); --u,--v;
  	if(ST[u] > ST[v]) swap(u,v);
  	int p = tree.lca(u,v);
  	if(p == u){
  		queries.pb({ST[u],ST[v],-1,i});
  	}else{
  		queries.pb({EN[u],ST[v],ST[p],i});
  	}
  }
  
  int B = 1; // block size.
  while(B*B <= M) ++B;
  B = max(int(1),N/B);
  
  sort(all(queries),[&](const auto &X,const auto &Y){
  	if((X[0]/B) == (Y[0]/B)){
  		return ((X[0]/B)&1) ? X[1] < Y[1] : X[1] > Y[1] ;
  	}else{
  		return (X[0]/B) < (Y[0]/B) ;
  	}	
  });
  
  vt<int> count_value(N,0), count_index(N,0);
  
  
  int ans = 0;
  
  auto add_value = [&](int x) -> void {
  	if(count_value[x] == 0) ++ans;
  	++count_value[x];
  	return;
  };
  
  auto rem_value = [&](int x) -> void {
  	if(count_value[x] == 1) --ans;
  	--count_value[x];
  	return;
  };
  
  auto add_index = [&](int i) -> void {
  	if(count_index[i] == 0){
  		add_value(a[i]);
  	}else{
  		assert(count_index[i] == 1);
  		rem_value(a[i]);
  	}
  	++count_index[i];
  	return;
  };
  
  auto rem_index = [&](int i) -> void {
  	if(count_index[i] == 2){
  		add_value(a[i]);
  	}else{
  		assert(count_index[i] == 1);
  		rem_value(a[i]);
  	}
  	--count_index[i];
  	return;
  };
  
  int L = 0, R = -1;
  
  for(auto [l,r,x,id]:queries){
  	while(R < r) add_index(A[++R]);
    while(L > l) add_index(A[--L]);
    while(R > r) rem_index(A[R--]);
    while(L < l) rem_index(A[L++]);
    if(x != -1){
    	add_index(A[x]);
    }	
    output[id] = ans;
    if(x != -1){
    	rem_index(A[x]);
    }
  }
  for(auto i : output) cout << i << endl;
  
  return 0;
}
 