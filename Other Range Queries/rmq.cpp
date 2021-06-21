/**
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
		for (int j = 1; 1<<j <= (int)((v).size()); ++j) {
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























const int MAXN=305000;
const int MAXLOG=20;

int n,a[MAXN];

int table[MAXLOG][MAXN][2],logs[MAXN];

void computeLogs(){
	logs[1]=0;
	f(i,2,n+1)	logs[i]=logs[i/2]+1;	
}

void buildSparseTable(){
  	f(i,0,logs[n]+1){
    	int curLen=(1LL<<i);
    	f(j,0,n-curLen+1){
      		if(curLen == 1) {
        		table[i][j][0]=table[i][j][1]=a[j];
      		}else{
        		table[i][j][0]=min( table[i-1][j][0] , table[i-1][j + (curLen/2)][0] );
        		table[i][j][1]=max( table[i-1][j][1] , table[i-1][j + (curLen/2)][1] );
      		}
    	}
  	}
}

int getMin(int l,int r){
	int p=logs[r-l+1];
	return min(table[p][l][0],table[p][r-(1LL<<p)+1][0]);
}

int getMax(int l,int r){
	int p=logs[r-l+1];
	return max(table[p][l][1],table[p][r-(1LL<<p)+1][1]);
}
