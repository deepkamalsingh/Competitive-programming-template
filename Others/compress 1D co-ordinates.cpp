struct compress_1d_co_ordinates {
	vector<int> values;
  void add(int x){
  	values.push_back(x);
  }
  void gen(){
  	sort(values.begin(),values.end());
  	values.erase(unique(values.begin(),values.end()),values.end());
  }
  int get(int x){
  	int j = lower_bound(values.begin(),values.end(),x) - values.begin();
  	assert(values[j] == x); return j;
  }
}compress;