/*
	* indexing starts from zero of our array , segment tree for mass operations , does not require lazy propagation
	* indexing of segment tree starts from 0   0
																						/ \
																					 1   2
	* source: pashka edu course with very little own modifications
	* to do questions using this method we should have both operation follow associative property and first op to follow commutivity,
			then distributive property as well(but of course some changes can be made to fit in some non - distributive functions ex +, +
	* verification http://codeforces.com/edu/course/2/lesson/5/2/practice/contest/279653/submission/103383500
	* set ID, NEUTRAL_ELEMENT, modify_op (modifaction done on array) , calc_op accordingly (what is asked on array)
	* get the intial segment tree also ie we may need to build it seperately sometimes
	* modify and asked query on interval [l, r)
*/
template<class T> struct SEGTREE {
	public:
		const T ID = , NEUTRAL_ELEMENT =  ;
		T modify_op(T a,T b){
			return   ;
		}
		T calc_op(T a,T b){
			return   ;
		}
		void apply_op(T &a,T b){
			a = modify_op(a, b) ;
		}
		int size ;
		vector<T> seg, ops ;
		void init(int n){
			size = 1 ;
			while(size < n) size *= 2 ;
			seg.assign(2*size, ID);
			ops.assign(2*size, ID);
		}
		void modify(int l, int r, int x, int lx, int rx, T v) {
			if( lx >= r || l >= rx ){
				return ;
			}
			if( lx >= l && rx <= r){
				apply_op(ops[x], v) ; apply_op(seg[x], v) ; return ;
			}
			int mid = (rx + lx)/2 ;
			modify(l, r, 2 * x + 1, lx, mid, v);
			modify(l, r, 2 * x + 2, mid, rx, v);
			seg[x] = calc_op(seg[2 * x + 1], seg[2 * x + 2]) ;
			apply_op(seg[x], ops[x]) ;
			return ;
		}
		void modify(int l, int r, T v) {
			modify(l, r, 0, 0, size, v) ; return ;
		}
		T get(int l, int r, int x, int lx, int rx) {
			if( lx >= r || l >= rx ){
				return NEUTRAL_ELEMENT ;
			}
			if( lx >= l && rx <= r){
				return seg[x] ;
			}
			int mid = (rx + lx)/2 ;
			T temp1 = get(l, r, 2 * x + 1, lx, mid) ;
			T temp2 = get(l, r, 2 * x + 2, mid, rx) ;
			T res = calc_op(temp1, temp2) ;
			apply_op(res, ops[x]) ;
			return res ;
		}
		T get(int l, int r) {
			return get(l, r, 0, 0, size) ;
		}
};