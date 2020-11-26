/*
created by: SonDinh
*/
#include<bits/stdc++.h>

#define ntest 0

using namespace std;

struct node {
    int cnt;
    node* child[2];
    node() {
        child[0] = child[1] = NULL;
        cnt = 0;
    }
};
node* trie;

/*
insert a 32-bit integer into trie
the leftmost bit will be inversed because: 1 -> negative number, 0 positive number
*/
void add(int x) {
    node* p = trie;
    for (int i = 31; i >= 0; --i) {
        int c = (x >> i) & 1;
        if (i == 31) c ^= 1;
        if (p->child[c] == NULL) p->child[c] = new node();
        p = p->child[c];
        ++p->cnt;
    }
}

/*
delete a 32-bit integer (must be existed in trie)
*/
void del(int x) {
    node* p = trie;
    for (int i = 31; i >= 0; --i) {
        int c = (x >> i) & 1;
        if (i == 31) c ^= 1;
        p = p->child[c];
        --p->cnt;
    }
}

/*
count the number in trie
*/
int getCount() {
    int ret = 0;
    if (trie == NULL) return ret;
    if (trie->child[0] != NULL) ret += trie->child[0]->cnt;
    if (trie->child[1] != NULL) ret += trie->child[1]->cnt;
    return ret;
}
/*
find k-th smallest number
*/
long long kth(int k, int ans, int weight, node* p) {
    if (k <= 0 || (p->child[0] == NULL && p->child[1] == NULL)) return ans;
    if (p->child[0] != NULL && p->child[0]->cnt >= k) return kth(k, ans, weight >> 1,  p->child[0]);
    else {
        if (p->child[0] == NULL) return kth(k, ans + weight, weight >> 1, p->child[1]);
        return kth(k - p->child[0]->cnt, ans + weight, weight >> 1, p->child[1]);
    }
}

/*
check if x is existed in trie or not
*/
int found(int x) {
    node* p = trie;
    for (int i = 31; i >= 0; --i) {
        int c = (x >> i) & 1;
        if (i == 31) c ^= 1;
        p = p->child[c];
        if (p == NULL || p->cnt < 1) return 0;
    }
    return 1;
}

/*
count the number that is smaller than k in trie
*/
int count(int k) {
    node *p = trie;
    int ret = getCount();
    if (ret == 0) return ret;
    for (int i = 31; i >= 0; --i) {
        int c = (k >> i) & 1;
        if (i == 31) c ^= 1;
        if (p->child[c] == NULL) p->child[c] = new node();
        if (c == 0 && p->child[1] != NULL) ret -= p->child[1]->cnt;
        p = p->child[c];
    }
    if (found(k)) --ret;
    return ret;
}
int q,k;
string c;

void solve() {
    trie = new node();
    cin >> q;
    while(q--) {
        cin >> c >> k;
        if (c == "I") {
            if (!found(k)) add(k);
        } else if (c == "D") {
            if (found(k)) del(k);
        } else if (c == "K") {
            if (getCount() < k) {
                cout << "invalid\n";
                continue;
            }
            // 32-th bit is sign , 1 -> negative, 0 -> positive, but it's inversed when add to trie
            int res = 0;
            if (trie->child[0] != NULL && trie->child[0]->cnt >= k) {
                res = kth(k, 1LL<<31, 1LL << 30, trie->child[0]);
            } else {
                if (trie->child[0] != NULL) res = kth(k - trie->child[0]->cnt, 0, 1LL << 30, trie->child[1]);
                else res = kth(k, 0, 1LL << 30, trie->child[1]);
            }
            cout << res << '\n';
        } else {
            cout << count(k) << '\n';
        }
    }
}
int32_t main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    if(ntest){
        int t;
        cin >> t;
        while(t--) solve();
    } else {
        solve();
    }

}



