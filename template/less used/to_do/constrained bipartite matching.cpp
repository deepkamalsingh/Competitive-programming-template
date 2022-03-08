/*
	* Derscription :- below.
	* source :- https://codeforces.com/contest/1521/submission/115574965.
	* verf :-
*/

// #include <dinic>

// constrained_bipartite_matching solves the following problem:
// You are given a bipartite graph with edges going from the left side to the right side (there can be multi-edges).
// For each node, you are given constraints in the form of low[node] and high[node], meaning that the number of matches
// at this node must end up between low[node] and high[node].
// Find a subset of the edges to match that satisfies all the low/high constraints, or determine that it's impossible.
// When a solution exists, this can also find the minimum number of matched edges needed in order to solve the
// constraints. Note that this adds an additional log factor to the time complexity due to binary search.
// See also https://cp-algorithms.com/graph/flow_with_demands.html and https://codeforces.com/contest/1240/submission/62062679
struct constrained_bipartite_matching{
	int N,M;
	int source, sink, dummy_source, dummy_sink;
	vector<pair<int,int>> edges;

	constrained_bipartite_matching(int n = 0,int m = 0){
		init(n,m);
	}

	void init(n,m){
		N = n, M = m;
		edges = {};
		source = N + M, sink = N + M + 1;
		dummy_source = N + M + 2, dummy_sink = N + M + 3;
	}

	void add_edge(int a,int b){
		assert(0 <= a && a < N);
		assert(0 <= b && b < M);
		edges.emplace_back(a, N + b);
	}

	pair<int,int> build_graph(const vector<int> &low,const vector<int> &high, int dummy_cap = INF){
		assert(int(low.size()) == N + M && int(high.size()) == N + M);
		graph.init(N + M + 4);
		int left_sum = 0, right_sum = 0;

		for(int i = 0; i < int(edges.size()); ++i)
			graph.add_directional_edge(edges[i].first,edges[i].second,1,i);

		for(int i = 0; i < N + M; ++i)
			if(i < N){
				graph.add_directional_edge(source,i,low[i]);
				graph.add_directional_edge(dummy_source,i,high[i]-low[i]);
				left_sum += low[i];
			}else{
				graph.add_directional_edge(i,sink,low[i]);
				graph.add_directional_edge(i,dummy_sink,high[i]-low[i]);
				right_sum += low[i];
			}

		graph.add_directional_edge(source,dummy_sink,right_sum);
		graph.add_directional_edge(dummy_sink,dummy_source,dummy_cap);
		graph.add_directional_edge(dummy_source,sink,left_sum);

		// Flow paths can move as follows:
    // 1) source -> left -> right -> sink. This helps directly satisfy two low constraints.
    // 2) source -> left -> right -> dummy_sink -> dummy_source -> sink. This satisfies a low constraint on the left
    //      with the help of a high constraint on the right. dummy_source -> sink is limited by left_sum in order to
    //      prevent using more of this than necessary to satisfy left low constraints.
    // 3) source -> dummy_sink -> dummy_source -> left -> right -> sink. This satisfies a low constraint on the
    //      right with the help of a high constraint on the left. dummy_source -> sink is limited by right_sum in
    //      order to prevent using more of this than necessary to satisfy right low constraints.
    // 4) source -> dummy_sink -> dummy_source -> sink. This is a direct path that helps ensure that the total flow
    //      reaches exactly left_sum + right_sum when completed.
    return {left_sum,right_sum};
	}

	int& get_capacity(int from,int to){
		for(auto &e : graph.adj[from])
			if(e.node == to)
				return e.capacity;

		assert(false);
	}

	void add_to_dummy(int change){
		get_capacity(dummy_sink,dummy_source) += change;
	}

	// Returns {success, edge assignment (true for matched edges)}.
	pair<bool,vector<bool>> solve(const vector<int> &low, const vector<int> &high){
		assert(int(low.size()) == N + M && int(high.size()) == N + M);

		for(int i = 0; i < N + M; ++i)
			if(low[i] > high[i])
				return {false,{}};

		pair<int,int> sums = build_graph(low,high);
		int left_sum = sums.first, right_sum = sums.second;
		int total_flow = graph.flow(source,sink);

		if(total_flow != left_sum + right_sum)
			return {false,{}};

		vector<bool> matched(edges.size(),false);

		for(auto &e_list : graph.adj)
			for(auto &e : e_list)
				if(e.id >= 0)
					matched[e.id] = e.capacity == 0;

		return {true,matched};
	}

}