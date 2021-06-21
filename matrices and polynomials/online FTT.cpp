// source :- https://tanujkhattar.wordpress.com/2018/01/
// FOR solving the recurrences of the form F[i] = sum (1 <= j < i) F[j] * G[i-j]
void convolve(int l1,int r1,int l2,int r2){
  vector<int> A, B;// 0-based polynomials
	for(int i = l1; i <= r1; ++i) A.push_back(F[i]);
	for(int i = l2; i <= r2; ++i) B.push_back(G[i]);
	auto C = A * B;
	for(int i = 0; i < int(C.size()); ++i){
		F[l1 + l2 + i] += C[i];
	}
}
F[1] = 1;
for(int = 1; i <= n-1; ++i){
	// we have computed till i and want to add its contribution
	F[i + 1] += F[i] * G[1];
	F[i + 2] += F[i] * G[2];
	for(int pw = 2; i % pw == 0 && pw + 1 <= n; pw *= 2){
		//iterate over every power of 2 such that it divides i.
		convolve(i - pw, i - 1, pw + 1, min(2 * pw, n));
	}
}