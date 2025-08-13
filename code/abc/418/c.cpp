#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <numeric>
#include <cmath>
#include <map>
#include <set>
#include <queue>
#include <stack>
#include <functional>
#include <ranges>
#include <cctype>
#include <iomanip>
using namespace std;

// #include "../../../ac-library-master/atcoder/dsu.hpp"
// using namespace atcoder;

using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
using vi = vector<int>;
using vl = vector<ll>;
using vvi = vector<vi>;
using vvl = vector<vl>;

const ll INF = 1e18;
const int MOD = 1000000007;
const string LOWALP = "abcdefghijklmnopqrstuvwxyz";
const string UPALP = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
const int dx[4] = {-1,0,1,0};
const int dy[4] = {0,1,0,-1}; // 4近傍、上右下左

#define rep(i, a, n) for (int i = a; i < (int)(n); ++i)
#define rrep(i, a, n) for (int i = (int)(n) - 1; i >= a; --i)
#define all(x) (x).begin(), (x).end()
#define sz(x) (int)(x).size()
#define Yes cout << "Yes" << endl
#define No cout << "No" << endl
#define out(x) cout << x << "\n"

template<class T> bool chmax(T &a, const T &b) {
    if (a < b) { a = b; return true; }
    return false;
}
template<class T> bool chmin(T &a, const T &b) {
    if (a > b) { a = b; return true; }
    return false;
}

void solve() {
    ll N, Q, maxA=0;
    cin >> N >> Q;
    vector<ll> A(N);
    rep(i, 0, N) {
        ll a;
        cin >> a;
        A[i]=a;
        chmax(maxA, a);
    }
    vector<ll> B(Q);
    rep(i, 0, Q) cin >> B[i];

    sort(all(A));
    vector<ll> sumA(N+1);//Aの累積和
    rep(i, 0, N){
        sumA[i + 1] = sumA[i] + A[i];
    }
    
    rep(bi, 0, Q){
        //難易度B[bi]
        if(B[bi]>maxA){
            out("-1");
            continue;
        }
        auto it_lower = lower_bound(all(A), B[bi]-1);
        auto idx_lower = distance(A.begin(), it_lower);
        out((sumA[idx_lower])+((B[bi]-1)*(N-idx_lower))+1);
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    // テストケースが1つの場合
    solve();

    // テストケースが複数ある場合 (コメントアウトを外して使用)
    /*
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
    */
    return 0;
}