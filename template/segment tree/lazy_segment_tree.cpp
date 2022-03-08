/*
  * Description segment tree for mass changes using lazy propagation
  * source: own
  * verify commutivity and distributivity property for changes, assignement ans sum do not follow these property
  * verification :- various
*/

#define CHANGE_HERE_ONLY 1

struct InfoLazy{

#ifdef CHANGE_HERE_ONLY

  // info about lazy value.

#endif

  // comb(x,ELAZY) = x.
  void apply_lazy(const InfoLazy& lazy){

#ifdef CHANGE_HERE_ONLY

    // apply lazy on lazy.

#endif

  }
};

#ifdef CHANGE_HERE_ONLY

constexpr InfoLazy ELAZY = ;

#endif

struct InfoNode{

#ifdef CHANGE_HERE_ONLY

  // comb(x,ENODE) = x.
  // info about node.

#endif

};

#ifdef CHANGE_HERE_ONLY

constexpr InfoNode ENODE = ;

#endif

struct TreeNode{
  int lx, rx;
  InfoNode node;
  // lazy value is applied to this node but not to its children.
  InfoLazy lazy;
  bool is_empty;

  TreeNode(bool flag = false) : is_empty(flag) {} 

  void apply_lazy(const InfoLazy& lazy_){
    // apply lazy_ value on lazy.
    lazy.apply_lazy(lazy_);

#ifdef CHANGE_HERE_ONLY

    // apply lazy value on current node.

#endif      
  }

  friend TreeNode join(const TreeNode& lhs,const TreeNode& rhs){
    
    if(lhs.is_empty)
      return rhs;
    if(rhs.is_empty)
      return lhs;

    TreeNode result;
    assert(lhs.rx == rhs.lx);
    result.lx = lhs.lx;
    result.rx = rhs.rx;

    result.lazy = ELAZY;

#ifdef CHANGE_HERE_ONLY

    // merge the nodes.


#endif 

    return result;
  };
};


struct LazySegmentTree {
  
  int size;
  vector<TreeNode> tree;

  void propogate(int x){
    if(tree[x].rx - tree[x].lx == 1) 
      return;
    tree[x << 1 | 1].apply_lazy(tree[x].lazy);
    tree[x + 1 << 1].apply_lazy(tree[x].lazy);
    tree[x].lazy = ELAZY;
  }

  LazySegmentTree(int n = -1) : size(-1) {
    if(n >= 0)
      init(n);
  }

  void init(int n){
    size = 1;
    while(size < n) 
      size <<= 1;
    tree.resize(size << 1);
    build(vector<InfoNode>{});
  }

  void build(const vector<InfoNode> &initial){
    int size_ = int(initial.size());
    if(size < 0)
      init(size_);
    assert(size >= size_);
    build(0, 0, size, initial, size_);
  }

  void build(int x,int lx,int rx,const vector<InfoNode> &initial,int size_){
    if(rx - lx == 1){
      tree[x].lx = lx, tree[x].rx = rx;
      tree[x].lazy = ELAZY;
      if(x >= size - 1 && x - size + 1 < size_)
        tree[x].node = initial[x - size + 1];
      else
        tree[x].node = ENODE;
    }else{
      int mid = lx + rx >> 1;
      build(x << 1 | 1, lx, mid, initial, size_);
      build(x + 1 << 1, mid, rx, initial, size_);
      tree[x] = join(tree[x << 1 | 1], tree[x + 1 << 1]);
    }
  }

  void update(int l, int r, int x,const InfoLazy& lazy){

    propogate(x);

    if(tree[x].lx >= r || l >= tree[x].rx)
      return;
    
    if(tree[x].lx >= l && tree[x].rx <= r){
      tree[x].apply_lazy(lazy);
      return;
    }

    int mid = tree[x].rx + tree[x].lx >> 1;
    update(l, r, x << 1 | 1, lazy);
    update(l, r, x + 1 << 1, lazy);
    tree[x] = join(tree[x << 1 | 1], tree[x + 1 << 1]);
  }

  // range update on [l,r).
  void update(int l, int r,const InfoLazy& lazy){
    update(l, r, 0, lazy);
  }

  TreeNode query(int l, int r, int x){

    propogate(x);

    if(tree[x].lx >= r || l >= tree[x].rx)
      return TreeNode(true);

    if(tree[x].lx >= l && tree[x].rx <= r)
      return tree[x];
    
    int mid = tree[x].rx + tree[x].lx >> 1;
    return join(query(l, r, x << 1 | 1), query(l, r, x + 1 << 1));
  }

  // range query on [l,r).
  InfoNode query(int l, int r){
    return query(l, r, 0).node;
  }
};