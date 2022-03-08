/*
  * Description :- checks whether some point is in polygon or not.
  * Source :- cp-algorithms.com/geometry/point-in-convex-polygon.html 
  * Verf :- works for either inside(including boundary) or outside(not including boundary). but inside v/s boundary can bug.
*/

// #include<lattice>

namespace InPolygon{
  bool point_in_triangle(const P& a,const P& b,const P&c,const P& p){
    return abs(cross(a,b,c)) == abs(cross(p,a,b)) + abs(cross(p,b,c)) + abs(cross(p,c,a));
  }

  vector<P> seq;
  P transalation;
  // assume points are given in counter-clockwise order.
  void init(const vector<P>& p_){
    vector<P> p = p_;
    int n = p.size();
    int pos = 0;
    for(int i = 0; i < n; ++i)
      if(p[i].y < p[pos].y || (p[i].y == p[pos].y && p[i].x < p[pos].x))
        pos = i;

    rotate(p.begin(),p.begin()+pos,p.end());
    seq.resize(n - 1);
    for(int i = 0; i < n - 1; ++i)
      seq[i] = p[i+1]-p[0];
    transalation = p[0];
    return;
  }

  int query(const P& p_){
    P p = p_ - transalation;
    if(sgn(cross(p,seq[0])) * sgn(cross(p,end(seq)[-1])) == 1)
      return 0;
    // check whether its on first line.
    if(cross(seq[0],p) == 0)
      return euclid(seq[0]) >= euclid(p) && dot(seq[0],p) >= 0 ? 1 : 0;
    // check whether its on last line.
    if(cross(end(seq)[-1],p) == 0)
      return euclid(end(seq)[-1]) >= euclid(p) && dot(end(seq)[-1],p) >= 0 ? 1 : 0;
    int l = 0, r = SZ(seq) - 1;
    while(r - l > 1){
      int mid = (l + r)/2;
      cross(seq[mid],p) >= 0 ? l = mid : r = mid;
    }
    bool tmp = point_in_triangle(seq[l],seq[l+1],P(0,0),p);
    if(!tmp)
      return 0; // outside
    if(cross(p,seq[l],seq[l+1]) == 0)
      return 1; // boundary
    return 2; // inside
  }
};