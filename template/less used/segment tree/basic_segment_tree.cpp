/*
  *	Description :- SEGMENT tree using recursive call.
  *	Point update range queries.
  *	the operation should be associative ie ((A o B) o C) == (A o (B o C)).
  * 0-based indexing.
  * set ID, NEUTRAL_ELEMENT and combiner_function functions accordingly.
  * set value at position p the segment is [lx,rx)
  * combiner_function(ID,b) = b
  * query is answered on [lx,rx)
  verification :- https://cses.fi/problemset/result/2169286/
*/

template<class T> 
struct ST {
  public:
    const T ID = 0, NEUTRAL_ELEMENT = 0;
    // comb(ID,a) = a.
    T combiner_function(T a, T b){
      return a + b;
    }
    
    int size;
    vector<T> segment_tree;
    void init(int n){
      size = 1;
      while(size < n) size *= 2;
      segment_tree.resize(2*size);
      build(0, 0, size);
    }
    
    void build(int x, int lx, int rx){
      if(rx - lx == 1){
        segment_tree[x] = ID;
      }else{
        int mid = (lx + rx)/2;
        build(2 * x + 1, lx, mid);
        build(2 * x + 2, mid, rx);
        segment_tree[x] = combiner_function(segment_tree[2 * x + 1], segment_tree[2 * x + 2]);
      }
    }
    
    void update(int pos, T value, int x, int lx, int rx){
      if( rx - lx == 1 ){
        segment_tree[x] = value;	return;
      }
      int mid = (rx + lx)/2 ;
      if(pos < mid){
        update(pos, value, 2 * x + 1, lx, mid);
      }else{
        update(pos, value, 2 * x + 2, mid, rx);
      }
      segment_tree[x] = combiner_function(segment_tree[2 * x + 1], segment_tree[2 * x + 2]);
    }
		
		// update value at pos p.
    void update(int pos, T value) {
      update(pos, value, 0, 0, size);
    }
    
    // query on [lx,rx).
    T query(int l, int r, int x, int lx, int rx) {
      if( lx >= r || l >= rx ){
        return NEUTRAL_ELEMENT ;
      }
      if( lx >= l && rx <= r){
        return segment_tree[x] ;
      }
      int mid = (rx + lx)/2;
      return  combiner_function(query(l, r, 2 * x + 1, lx, mid), query(l, r, 2 * x + 2, mid, rx)) ;
    }
    
    T query(int l, int r) {
      return query(l, r, 0, 0, size) ;
    }
};