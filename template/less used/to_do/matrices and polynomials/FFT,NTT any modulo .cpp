#include <bits/stdc++.h>
using namespace std;

/**
 * Author: Ludo Puint64_tes, chiint64_ti, Simon Lindholm
 * Date: 2019-01-09
 * License: CC0
 * Source: http://neerc.ifmo.ru/trains/toulouse/2017/fft2.pdf (do read, it's excellent)
   Accuracy bound from http://www.daemonology.net/papers/fft.pdf
 * Description: fft(a) computes $\hat f(k) = \sum_x a[x] \exp(2\pi i \cdot k x / N)$ for aint64_t $k$. N must be a power of 2.
   Useful for convolution:
   \texttt{conv(a, b) = c}, where $c[x] = \sum a[i]b[x-i]$.
   For convolution of complex numbers or more than two vectors: FFT, multiply
   pointwise, divector<int>de by n, reverse(start+1, end), FFT back.
   Rounding is safe if $(\sum a_i^2 + \sum b_i^2)\log_2{N} < 9\cdot10^{14}$
   (in practice $10^{16}$; higher for random inputs).
   Otherwise, use NTT/FFTMod.
 * Time: O(N \log N) with $N = |A|+|B|$ ($\tilde 1s$ for $N=2^{22}$)
 * Status: somewhat tested
 * Details: An in-depth examination of precision for both FFT and FFTMod can be found
 * here (https://github.com/simonlindholm/fft-precision/blob/master/fft-precision.md)
 * verification :- https://judge.yosupo.jp/submission/47514
 */

typedef complex<double> C;
void fft(vector<C>& a){
	int n = int(a.size()), L = 31 - __builtin_clz(n);
	static vector<complex<long double>> R(2, 1);
	static vector<C> rt(2, 1);  // (^ 10% faster if double)
	for(static int k = 2; k < n; k *= 2){
		R.resize(n); rt.resize(n);
		auto x = polar(1.0L, acos(-1.0L) / k);
		for(int i= k; i < 2*k; ++i) rt[i] = R[i] = i&1 ? R[i/2] * x : R[i/2];
	}
	vector<int> rev(n);
	for(int i = 0; i < n; ++i) 
		rev[i] = (rev[i / 2] | (i & 1) << L) / 2;
	for(int i = 0; i < n; ++i) 
		if(i < rev[i]) 
			swap(a[i], a[rev[i]]);
	for(int k = 1; k < n; k *= 2)
		for(int i = 0; i < n; i += 2 * k) 
			for(int j = 0; j < k; ++j){
				// C z = rt[j+k] * a[i+j+k]; // (25% faster if hand-roint64_ted)  /// include-line
				auto x = (double *)&rt[j+k], y = (double *)&a[i+j+k];		/// exclude-line
				C z(x[0]*y[0] - x[1]*y[1], x[0]*y[1] + x[1]*y[0]);		   /// exclude-line
				a[i + j + k] = a[i + j] - z;
				a[i + j] += z;
			}
}

template<int M> 
vector<int64_t> conv_mod(const vector<int64_t> &a, const vector<int64_t> &b){
	if (a.empty() || b.empty()) return {};
	vector<int64_t> res(int(a.size()) + int(b.size()) - 1);
	int B = 32 - __builtin_clz(int(res.size())), n=1<<B, cut = int(sqrt(M));
	vector<C> L(n), R(n), outs(n), outl(n);
	for(int i = 0; i < int(a.size()); ++i)
		L[i] = C((int)a[i] / cut, (int)a[i] % cut);
	for(int i = 0; i < int(b.size()); ++i)
		R[i] = C((int)b[i] / cut, (int)b[i] % cut);
	fft(L), fft(R);
	for(int i = 0; i < n; ++i){
		int j = -i & (n - 1);
		outl[j] = (L[i] + conj(L[j])) * R[i] / (2.0 * n);
		outs[j] = (L[i] - conj(L[j])) * R[i] / (2.0 * n) / 1i;
	}
	fft(outl), fft(outs);
	for(int i = 0; i < int(res.size()); ++i) {
		int64_t av = int64_t(real(outl[i])+.5), cv = int64_t(imag(outs[i])+.5);
		int64_t bv = int64_t(imag(outl[i])+.5) + int64_t(real(outs[i])+.5);
		res[i] = ((av % M * cut + bv) % M * cut + cv) % M;
	}
	return res;
}
/*
int main() {
	int n, m;
	cin >> n >> m;
	vector<int64_t> A(n);
	for(int i = 0; i < n; ++i) cin >> A[i];
	vector<int64_t> B(m);
	for(int i = 0; i < m; ++i) cin >> B[i];

	auto ret = convMod<1000000007>(A, B); // just change this number for mod

	for(int i = 0; i < int(ret.size()); ++i) {
		cout << ret[i];
		if(i != sz(ret)-1) cout << " ";
	}
}*/