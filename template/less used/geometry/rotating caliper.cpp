/*
	* Description :- rotating calipers.
	* Sources :- https://ideone.com/TjjhBR.
	* Verf :- kattis robert hood.
*/

// #include<lattice>

// points can be in any order.
int max_distance(vector<P> p){
  int n = p.size();
  if(n < 2)
    return 0;
  if(n == 2)
    return euclid(p[0],p[1]);
  int k = 1;
  while(abs(cross(p[n-1],p[0],p[k+1])) > abs(cross(p[n-1],p[0],p[k])))
    ++k;
  int ans = 0;
  // i and j are here antipodal.
  for(int i = 0, j = k; i <= k && j < n;){
    ans = max(ans, euclid(p[i],p[j]));
    while(j + 1 < n && abs(cross(p[i],p[i+1],p[j+1])) > abs(cross(p[i],p[i+1],p[j]))){
      ++j;
      ans = max(ans, euclid(p[i],p[j]));
    }
    ++i;
  }
  return ans;
}