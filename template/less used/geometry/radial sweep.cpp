/*
	* Description :- sorting points by their bearing.
	* Sources :- USACO guide.
	* Verf :- ??
*/

struct P{
	int x,y;
}origin;

struct Event {
	int type, id;
	P loc;
};

// Cross product
int cross(P a,P b){
	return (a.y - origin.y) * (b.x - origin.x) - (a.x - origin.x) * (b.y - origin.y);
}

// Which half of the plane some point lies in
int half(P p){
	if(p.x != origin.x) 
		return (p.x < origin.x) - (p.x > origin.x);
	return (p.y < origin.y) - (p.y > origin.y);
}

// Custom comparator to sort by bearing in clockwise order starting from 12'O clock.
bool operator<(Event a, Event b){
	int ah = half(a.loc), bh = half(b.loc);
	if(ah == bh){
		int c = cross(a.loc, b.loc);
		if(c == 0) 
			return a.type > b.type;
		return c > 0;
	}
	return ah < bh;
}