int cdiv(int a,int b) { return a/b+((a^b)>0&&a%b); } // divide a by b rounded up
int fdiv(int a,int b) { return a/b-((a^b)<0&&a%b); } // divide a by b rounded down