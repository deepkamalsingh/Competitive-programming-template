



/*
	Description :- Trie data structure with addition and search , Only add functionality , rest you should code according to problem statement.
	source      :- https://cp-algorithms.com/string/aho_corasick.html
	verifcation :- https://www.spoj.com/status/SUBXOR,deepkamal/
*/


const int K = ??? ;

struct Vertex {
    int next[K], count[K];
    bool leaf = false;
    Vertex(){ 
    	fill(begin(next), end(next), -1);
    	fill(begin(count), end(count), 0);
    }
};

struct TRIE {
	vector<Vertex> Trie;
	TRIE(){ Trie.emplace_back(); }
	void add_string(string const& s) {
    int v = 0;
    for(auto ch : s){
        int c = ch - '0';
        if (Trie[v].next[c] == -1) {
            Trie[v].next[c] = Trie.size();
            Trie.emplace_back();
        }
        Trie[v].count[c]++;
        v = Trie[v].next[c];
    }
    Trie[v].leaf = true ;
	}
};







==============================================================================================================================================================================================
#include <bits/stdc++.h>
 
using namespace std ;
 
#define int int64_t 
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
  if(sz(s)){
    freopen((s+".in").c_str(),"r",stdin);
    freopen((s+".out").c_str(),"w",stdout);
  }
}
 
/*
	Description :- Trie data structure with addition and search , Only add functionality , rest you should code according to problem statement.
	source      :- https://cp-algorithms.com/string/aho_corasick.html
	verifcation :- https://www.spoj.com/status/SUBXOR,deepkamal/
		       https://codeforces.com/contest/706/submission/109148201

*/
 
 
const int K = 2, BIT = 32 ;
 
struct Vertex {
    int next[K], count[K];
    bool leaf = false;
    Vertex(){ 
    	fill(begin(next), end(next), -1);
    	fill(begin(count), end(count), 0);
    }
};
 
struct TRIE {
	vector<Vertex> Trie;
	TRIE(){ Trie.emplace_back(); }
	void add_string(string const& s) {
    int v = 0;
    for(auto ch : s){
        int c = ch - '0';
        if (Trie[v].next[c] == -1) {
            Trie[v].next[c] = Trie.size();
            Trie.emplace_back();
        }
        Trie[v].count[c]++;
        v = Trie[v].next[c];
    }
    Trie[v].leaf = true ;
	}
	void remove_string(string const& s){
    int v = 0;
    for(auto ch : s){
        int c = ch - '0';
        assert(Trie[v].next[c] != -1) ;
        Trie[v].count[c]--;
        v = Trie[v].next[c];
    }
    Trie[v].leaf = true ;
	}
	int query(string s){
		assert(sz(s) == BIT);
		int v = 0, ans = 0;
		f(i,0,BIT){
			int si = s[i] - '0';
			if(Trie[v].count[!si] > 0){
				ans += (int(1) << (BIT - i - 1)) ;
				v = Trie[v].next[!si] ;
			}else{
				v = Trie[v].next[si] ;
			}
		}
		return ans ;
	}
};
string str(int x){
	string ans;
	f(i,0,BIT){
		if(x & (int(1) << i)) ans.pb('1');
		else ans.pb('0');
	}
	reverse(all(ans));
	return ans;
}
signed main(){
  setIO() ;
  int q; rd(q);
  TRIE trie;
  trie.add_string(str(0));
  while(q--){
  	char c; int x; rd(c,x);
  	if(c == '+'){
  		trie.add_string(str(x));
  	}else if(c == '-'){
  		trie.remove_string(str(x));
  	}else{
  		cout << trie.query(str(x)) << endl ;
  	}
  }
}