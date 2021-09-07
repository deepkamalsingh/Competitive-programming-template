//source :- https://codeforces.com/blog/entry/61587
//use shuffle(all(a),rng) to have a random permutation.

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

int random(int L, int R){
  return uniform_int_distribution<int>(L,R)(rng) ;
}