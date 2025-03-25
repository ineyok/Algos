// O(|s1| + |s2| + .. + |sn|)

// Автомат Ахо-Корасик

struct Node {
    int term, pr, lastc, suf, super, go[Alf];
    Node() {
        term = pr = lastc = 0;
        suf = super = -1;
        fill(go, go + Alf, -1);
    }
};

// ...

int suf(int v);
int go(int v, int c) {
    if(trie[v].go[c] == -1) trie[v].go[c] = go(suf(v), c);
    return trie[v].go[c];
}
int suf(int v) {
    if(trie[v].suf == -1) {
        if(trie[v].pr == 0) trie[v].suf = 0;
        else trie[v].suf = go(suf(trie[v].pr), trie[v].lastc);
    }
    return trie[v].suf;
}
int super(int v) { // Не больше sqrt(L) до корня
    if(trie[v].super == -1) {
        if(!v || trie[trie[v].suf].term) trie[v].super = trie[v].suf;
        else trie[v].super = super(trie[v].suf);
    }
    return trie[v].super;
}
