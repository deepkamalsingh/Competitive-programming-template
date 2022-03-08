/* 
  * Description :- sweep line algorithm for finite segments.
  * Source :- https://cp-algorithms.com/geometry/intersecting_segments.html
  * Verf :- USACO 2019 US Open Contest, Silver Problem 2.
*/

using F = long double;
using point = complex<F>;

#define X real()
#define Y imag()

const F EPS = 1E-9;

struct seg{
  point p,q;
  int id;
  F get_Y(F x) const {
    if(abs(p.X-q.X) < EPS)
      return p.Y;
    return p.Y+(q.Y-p.Y)*(x-p.X)/(q.X-p.X);
  }
};

bool intersect1d(F L1, F R1, F L2, F R2){
  if(L1 > R1)
    swap(L1,R1);
  if(L2 > R2)
    swap(L2, R2);
  return max(L1,L2) <= min(R1,R2)+EPS;
}

int vec(const point& a, const point& b, const point& c){
  F s = (b.X-a.X)*(c.Y-a.Y)-(b.Y-a.Y)*(c.X-a.X);
  return abs(s) < EPS ? 0 : s > 0 ? +1 : -1;
}

bool intersect(const seg& a, const seg& b){
  return  intersect1d(a.p.X, a.q.X, b.p.X, b.q.X) &&
          intersect1d(a.p.Y, a.q.Y, b.p.Y, b.q.Y) &&
          vec(a.p, a.q, b.p) * vec(a.p, a.q, b.q) <= 0 &&
          vec(b.p, b.q, a.p) * vec(b.p, b.q, a.q) <= 0;
}

bool operator<(const seg& a, const seg& b){
  F x = max(min(a.p.X, a.q.X),min(b.p.X,b.q.X));
  return a.get_Y(x) < b.get_Y(x) - EPS;
}

struct event{
  F x;
  int tp, id;
  event() {}
  event(F x, int tp, int id) : x(x), tp(tp), id(id) {}

  bool operator<(const event& e) const {
    if(abs(x - e.x) > EPS)
      return x < e.x;
    return tp > e.tp;
  }
};

set<seg> s;
vector<set<seg>::iterator> where;

set<seg>::iterator prev(set<seg>::iterator it){
    return it == s.begin() ? s.end() : --it;
}

set<seg>::iterator next(set<seg>::iterator it){
    return ++it;
}

pair<int,int> solve(const vector<seg>& a){
  int n = (int)a.size();
  vector<event> e;
  for(int i = 0; i < n; ++i){
    e.push_back(event(min(a[i].p.X, a[i].q.X), +1, i));
    e.push_back(event(max(a[i].p.X, a[i].q.X), -1, i));
  }
  sort(e.begin(), e.end());
  s.clear();
  where.resize(a.size());
  for(size_t i = 0; i < e.size(); ++i){
    int id = e[i].id;
    if(e[i].tp == +1){
      set<seg>::iterator nxt = s.lower_bound(a[id]), prv = prev(nxt);
      if(nxt != s.end() && intersect(*nxt, a[id]))
        return make_pair(nxt->id, id);
      if(prv != s.end() && intersect(*prv, a[id]))
        return make_pair(prv->id, id);
      where[id] = s.insert(nxt, a[id]);
    }else{
      set<seg>::iterator nxt = next(where[id]), prv = prev(where[id]);
      if(nxt != s.end() && prv != s.end() && intersect(*nxt, *prv))
        return make_pair(prv->id, nxt->id);
      s.erase(where[id]);
    }
  }
  return make_pair(-1, -1);
}


