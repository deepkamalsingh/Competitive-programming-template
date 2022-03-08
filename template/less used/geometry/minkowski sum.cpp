/*
	* Description :- minkowski sum of two polygons in O(n+m).
	* Source :- https://cp-algorithms.com/geometry/minkowski.html.
	* Verf :- https://codeforces.com/contest/87/submission/141292620
*/

// #include <lattice>

namespace Minkowski{
  void reorder(vector<P>& a){
    size_t pos = 0;
    for(size_t i = 0; i < a.size(); ++i)
      if(a[i].y < a[pos].y || (a[i].y == a[pos].y && a[i].x < a[pos].x))
        pos = i;
    rotate(a.begin(),a.begin()+pos,a.end());
    return;
  }

  vector<P> sum(vector<P> a,vector<P> b){
    reorder(a);
    reorder(b);
    a.push_back(a[0]);
    a.push_back(a[1]);
    b.push_back(b[0]);
    b.push_back(b[1]);
    vector<P> ret;
    size_t i = 0, j = 0;
    while(i < a.size() - 2 || j < b.size() - 2){
      ret.push_back(a[i]+b[j]);
      int val = cross(a[i+1]-a[i],b[j+1]-b[j]);
      if(val >= 0)
        ++i;
      if(val <= 0)
        ++j;
    }
    return ret;
  }
}