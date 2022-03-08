/*
 * Description: 1D range minimum query. Can also do queries 
 	* for any associative operation in $O(1)$ with D\&C
 * Source: KACTL, BENQ
 * Verification: 
	* https://cses.fi/problemset/result/1755689/
 * Memory: O(N\log N)
 * Time: O(1)
 * Zero based indexing 
 * gives ans for [l, r]
 */
 
template<class T> struct RMQ { // floor(log_2(x))
	int level(int x) { 
    return 31 - __builtin_clz(x); 
  } 
	vector<T> v; vector<vector<int> > jmp;
	int comb(int a, int b) { // index of min
		return v[a]==v[b] ? min(a,b) : (v[a]<v[b] ? a : b) ; 
  } 
	void init(const vector<T> & _v) {
		v = _v; jmp = { vector<int> ((int)((v).size())) } ; 
    iota(begin(jmp[0]), end(jmp[0]), 0) ;
		for (int j = 1; (1<<j) <= (int)((v).size()); ++j) {
			jmp.push_back(vector<int>((int)((v).size())-(1<<j)+1));
			for(int i=0; i < (int)((jmp[j]).size()) ; ++i){
        jmp[j][i] = comb(jmp[j-1][i], jmp[j-1][i+(1<<(j-1))]) ;
      } 
		}
	}
	int index(int l, int r) { // get index of min element
		assert(l <= r); 
    int d = level(r-l+1);
		return comb(jmp[d][l], jmp[d][r-(1<<d)+1]); 
  }
	T query(int l, int r) { 
    return v[index(l,r)]; 
  }
};

/*Description:
	* builds the suffix array in O(n * log n) time with lcp query in O(1) .
	*what we get is for string s = "ababba"
   i  lcp sa string
	 0	0		6		""
	 1  0		5		a
	 2  1		0		ababba
	 3  2		2		abba
	 4  0		4		ba
	 5  2		1		babba
	 6  1		3		bba
 	*verification:  https://codeforces.com/edu/course/2/lesson/2/5/practice/contest/269656/submission/108806008
 	* dont put any symbol less than '$' in string 
 	* put '+' instead
*/
struct SUFFIX_ARRAY{
	vt<int> P, LCP, WHERE;
	RMQ<int> rmq;
	void count_sort(vt<int> &p,vt<int> &c){
		int n = sz(p);
		vt<int> cnt(n,0);
		for(auto i : p){
			cnt[c[i]]++;
		}
		vt<int> pos(n,0), new_p(n);
		pos[0] = 0;
		f(i,1,n) pos[i] = pos[i-1] + cnt[i-1];
		for(auto i : p){
			int val = c[i] ;
			new_p[pos[val]] = i ;
			pos[val]++;
		}
		p = new_p ;
	}
	
	void Build(string s){
		s += " " ;
		int n = s.size();
		vt<int> p(n), c(n);
		{  // k = 0
			vt<pr<char,int>> a(n);
			f(i,0,n) a[i] = {s[i],i};
			sort(all(a));
			f(i,0,n) p[i] = a[i].sc ;
			c[p[0]] = 0;
			f(i,1,n){
				if(a[i].fr == a[i-1].fr){
					c[p[i]] = c[p[i-1]];
				}else{
					c[p[i]] = c[p[i-1]] + 1;
				}
			}
		}
		int k = 0;
		while((1<<k) < n){
			f(i,0,n) p[i] = (p[i]-(1<<k)+n)%n;
			count_sort(p,c) ;
			vt<int> new_c(n);
		
			new_c[p[0]] = 0 ;
			f(i,1,n){
				pr<int,int> prev = {c[p[i-1]],c[(p[i-1]+(1<<k))%n]} ;
				pr<int,int> now = {c[p[i]],c[(p[i]+(1<<k))%n]} ;
				new_c[p[i]] = new_c[p[i-1]] + (prev != now) ;
			}
			c = new_c;
			k++;
		}
		
		k = 0;
		vt<int> lcp(n);
		f(i,0,n-1){
			int pi = c[i];
			int j = p[pi-1];
			while(s[i + k] == s[j + k]) k++;
			lcp[pi] = k;
			k = max(k-1, int(0));
		}
		P = p;
		WHERE.resize(n);
		f(i,0,sz(p)) WHERE[p[i]] = i ;
		LCP = lcp; 
		rmq.init(lcp);
	}
	vt<int> get_lcp(){
		return LCP;
	}
	vt<int> get_sa(){
		return P;
	}
	int lcp(int i,int j){
		if(i == j) return sz(LCP) - i - 1;
		int l = WHERE[i], r = WHERE[j];
		assert(l != r);
		if(l>r) swap(l,r);
		return rmq.query(l+1,r);
	}
};