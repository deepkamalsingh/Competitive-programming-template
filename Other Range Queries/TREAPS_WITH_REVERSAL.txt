

/*
 * Treaps Implementation
  * prior is priority which gives heap property
  * key gives BST property
  * size is size of our tree
  * sum is sum of our subtree
  * lazy is lazy value
  * val is value stored at that node
  * rev is bool for reversal or not
 * source:
    https://tanujkhattar.wordpress.com/2016/01/10/treaps-one-tree-to-rule-em-all-part-2/
    https://www.codechef.com/viewsolution/36079099
 * verification:
    https://www.spoj.com/status/HORRIBLE,deepkamal/
    https://www.codechef.com/viewsolution/41633615
*/
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

int Random(){
  return uniform_int_distribution<int>(0,1e9)(rng) ;
}

struct node{
    int prior, size, val, sum, lazy, key; 
    bool rev ;
    node *l, *r;
    node ():l(nullptr) , r(nullptr) , rev(false){}
};
node* newnode(int k,int _val){
    node *ret ; ret = new node();
    ret->key = k ;
    ret->val = ret->sum = _val;
    ret->lazy = 0 ;
    ret->size = 1 ;
    ret->prior = Random() ;
    return ret ;
}
typedef node* pnode;


struct IMPLICIT_TREAP {

  node *tree;
  IMPLICIT_TREAP(): tree (nullptr) { }

  int SZ(pnode t){
    return t ? t->size : 0 ;
  }

  void upd_sz(pnode t){
    if(t){ t->size = SZ(t->l) + 1 + SZ(t->r); }
  }

  void combine(pnode& t,pnode l,pnode r){//combine segtree ranges
    t->sum = 0 ;
    if(l) t->sum += l->sum ; 
    if(r) t->sum += r->sum;
  }

  void propagate(pnode t){
    if(!t or !t->lazy) return ; // here this implementation is for sum so t->lazy != 0
    t->val += t->lazy ; //operation of lazy
    t->sum += t->lazy * SZ(t) ;
    if(t->l) t->l->lazy += t->lazy ; //propagate lazy for t's children
    if(t->r) t->r->lazy += t->lazy ;
    t->lazy = 0;
  }
  void reset(pnode t){
    if(t) t->sum = t->val;//lazy already propagated
  }
  void rev(node* t){ // similar to propogate
    if(!t or t->rev == 0) return ;
    if(t->l) t->l->rev ^= 1;
    if(t->r) t->r->rev ^= 1;
    swap(t->l, t->r);
    t->rev = 0 ;
  }
  void operation(pnode t){//operation of segtree
    if(!t) return ;
    reset(t) ; // node represents single element of array
    rev(t->l) ; rev(t->r) ;
    propagate(t->l) ; propagate(t->r) ;//imp:propagate lazy before combining l,r
    combine(t,t->l,t->r) ; t->sum += t->val ;
  }
  void split(pnode t,pnode &l,pnode &r,int pos,int add = 0){ // add keeps track of the i value
    if(!t){ l = r = NULL ; return ; }
    rev(t) ; propagate(t) ; 
    int curr_pos = add + SZ(t->l);
    if(curr_pos <= pos){//element at pos goes to "l"
      split(t->r, t->r, r, pos, curr_pos+1); l = t;
    }else{ 
      split(t->l, l, t->l, pos, add); r = t;
    }
    upd_sz(t) ; operation(t) ;
  }
  void merge(pnode &t,pnode l,pnode r){//result/left/right array
    rev(l) ; rev(r) ;
    propagate(l) ; propagate(r) ;
    if(!l or !r){
      t = l?l:r;
    }else if(l->prior > r->prior) {
      merge(l->r,l->r,r); t = l;
    }else{
      merge(r->l,l,r->l); t = r;
    }
    upd_sz(t) ; operation(t) ;
  }
  void insert(int pos,int _val){
    pnode r = newnode(pos,_val);
    pnode a, b, c;
    split(tree, a, b, pos-1) ;
    merge(c, a, r);
    merge(tree, c, b);  
  }
  void del(int pos){
    pnode a, b, c;
    split(tree, a, c, pos);
    split(a, a, b, pos-1);
    merge(tree, a, c);
  }
  int get(int pos){
    pnode a, b, c;
    split(tree, a, c, pos) ; split(a, a, b, pos-1) ;
    merge(a, a, b) ; merge(tree, a, c) ;
    return b->val ;
  }
  void range_update(pnode t,int l,int r,int val){ //[l,r]
    pnode a, b, c;
    split(t, b, c, r) ; split(b, a, b, l-1) ;
    b->lazy += val;
    merge(b,a,b) ; merge(t,b,c) ;
  }
  int range_query(pnode t,int l,int r){//[l,r]
    pnode a, b, c;
    split(t,a,c,r) ; split(a,a,b,l-1) ;
    int ans = b->sum ;
    merge(a,a,b) ; merge(t,a,c) ;
    return ans;
  }
  void reverse(pnode t,int l,int r){
    pnode a, b, c;
    split(t, b, c, r); split(b, a, b, l-1);
    b->rev ^= 1;
    merge(b, a, b); merge(t, b, c);
  }
};

