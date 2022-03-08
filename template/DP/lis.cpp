/*
  * source :- cp-algorithms, own modifications to restore subsequence
  * verif :- https://www.codechef.com/viewsolution/40974280 
  * to convert it into non - decreasing simply do d[j-1] <= a[i], verification for this needs to be done
*/

namespace Lis{
  vector<int> lis(vector<int> const& a){
    int n = a.size();
    const int INF = 2e9;
    vector<int> d(n+1, INF), in(n, -1), prev(n, -1);
    d[0] = -INF;

    for(int i = 0; i < n; i++){
      int j = upper_bound(d.begin(), d.end(), a[i]) - d.begin();
      // change d[j-1] < a[i] to d[j-1] <= a[i] if we want longest non-decreasing sequence.
      if(d[j-1] < a[i] && a[i] < d[j]){
        prev[i] = in[j-1];
        d[j] = a[i]; in[j] = i;
      }
    }
    for(int i = n; i >= 0; --i)
      if(d[i] < INF){
        int j = in[i]; 
        vector<int> ans;
        while(j != -1){
          ans.push_back(j); 
          j = prev[j];
        }
        reverse(ans.begin(), ans.end());
        return ans;
      }
  }
}
