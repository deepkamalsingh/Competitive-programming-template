/*
	* decription :- find both the centroids of a tree (if exists).
	* source :- https://codeforces.com/contest/1406/submission/92589305
	* verification :- https://cses.fi/problemset/result/2386147/
*/
 

 
vector<int> find_centroids(int N, const vector<vector<int>> adj)  {
	vector<int> sz(N);
	function<void(int,int)> dfs = [&](int i,int p){
		sz[i] = 1;
		for(auto j : adj[i]) if(j != p){
			dfs(j,i); sz[i] += sz[j];
		}
	};
  dfs(0,-1);
  assert(sz[0] == N);
  int now = 0, parent = -1;
	bool found;
  // Repeatedly move to the subtree that is at least half of the tree, if such a subtree exists.
  do{
  	found = false;
		for(auto j : adj[now]){
			if(j != parent && 2 * sz[j] >= N){
				parent = now;
				now = j;
				found = true;
				break;
			}
		}
  } while(found);
  if(2 * sz[now] == N) return {now, parent};
  return {now};
}