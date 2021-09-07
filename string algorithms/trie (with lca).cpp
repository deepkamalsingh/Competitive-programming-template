/*
	* Description :- trie with lca to compare strings.
	* Sources :- https://codeforces.com/contest/1209/submission/60549043.
	* Verification :- to be done.
*/


template<const int SZ,const int ALPHABET>
struct prefix_tree {
	
	static const int LOG = __lg(SZ) + 1;
	
	
	
	struct trie_node {
  	int link[ALPHABET];
  	int ancestor[LOG];
    int what;
    int depth;
 
    trie_node() {
      memset(link, -1, sizeof(link));
      memset(ancestor, -1, sizeof(ancestor));
    }
	};
	
	vector<trie_node> trie;
	
	prefix_tree(){
		trie.emplace_back();
		trie[0].depth = 0;
	}
	
	void create_node(int parent, int c) {
    trie.emplace_back();
    trie.back().what = c;
    trie.back().depth = trie[parent].depth + 1;
    trie.back().ancestor[0] = parent;
 
    for(int k = 0; k + 1 < LOG; k++) {
    	int first = trie.back().ancestor[k];
      trie.back().ancestor[k + 1] = first < 0 ? -1 : trie[first].ancestor[k];
    }
	}
	
	int get_or_create_node(int current, int c) {
    if (trie[current].link[c] < 0) {
      trie[current].link[c] = trie.size();
      create_node(current, c);
    }
 
    return trie[current].link[c];
	}
 
	int insert_str(const string &str) {
		int current = 0;
    for(char c : str){
      current = get_or_create_node(current, c - 'a');
 		}
    return current;
	}
	
	// return whether a is lexographically smaller than b or not.
	bool compare_str(int a, int b) {
  	if(a == b){
    	return false;
 		}
 		
    if(trie[a].depth > trie[b].depth){
    	
    	for(int k = LOG - 1; k >= 0; k--){
    		if(trie[a].depth >= trie[b].depth + (1<<k)){
    			a = trie[a].ancestor[k];
    		}
    	}
    	
    	if(a == b) return false;
    	
    }else if(trie[a].depth < trie[b].depth){
    	
    	for(int k = LOG - 1; k >= 0; k--){
    		if(trie[b].depth >= trie[a].depth + (1<<k)){
    			b = trie[b].ancestor[k];
    		}
    	}
    	if(a == b) return true;
    	
    }
 		
  	for(int k = LOG - 1; k >= 0; k--){
  		if (trie[a].ancestor[k] != trie[b].ancestor[k]) {
    		a = trie[a].ancestor[k];
    		b = trie[b].ancestor[k];
      	assert(trie[a].depth == trie[b].depth);
    	}
  	}
    
 
  	assert(a != b);
  	assert(trie[a].ancestor[0] == trie[b].ancestor[0]);
  	return trie[a].what < trie[b].what;
	}
	
};