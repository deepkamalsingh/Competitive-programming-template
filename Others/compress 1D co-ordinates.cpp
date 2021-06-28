template<class T>	struct compress_1d_co_ordinates {
	
	vector<T> values;
	
  void add(T x){
  	values.push_back(x);
  	return;
  }
  
  void gen(){
  	sort(values.begin(),values.end());
  	values.erase(unique(values.begin(),values.end()),values.end());
  	return;
  }
  
  int get(T x){
  	int j = lower_bound(values.begin(),values.end(),x) - values.begin();
  	assert(values[j] == x); return j;
  }
  
  void clear(){
  	values.clear();
  	return;
  }
  
};