/*
	* description :- palindromic tree for a string which is genralized version of kmp for palindromes.
	* indexing of palindromic tree starts from 1.
	* source :- http://adilet.org/blog/palindromic-tree/.
	* verification :- https://www.spoj.com/status/NUMOFPAL,deepkamal/
*/

template<int MAX_N,int ALPHABET>
struct palindromice_tree {
	
	static const int INF = 1e9;
	
	struct node {
		// the next node which stores c + palindrome + c
  	array<int,ALPHABET> next;
  	// length of the current palindrome
  	int length;
  	// maximum proper suffix of the current palindrome which is also a palindrome.
  	int suffix_link; 
  	// how many proper suffix of our palindrome are also palindrome.
  	int chain_length;
  	node(){
  		next.fill(-INF);
  		length = chain_length = suffix_link = -INF;
  	}
	};

	// our string
	string s; 
	// our palindromic tree
	node tree[MAX_N]; 
	// total number of nodes
	int total_nodes;           
	// maximum suffix palindrome of present string.
	int max_suffix;	
	
	palindromice_tree() {
		// node 1 - root with length -1, node 2 - root with length 0
    tree[1].length = -1, tree[1].suffix_link = 1, tree[1].chain_length = 0;
    tree[2].length = 0, tree[2].suffix_link = 1, tree[2].chain_length = 0;
    total_nodes = 2; 
    max_suffix = 2;
	}
	
	bool add_char(char _c) {
		s.push_back(_c);
		int pos = int(s.size()) - 1;
		
  	int cur_suffix = max_suffix, cur_length = 0;
  	int c = s[pos] - 'a';

  	while(true){
      cur_length = tree[cur_suffix].length;
      if(pos - 1 - cur_length >= 0 && s[pos - 1 - cur_length] == s[pos]){
      	break;  
      } 
      cur_suffix = tree[cur_suffix].suffix_link;
  	}       
  	
  	if(tree[cur_suffix].next[c] > 0){  
      max_suffix = tree[cur_suffix].next[c];
      return false;
  	}

  	int now = ++total_nodes;
  	
  	max_suffix = now;
  	tree[now].length = tree[cur_suffix].length + 2;
  	tree[cur_suffix].next[c] = now;
  
  	if(tree[now].length == 1){
    	tree[now].suffix_link = 2;
    	tree[now].chain_length = 1;
    	return true;
  	}

  	while(true){
    	cur_suffix = tree[cur_suffix].suffix_link;
    	cur_length = tree[cur_suffix].length;
    	if(pos - 1 - cur_length >= 0 && s[pos - 1 - cur_length] == s[pos]){
        tree[now].suffix_link = tree[cur_suffix].next[c];
        break;
    	}       
  	}           

  	tree[now].chain_length = 1 + tree[tree[now].suffix_link].chain_length;

  	return true;
	}

	
};