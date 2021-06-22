
/*
  * Description segment tree for mass changes using lazy propagation
  * source: pashka edu course with very little own modifications
  * verify commutivity and distributivity property for changes, assignement ans sum do not follow these property
  * set ID, NEUTRAL_ELEMENT, NO_OPERATION accordingly.
  * update on interval [l, r) and query val at range [l, r)
  * change x tells that at x this change is done but have to propogate to children
  * verification :- https://codeforces.com/edu/course/2/lesson/5/2/practice/status
*/

template<class T, class H> struct lazy_segment_tree {
  const T ID = , NEUTRAL_ELEMENT = ;
  const H NO_OPERATION = ;
  int size ;
  vector<T> segment_tree;
  vector<H> change;

  void apply_lazy_on_change(H &a, H b){

  }

  T combiner_function(T a, T b){

  }

  void apply_lazy_on_node(T &a, H b){

  }

  void propogate(int x, int lx, int rx){
    if(rx - lx == 1) return ;
    apply_lazy_on_node(segment_tree[2 * x + 1], change[x]);
    apply_lazy_on_node(segment_tree[2 * x + 2], change[x]);
    apply_lazy_on_change(change[2 * x + 1], change[x]);
    apply_lazy_on_change(change[2 * x + 2], change[x]);
    change[x] = NO_OPERATION;
  }

  void init(int n){
    size = 1;
    while(size < n) size *= 2;
    segment_tree.assign(2*size, ID);
    change.assign(2*size, NO_OPERATION);
  }

  void build(const vector<T> &initial){
    int _size = int(initial.size());
    init(_size);
    assert(_size <= size);
    build(0, 0, size, initial, _size);
  }
  void build(int x, int lx, int rx, const vector<T> &initial, int _size){
    if(rx - lx == 1){
      if(x >= size - 1 && x - size + 1 < _size){
        segment_tree[x] = initial[x - size + 1];
      }else{
        segment_tree[x] = ID;
      }
    }else{
      int mid = (lx + rx)/2;
      build(2 * x + 1, lx, mid, initial, _size);
      build(2 * x + 2, mid, rx, initial, _size);
      segment_tree[x] = combiner_function(segment_tree[2 * x + 1], segment_tree[2 * x + 2]);
    }
  }

  void update(int l, int r, int x, int lx, int rx, H value) {
    propogate(x, lx, rx) ;
    if( lx >= r || l >= rx ){
      return;
    }
    if( lx >= l && rx <= r){
      apply_lazy_on_node(segment_tree[x], value);
      apply_lazy_on_change(change[x], value);
      return ;
    }
    int mid = (rx + lx)/2 ;
    update(l, r, 2 * x + 1, lx, mid, value);
    update(l, r, 2 * x + 2, mid, rx, value);
    segment_tree[x] = combiner_function(segment_tree[2 * x + 1], segment_tree[2 * x + 2]) ;
    return ;
  }

  void update(int l, int r, H value) {
    update(l, r, 0, 0, size, value) ; return ;
  }

  T query(int l, int r, int x, int lx, int rx) {
    propogate(x, lx, rx) ;
    if( lx >= r || l >= rx ){
      return NEUTRAL_ELEMENT;
    }
    if( lx >= l && rx <= r){
      return segment_tree[x] ;
    }
    int mid = (rx + lx)/2 ;
    return combiner_function(query(l, r, 2 * x + 1, lx, mid), query(l, r, 2 * x + 2, mid, rx)) ;
  }

  T query(int l, int r) {
    return query(l, r, 0, 0, size) ;
  }
};



