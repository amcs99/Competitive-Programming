/* created by : Son Dinh */

#include<bits/stdc++.h>

using namespace std;

const int mod = 111539786;
typedef long long ll;
struct matrix{
    ll a0,a1,a2,a3;
    matrix(): a0(0), a1(0), a2(0), a3(0){}
    matrix(int x, int y, int z, int t): a0(x), a1(y), a2(z), a3(t){}
};

matrix operator*(matrix a, matrix b){
    matrix res;
    res.a0 = ((a.a0 * b.a0) % mod + (a.a1 * b.a2) % mod) % mod;
    res.a1 = ((a.a0 * b.a1) % mod + (a.a1 * b.a3) % mod) % mod;
    res.a2 = ((a.a2 * b.a0) % mod + (a.a3 * b.a2) % mod) % mod;
    res.a3 = ((a.a2 * b.a1) % mod + (a.a3 * b.a3) % mod) % mod;
    return res;
}
matrix fpow(matrix a, int b){
    matrix ans = matrix(0,1,1,1);
    while(b){
        if(b & 1) ans = ans * a;
        a = a * a;
        b >>= 1;
    }
    return ans;
}
int n;
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    int t;
    cin >> t;
    while(t--){
        cin >> n;
        cout << fpow(matrix(0,1,1,1),n).a1 << '\n';
    }
    return 0;
}
