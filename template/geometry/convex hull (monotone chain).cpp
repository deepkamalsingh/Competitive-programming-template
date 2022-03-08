/*
	* Description :- convex hull of points using andrew's algorithm.
	* Sources :- USACO guide.
	* Verf :- open.kattis.com/problems/convexhull
*/

// #include<lattice>

namespace Hull{
  // return convex_hull in counter-clockwise order.
  vector<P> convex_hull(vector<P> points){
    vector<P> hull;
    sort(points.begin(), points.end(), [&](const auto& l,const auto& r){
      return l.x == r.x ? l.y < r.y : l.x < r.x;
    });
    points.erase(unique(points.begin(), points.end()), points.end());
    int n = points.size();
    if(n < 3)
      return hull = points;

    // lower hull
    for(int i = 0; i < n; ++i){
      // if the new point a right is formed we remove the latest point.
      // we remove points that are collinear as well.
      while(int(hull.size()) > 1 && cross(hull[hull.size()-2],hull.back(),points[i]) <= 0)
        hull.pop_back();
      hull.push_back(points[i]);
    }

    // upper hull
    auto lower_hull_length = hull.size();
    for(int i = n-2; i >= 0; --i){
      // we can only remove a point if there are still points left in the upper hull
      while(hull.size() > lower_hull_length && cross(hull[hull.size()-2],hull.back(),points[i]) <= 0)
        hull.pop_back();
      hull.push_back(points[i]);
    }
    hull.pop_back();
    return hull;
  }
}

