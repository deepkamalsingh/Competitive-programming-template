/*
  * Description :- monotonic convex hull trick.
  * Source :- https://codeforces.com/blog/entry/63823.
  * Verf :- F = false works where as F = true is also correct.
  * Verf :- ABC 228 H.
*/

// F = true means queries are in arbitary order else they are in non-increasing order.
// add(m,c) has m in non-increasing order.
// return max value for m*x+c.

template<bool F>
struct monotonic_cht{
  static int floor_div(int a,int b){
    return a/b-((a^b)<0&&a%b);
  }

  struct line{
    int m,c;
    int eval(int x){
      return m*x+c;
    }
    int isect(const line& l){
      return floor_div(c-l.c,l.m-m);
    }
  };

  deque<line> dq;

  void init(){
    dq.clear();
  }

  void add(int m,int c){
    line cur = {m,c};
    if(dq.size() >= 1 && dq.front().m == m){
      if(dq.front().c >= c)
        return;
      dq.pop_front();
    }
    while(dq.size() >= 2 && cur.isect(dq[0]) >= dq[0].isect(dq[1]))
      dq.pop_front();
    dq.push_front(cur);
  }

  int query(int x){
    if(F){
      assert(!dq.empty());
      if(dq.size() == 1)
        return dq[0].eval(x);
      int lo = 0, hi = dq.size() - 1;
      while(hi - lo > 1){
        int mid = (hi + lo)/2;
        dq[mid].isect(dq[mid+1]) < x ? lo = mid : hi = mid;
      }
      return max(dq[lo].eval(x),dq[lo+1].eval(x));
    }else{
      while(dq.size() >= 2 && end(dq)[-1].eval(x) <= end(dq)[-2].eval(x))
        dq.pop_back();
      return dq.back().eval(x);
    }
  }
};