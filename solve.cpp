#include <bits/stdc++.h>
using namespace std;

#define int int64_t //be careful about this 

#define pr pair
#define ar array
#define fr first
#define sc second
#define vt vector
#define pb push_back
#define eb emplace_back
#define lb lower_bound
#define ub upper_bound

#define SZ(x) ((int)(x).size())
#define all(a) (a).begin(),(a).end()
#define allr(a) (a).rbegin(),(a).rend()
#define mem(a,b) memset(a, b, sizeof(a))

template<class A> void rd(vt<A>& v);
template<class T> void rd(T& x){ cin >> x;}
template<class H, class... T> void rd(H& h, T&... t) { rd(h); rd(t...);}
template<class A> void rd(vt<A>& x) { for(auto& a : x) rd(a);}

template<class T> bool ckmin(T& a, const T b) { return b < a ? a = b, 1 : 0;}
template<class T> bool ckmax(T& a, const T b) { return a < b ? a = b, 1 : 0;}

template<typename T>
void __p(T a) {
  cout<<a; 
}
template<typename T, typename F>
void __p(pair<T, F> a) {
  cout<<"{";
  __p(a.first);
  cout<<",";
  __p(a.second);
  cout<<"}\n"; 
}
template<typename T>
void __p(std::vector<T> a) {
  cout<<"{";
  for(auto it=a.begin(); it<a.end(); it++)
    __p(*it),cout<<",}\n"[it+1==a.end()]; 
}
template<typename T, typename ...Arg>
void __p(T a1, Arg ...a) {
  __p(a1);
  __p(a...);
}
template<typename Arg1>
void __f(const char *name, Arg1 &&arg1) {
  cout<<name<<" : ";
  __p(arg1);
  cout<<endl;
}
template<typename Arg1, typename ... Args>
void __f(const char *names, Arg1 &&arg1, Args &&... args) {
  int bracket=0,i=0;
  for(;; i++)
    if(names[i]==','&&bracket==0)
      break;
    else if(names[i]=='(')
      bracket++;
    else if(names[i]==')')
      bracket--;
  const char *comma=names+i;
  cout.write(names,comma-names)<<" : ";
  __p(arg1);
  cout<<" | ";
  __f(comma+1,args...);
}


void setIO(string s = "") {
  ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0); 
  // remove this when size of input is not fixed.
  cin.exceptions(cin.failbit); 
	cout.precision(15);	cout << fixed;
  if(SZ(s)){
  	freopen((s+".in").c_str(),"r",stdin);
  	freopen((s+".out").c_str(),"w",stdout);
  }
}


/*/--------------------------------------------------look below-----------------------------------------------------------------------------------/*/




































void solve(){
	
}

signed main(){
  setIO();
  int t; rd(t);
  while(t--){
  	solve();
  }
}







// tips to avoid bugs.

/*
	* be careful of whats happening you dont want a continue statement to miss imp line of code.
	* be careful when to update what since it might be needed in next segment of code.
	* dont get stuck on one idea.
*/
















