int determinant(vector<vector<int>> M,int P){
	function<int(int)> inv = [&](int x){
		int a = x, b = P - 2, ans = 1;
		for (; b; b /= 2, a = (a * a)%P) if(b&1) ans = (ans * a)%P;
    return ans;
	};
	int det = 1;
  int n = M.size();
  for(int i = 0; i < n; ++i){
    int t = i;
    for(int j = i+1; j < n; ++j){
      if(abs(M[j][i]) > abs(M[t][i]))	t = j;
    }
 		if(!M[t][i])	return 0;
    if(t != i){
      swap(M[i], M[t]);
      det *= -1;
    }
    det *= M[i][i];
    det %= P;
    for(int j = i+1; j < n; ++j){
      M[i][j] *= inv(M[i][i]);
      M[i][j] %= P;
    }
 		for(int j = 0; j < n; ++j){
      if(i == j) continue;
      for(int k = i+1; k < n; ++k){
        M[j][k] -= M[i][k] * M[j][i];
        M[j][k] %= P;
      }
    }
  }
  return det;
}