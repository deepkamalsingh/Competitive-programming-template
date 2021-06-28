//source :- https://codeforces.com/blog/entry/61587
#define rand __rand
auto random_address = [] { char *p = new char; delete p; return uint64_t(p); };
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count() * (random_address() | 1));
int rand(int L = 0,int R = int(1e9)){
  return uniform_int_distribution<int>(L,R)(rng) ;
}