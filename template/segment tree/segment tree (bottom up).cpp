/*
 * description :- normal segment tree with bottom up approach.
 * source :- https://codeforces.com/blog/entry/18051
 * verification :- https://cses.fi/problemset/result/2318580/
 * query in done on interval [l, r].
 * 0 - based indexing.
*/

template<class T> 
struct BasicSegmentTree { 
  const T ID =  0;
  T comb(T a, T b){// comb(ID,b) = b
    return a + b;
  }
  int n; vector<T> seg;
  void init(int _n){
    n = _n; seg.assign(2 * n,ID);
  }
  void pull(int p){
    seg[p] = comb(seg[2 * p], seg[2 * p + 1]);
  }
  void upd(int p, T val){ // update val at position p
    seg[p += n] = val;
    for(p /= 2; p; p /= 2) pull(p);
  }
  T query(int l, int r){ // query on interval [l, r]
    T ra = ID, rb = ID;
    for(l += n, r += n+1; l < r; l /= 2, r /= 2){
      if(l&1) ra = comb(ra,seg[l++]);
      if(r&1) rb = comb(seg[--r],rb);
    }
    return comb(ra,rb);
  }
};