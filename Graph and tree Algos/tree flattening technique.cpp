/*
	Description :- 
		* st maps the nodes to their respective position in euler tour array
  	* its like asking whats the position of this node in our array, so its st[i] only
    * subtree size is en[i] - st[i] +1 .
    * below code deals with subtree queries.
    * to deal with path queries :-
    	* en[i] = timer++;
    	* the path b/w (u,v) (gives ST[u] <= ST[v]) is 
    		* if(lca(u,v) == u) [ST[u],ST[v]] in A.
    		* else it is [EN(u), ST(v)] + [ST(P), ST(P)] in A.
    		* here only those nodes which appear once are considered.
    		* array A[--EN[i]] = A[--ST[i]] = i; 
        * verification :- https://www.spoj.com/status/COT2,deepkamal/
    * source :-  https://codeforces.com/blog/entry/43230 (path queries).
    * another blog :- https://codeforces.com/blog/entry/78564 
*/ 
const int MAXN = 2e5 + 7;
vector<int> g[MAXN], st(MAXN), en(MAXN), preorder;
int timer ;
void dfs(int i, int p){
  preorder.push_back(i) ;
  st[i] = timer++ ;
  for(auto j:g[i]) if(j!=p){
    dfs(j, i);
  }
  en[i] = timer - 1 ;
}