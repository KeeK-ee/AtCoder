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

#include <atcoder/all>
using namespace atcoder;

using ll = long long;
using ull = unsigned long long;
using ld = long double;
using pll = pair<ll, ll>;
using vpll = vector<pll>;
using vvpll = vector<vpll>;
using vl = vector<ll>;
using vvl = vector<vl>;
using vb = vector<bool>;
using vvb = vector<vb>;
using vs = vector<string>;
using pq = priority_queue<ll>;
using pq_min = priority_queue<ll, vector<ll>, greater<ll>>; //小さい順
using mint = modint998244353;

const ll INF = 8000000000000000000LL; // 8*10^18
const ll MOD = 998244353;
const ld pi = 3.141592653589793238;
const string abc = "abcdefghijklmnopqrstuvwxyz";
const string ABC = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
const int dx[4] = {-1,0,1,0};
const int dy[4] = {0,1,0,-1}; // 4近傍、上右下左

#define rep(i, a, n) for (ll i = a; i < (ll)(n); ++i)
#define rrep(i, a, n) for (ll i = (ll)(n) - 1; i >= a; --i)
#define all(x) (x).begin(), (x).end()
#define sz(x) (ll)(x).size()
#define Yes cout << "Yes" << endl
#define No cout << "No" << endl
#define out(x) cout << x << "\n"
#define fix cout << fixed <<  setprecision(15)

template<class T> bool chmax(T &a, const T &b) {
    if (a < b) { a = b; return true; }
    return false;
}
template<class T> bool chmin(T &a, const T &b) {
    if (a > b) { a = b; return true; }
    return false;
}

/**
 * 開始位置と(i=0~N-1)と間隔(j=1~N-1-i)を全探索->O(N^2*logN)=10^8->一応間に合う
 * 高さを固定->難しそう
 * 間隔(i=1~N-1)と開始位置(j=0~i-1)を全探索->O(N^2)(間隔を固定したときに, 数列の各項を高々1回ずつしか見ない=O(N))
 * ansのchmaxのタイミングはif(true)の場合にする
 * ansの初期値が0だと1WA
 */
void solve() {
// ロジックをちゃんと考える！！！
    ll N; cin >> N;
    vl H(N);
    rep(i, 0, N) cin >> H[i];
    ll ans=1;
    rep(i, 1, N){
        rep(j, 0, i){
            ll tmp=0, v=H[j];
            // 間隔i, 始点jの条件で高さが同じものが最大何個続くか?
            for(ll k=j; k<N ; k+=i){
                if(H[k]==v) {
                    tmp++;
                    chmax(ans, tmp);
                }
                else{
                    v = H[k];
                    tmp = 1;
                }
            }
        }
    }
    out(ans);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    // テストケースが1つの場合
    solve();

    // テストケースが複数ある場合
    // int t;
    // cin >> t;
    // while (t--) {
    //     solve();
    // }
    return 0;
}