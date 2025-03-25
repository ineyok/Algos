// O(|s|) на звпрос

// Бор - префиксное дерево

const int Alf = 26;

struct Node {
    int term;
    int link[Alf];
    Node() : term(0) {
        fill(link, link + Alf, -1);
    }
};
vector<Node> trie(1);

void add_str(string & s) {
    int v = 0;
    for(char ch : s) {
        int c = ch - 'a';
        if(trie[v].link[c] == -1) {
            trie[v].link[c] = siz(trie);
            trie.push_back(Node());
        }
        v = trie[v].link[c];
    }
    trie[v].term = 1;
}

bool query(string & s) {
    int v = 0;
    for(char ch : s) {
        int c = ch - 'a';
        if(trie[v].link[c] == -1) return 0;
        v = trie[v].link[c];
    }
    return trie[v].term;
}
