/*
 * source :- https://codeforces.com/blog/entry/68953 
 * for some reason changing if(mask & 1 << i == 0) to if(mask & 1 << i){ code... } gives WA.
 * Description :- 
  * here it checks whether some set forms basis or not
  * basis[i] keeps the mask of the vector whose f value is i
  * f(x) denotes lsb(x) which can also be altered to msb(x)
  * sz = Current size of the basis
  * continue if i != f(mask)
  * If there is no basis vector with the i'th bit set, then insert this vector into the basis
  * Otherwise subtract the basis vector from this vector
*/

template<int N>
struct xor_basis {
  vector<int> basis;
  int size;

  xor_basis() : basis(N,0), size(0) {}

  bool add(int mask){
    for(int i = 0; i < N; ++i){
      if((mask&(1LL<<i)) == 0)
        continue;
      if(basis[i] == 0){
        basis[i] = mask;
        size += 1;
        return true;
      }
      mask ^= basis[i];
    }
    return false;
  }  
};