struct DSU {
	int n;
  // root node: -1 * component size
  // otherwise: parent
  vector<int> parent_or_size;

  DSU(int n) : n(n), parent_or_size(n, -1) {}

  int merge(int a, int b) {
    int x = leader(a), y = leader(b);
    if (x == y) return x;
    if (-parent_or_size[x] < -parent_or_size[y]) swap(x, y);
    parent_or_size[x] += parent_or_size[y] ;
    parent_or_size[y] = x ;
    return x ;
  }

  bool same(int a, int b) {
    return leader(a) == leader(b);
  }

  int leader(int a) {
    if (parent_or_size[a] < 0) return a;
    return parent_or_size[a] = leader(parent_or_size[a]);
  }

  int size(int a) {
    return -parent_or_size[leader(a)];
  }
  
  vector<vector<int>> groups() {
  	vector<int> leader_buf(n), group_size(n);
    for(int i = 0; i < n; i++) {
	    leader_buf[i] = leader(i);
      group_size[leader_buf[i]]++;
    }
    vector<vector<int>> result(n);
    for(int i = 0; i < n; i++) {
    	result[i].reserve(group_size[i]);
    }
    for(int i = 0; i < n; i++) {
    	result[leader_buf[i]].push_back(i);
    }
    result.erase(remove_if(result.begin(), result.end(),[&](const auto& v) {return v.empty(); }),result.end());
    return result;
  }
};