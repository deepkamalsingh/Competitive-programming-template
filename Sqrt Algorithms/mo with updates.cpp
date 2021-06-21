// see https://codeforces.com/blog/entry/87356
// https://codeforces.com/blog/entry/72690

#include <bits/stdc++.h>

using namespace std ;

//#define int int64_t //be careful about this 
#define endl "\n"
#define f(i,a,b) for(int i=int(a);i<int(b);++i)

#define pr pair
#define ar array
#define fr first
#define sc second
#define vt vector
#define pb push_back
#define LB lower_bound  
#define UB upper_bound
#define PQ priority_queue

#define sz(x) ((int)(x).size())
#define all(a) (a).begin(),(a).end()
#define allr(a) (a).rbegin(),(a).rend()
#define mem0(a) memset(a, 0, sizeof(a))
#define mem1(a) memset(a, -1, sizeof(a))

template<class A> void rd(vt<A>& v);
template<class T> void rd(T& x){ cin >> x; }
template<class H, class... T> void rd(H& h, T&... t) { rd(h) ; rd(t...) ;}
template<class A> void rd(vt<A>& x) { for(auto& a : x) rd(a) ;}

template<class T> bool ckmin(T& a, const T& b) { return b < a ? a = b, 1 : 0; }
template<class T> bool ckmax(T& a, const T& b) { return a < b ? a = b, 1 : 0; }

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
  cin.exceptions(cin.failbit); 
	cout.precision(15);	cout << fixed;
  #ifdef ONLINE_JUDGE
  if(sz(s)){
  	freopen((s+".in").c_str(),"r",stdin);
  	freopen((s+".out").c_str(),"w",stdout);
  }
  #endif
}
const int N = 1e5 + 7;
const int S = 2714; //(2*n*n)^(1/3)
struct query {
	int t, l, r, k, i;
};
signed main(){
  setIO() ;
  int n, m; rd(n,m);
  vt<int> a(n); rd(a);
  vt<query> q;
  vt<ar<int,3>> upd; // this stoans previous and next element at index p
  f(_,0,m){
  	int t; rd(t);
  	if(t == 1){
  		int l,r,k; rd(l,r,k); --l,--r;
  		int temp = sz(q);
  		q.pb({sz(upd), l, r, k, temp});
  	}else{
  		int p,x; rd(p,x); --p;
  		upd.pb({p,a[p],x});
  		a[p] = x;
  	}
  }
  for(int i = sz(upd) - 1; i >= 0; --i){
   	a[upd[i][0]] = upd[i][1];// a[position] = previuos value before applying this operation 
  }
  sort(all(q),[&](auto &x,auto &y){
    if(x.t/S != y.t/S)	return x.t < y.t;
    if(x.l/S != y.l/S)	return x.l < y.l;
    if((x.l/S) & 1)	return x.r < y.r;
    return x.r > y.r; 
  });
  
  /*
    above one is faster so use that but this is also possible
    sort(all(q),[&](auto &x,auto &y){
     if(x.l/S != y.l/S)	return x.l < y.l;
     if(x.r/S != y.r/S)	return x.r < y.r;
     return x.t < y.t; 
    });
  





  */
  vt<int> cnt(N); // holds frequency of i
  vt<int> ord(N); // holds frequency array in sorted way by using bound
  // it stoans 8 8 8 5 5 5 3 3 1 1  in the following way.
  vt<ar<int,2>> bound(N,{N,0});
  bound[0] = {0, N-1};
  int L = 0, R = -1, T = 0; // T is number of updates done
  auto add = [&](int x){// add element with value x, ord is changed as 3 3 2 1 -> 3 3 3 1
  	int c = cnt[x];
  	++ord[bound[c][0]]; 
		bound[c + 1][1] = bound[c][0]; 
		if(bound[c+1][0] == N) bound[c+1][0] = bound[c + 1][1];
		if(bound[c][0] == bound[c][1]){
			bound[c][0] = N;
		}else{
			bound[c][0]++;
		}
		++cnt[x];
  };
  auto rem = [&](int x){// remove element with value x,	ord is changed as 3 3 2 1 -> 3 2 2 1
  	int c = cnt[x];
  	--ord[bound[c][1]];
  	if(bound[c-1][0] == N) bound[c-1][1] = bound[c][1];
  	bound[c-1][0] = bound[c][1];
  	if(bound[c][0] == bound[c][1]) bound[c][0] = N;
  	--bound[c][1];
  	--cnt[x]; 
  };
  auto apply=[&](int i,int flag){// flag tells we are going forward or backward in queries
  	int p = upd[i][0];
  	int x = upd[i][flag + 1];
  	if(L <= p && p <= R){// if it affects us then make changes in ord and bound
  		rem(a[p]);
  		a[p] = x;
  		add(a[p]);
  	}
  	a[p] = x;
  };
  vt<int> out(sz(q));
  for(auto qq : q){
  	int t = qq.t, l = qq.l, r = qq.r, k = qq.k;
  	while(T < t) apply(T++, 1);
    while(T > t) apply(--T, 0);
    while(R < r) add(a[++R]);
    while(L > l) add(a[--L]);
    while(R > r) rem(a[R--]);
    while(L < l) rem(a[L++]);
    
    int ans = N;
    for(int i = 0, j = 0, sum = 0; i < N && ord[i] > 0; i = bound[ord[i]][1] + 1){
    	// i is first pointer and j is second pointer
    	// find j st we cover at least k frequencies
    	// sum stores current count of frequencies elements 
      while(j < N && ord[j] > 0 && sum < k) {
        sum += bound[ord[j]][1] - bound[ord[j]][0] + 1;
        j = bound[ord[j]][1] + 1;
      }
      if (sum >= k) ans = min(ans, ord[i] - ord[j - 1]);
      sum -= bound[ord[i]][1] - bound[ord[i]][0] + 1;
    }
    out[qq.i] = (ans == N ? -1 : ans) ; 
  } 
  for(auto i : out) cout << i << endl ;
}
 