
/*
	Description :- Sparse lazy segment tree
	Source :- https://usaco.guide/plat/sparse-seg?lang=cpp
	Verification :- https://oj.uz/submission/409297

*/
struct Node {
	int sum, lazy, tl, tr, l, r;// node cover [tl,tr], also lazy is not added to current node;
	Node() : sum(0), lazy(0), l(-1), r(-1) {}
};

const int MAXN = 123456;
Node st[64 * MAXN];
int cnt = 2;


void propogate(int x) {
	if (st[x].lazy) {
		st[x].sum = st[x].tr - st[x].tl + 1;
		int mid = (st[x].tl + st[x].tr) / 2;
		if (st[x].l == -1) {
			st[x].l = cnt++;
			st[st[x].l].tl = st[x].tl;
			st[st[x].l].tr = mid;
		}
		if (st[x].r == -1) {
			st[x].r = cnt++;
			st[st[x].r].tl = mid + 1;
			st[st[x].r].tr = st[x].tr;
		}
		st[st[x].l].lazy = st[st[x].r].lazy = 1;
		st[x].lazy = 0;
	}
}

void update(int x, int l, int r) {
	propogate(x);
	if (l == st[x].tl && r == st[x].tr) {
		st[x].lazy = 1;
		propogate(x);
	} else {
		int mid = (st[x].tl + st[x].tr) / 2;
		if (st[x].l == -1) {
			st[x].l = cnt++;
			st[st[x].l].tl = st[x].tl;
			st[st[x].l].tr = mid;
		}
		if (st[x].r == -1) {
			st[x].r = cnt++;
			st[st[x].r].tl = mid + 1;
			st[st[x].r].tr = st[x].tr;
		}

		if (l > mid) update(st[x].r, l, r);
		else if (r <= mid) update(st[x].l, l, r);
		else {
			update(st[x].l, l, mid);
			update(st[x].r, mid + 1, r);
		}

		propogate(st[x].l);
		propogate(st[x].r);
		st[x].sum = st[st[x].l].sum + st[st[x].r].sum;
	}
}

int query(int x, int l, int r) {
	propogate(x);
	if (l == st[x].tl && r == st[x].tr) return st[x].sum;
	else {
		int mid = (st[x].tl + st[x].tr) / 2;
		if (st[x].l == -1) {
			st[x].l = cnt++;
			st[st[x].l].tl = st[x].tl;
			st[st[x].l].tr = mid;
		}
		if (st[x].r == -1) {
			st[x].r = cnt++;
			st[st[x].r].tl = mid + 1;
			st[st[x].r].tr = st[x].tr;
		}

		if (l > mid) return query(st[x].r, l, r);
		else if (r <= mid) return query(st[x].l, l, r);
		else return query(st[x].l, l, mid) + query(st[x].r, mid + 1, r);
	}
}
