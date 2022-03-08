/*
	*Description :- tarjan algorithm for BCC
		*BCC[u] gives biconnected component u is in. 
		*BBC is for edges not vertices
		*A common trick to solve problems is to make a graph 
		 consisting of (BBC u is part of, u) as edges 
		*Remember to have MAXN to O(N + M)
	*Verification :- https://cses.fi/problemset/result/1928707/
		
*/
 
const int MAXN = 250000 ;
 
struct TARJAN {
	int N;
	vector<vector<int>> adj;
	vector<vector<int>> bcc;
	vector<int> in,low;
	int bccnum = 0;
	int t = 0;
	stack<pair<int, int> > s;
	bool visited[MAXN];
	
	void init(int _N){
		N = _N;
		in.resize(MAXN);
		low.resize(MAXN);
		adj.resize(MAXN);
		bcc.resize(MAXN);
	}
	void ae(int u,int v){
		adj[u].pb(v);
		adj[v].pb(u);
	}
	
	void dfs(int n, int p=-1) {
		visited[n] = true;
		low[n] = in[n] = t++;
		for (int v : adj[n]) if (v != p) {
			if (!visited[v]) {
				s.emplace(v, n);
				dfs(v, n);
				low[n] = min(low[n], low[v]);
				if (low[v] >= in[n]) {
					while (true) {
						auto p = s.top();
						s.pop();
						int a = p.first, b = p.second;
						if (bcc[a].empty() || bcc[a].back() != bccnum)
							bcc[a].push_back(bccnum);
						if (bcc[b].empty() || bcc[b].back() != bccnum)
							bcc[b].push_back(bccnum);
						if (a == v && b == n) break;
					}
					++bccnum;
				}
			}
			else if (in[v] < in[n]) {
				low[n] = min(low[n], in[v]);
				s.emplace(v, n);
			}
		}
	}
 
	void tarjan() {
		for (int i = 0; i < N; i++) {
			if (!visited[i])
				dfs(i);
		}
	}
 
	bool biconnected(int u, int v) {
		for (int c : bcc[u]) {
			if (binary_search(bcc[v].begin(), bcc[v].end(), c))
				return true;
		}
		return false;
	}
};








































/*=========================================================================================================================================================================================*/


/*

// tarjan_bcc.cpp
// Eric K. Zhang; Dec. 21, 2017

#include <bits/stdc++.h>
using namespace std;

#define MAXN 1000

namespace tarjan {
	int N;
	vector<int> adj[MAXN];
	vector<int> bcc[MAXN];
	int bccnum = 0;
	int in[MAXN], low[MAXN], t = 0;
	stack<pair<int, int> > s;
	bool visited[MAXN];

	void dfs(int n, int p=-1) {
		visited[n] = true;
		low[n] = in[n] = t++;
		for (int v : adj[n]) if (v != p) {
			if (!visited[v]) {
				s.emplace(v, n);
				dfs(v, n);
				low[n] = min(low[n], low[v]);
				if (low[v] >= in[n]) {
					while (true) {
						auto p = s.top();
						s.pop();
						int a = p.first, b = p.second;
						if (bcc[a].empty() || bcc[a].back() != bccnum)
							bcc[a].push_back(bccnum);
						if (bcc[b].empty() || bcc[b].back() != bccnum)
							bcc[b].push_back(bccnum);
						if (a == v && b == n) break;
					}
					++bccnum;
				}
			}
			else if (in[v] < in[n]) {
				low[n] = min(low[n], in[v]);
				s.emplace(v, n);
			}
		}
	}

	void tarjan() {
		for (int i = 0; i < N; i++) {
			if (!visited[i])
				dfs(i);
		}
	}

	bool biconnected(int u, int v) {
		for (int c : bcc[u]) {
			if (binary_search(bcc[v].begin(), bcc[v].end(), c))
				return true;
		}
		return false;
	}
}

int main() {
	tarjan::N = 9;
	vector<pair<int, int> > edges = {
		{0, 1}, {1, 2}, {2, 3}, {3, 1},
		{1, 4}, {4, 5}, {5, 0}, {0, 6},
		{6, 7}, {7, 8}, {8, 6}
	};
	for (auto p : edges) {
		tarjan::adj[p.first].push_back(p.second);
		tarjan::adj[p.second].push_back(p.first);
	}

	tarjan::tarjan();

	for (int i = 0; i < tarjan::bccnum; i++) {
		cout << "BCC #" << i + 1 << ":";
		for (int j = 0; j < tarjan::N; j++) {
			auto& v = tarjan::bcc[j];
			if (find(v.begin(), v.end(), i) != v.end()) {
				cout << ' ' << j;
			}
		}
		cout << endl;
	}
	return 0;
}

----------------------------------------------------------------------------------------------------------------------------------------------------------

// Description:
// B -> stores the nodes in a bcc
// bcc[u] -> which bcc u is in.
// cmpno -> number of bcc's
// to just get bridges call get_bridge
// https://codeforces.com/contest/732/submission/55833415
struct BCC{
    #define N 400005
    vector<int> tree[N], g[N], B[N];
    int U[N], V[N], temp[N], bcc[N], ind[N], T, cmpno, m, n;
    bitset<N> vis, bridge;
    vector<int> Q[N];
    void init(int _n){ n = _n, cmpno = 0, T = 0, m = 0; }
    void reset(int n){
        fr(i, 1, n){
            g[i].clear(), tree[i].clear(), B[i].clear();
            ind[i] = 0;
        }
        bridge.reset();
    }
    int adj(int u,int e){ return U[e] == u ? V[e] : U[e]; }
    void addedge(int u,int v){
        U[m] = u, V[m] = v;
        g[u].pb(m), g[v].pb(m);
        m++;
    }
    void get_bridges(){
        fr(i, 1, n)
            if(!vis[i])
                dfs1(i, -1);
        vis.reset();
    }
    void go(){
        get_bridges();
        fr(i, 1, n)
            if(!vis[i]){
                cmpno++; dfs2(i);
            }
        vis.reset();
    }
    int dfs1(int u,int e){
        vis[u] = 1;
        temp[u] = T++;
        int t = temp[u];
        for(int id: g[u]){
            int v = adj(u, id);
            if(!vis[v]) t = min(t, dfs1(v, id));
            else if(id != e) t = min(t, temp[v]);
        }
        if(t == temp[u] && e != -1) bridge[e] = 1;
        return t;
    }
    void dfs2(int u){
        int cur_cmp = cmpno;
        Q[cur_cmp].pb(u);
        bcc[u] = cur_cmp;
        B[cur_cmp].pb(u);
        vis[u] = 1;
        while(Q[cur_cmp].size() != ind[cur_cmp])
        {
            int u = Q[cur_cmp][ind[cur_cmp]];
            ind[cur_cmp]++;
            for(int e: g[u])
            {
                int v = adj(u, e);
                if(vis[v]) continue;
                if(bridge[e])
                {
                    cmpno++;
                    tree[cur_cmp].pb(cmpno);
                    tree[cmpno].pb(cur_cmp);
                    dfs2(v);
                }
                else
                {
                    Q[cur_cmp].pb(v);
                    vis[v] = 1;
                    bcc[v] = cur_cmp;
                    B[cur_cmp].pb(v);
                }
            }
        }
    }
    #undef N
}B; */