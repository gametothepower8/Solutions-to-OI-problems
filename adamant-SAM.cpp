const int maxn = 4e5 + 42;
map<char, int> to[maxn];
int len[maxn], link[maxn], fpos[maxn];
int sz = 1, last;
 
void add_letter(char c) {
    int p = last;
    last = sz++;
    len[last] = fpos[last] = len[p] + 1;
    for(; to[p][c] == 0; p = link[p]) {
        to[p][c] = last;
    }
    int q = to[p][c];
    if(q != last) {
        int cl = sz++;
        to[cl] = to[q];
        link[cl] = link[q];
        len[cl] = len[p] + 1;
        link[last] = link[q] = cl;
        for(; to[p][c] == q; p = link[p]) {
            to[p][c] = cl;
        }
    }
}
