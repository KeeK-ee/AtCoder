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
const int dy4[4] = {-1,0,1,0};
const int dx4[4] = {0,1,0,-1};
const int dy8[8] = {-1, -1, 0, 1, 1, 1, 0, -1};
const int dx8[8] = {0, 1, 1, 1, 0, -1, -1, -1};

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
bool out_of_grid(ll y, ll x, ll H, ll W) {
    return (y < 0 || x < 0 || y >= H || x >= W);
}

/**
 * 答えで二分探索
 * 最小値の最大化や最大値の最小化はにぶたんらしい
 * 負担量を決め打ったときに分割可能かどうかの判定をO(N)で可能
 * つまり全体としてO(NlogN)で解ける
 * 
 * 負担量を"ちょうどM"やトラックを"ちょうどK台に分割"ととらえると難しい
 * 判定にはM以上でK台以上とするとよい
 * 貪欲に構築していってK+1台以上に分割できた場合はK台以上を必ず達成可能(単純にトラックを減らしてその分の荷物を別のトラックに任せればいい)
 */
void solve() {
// ロジックをちゃんと考える！！！
    ll N, K; cin >> N >> K;
    vl A(N); rep(i, 0, N) cin >> A[i];

    auto check = [&](ll x) -> bool {
        ll idx=0, cnt=0;
        while(idx<N){
            ll tmp=0;
            while(idx<N && tmp<x){
                tmp += A[idx]; idx++;
            }
            if(tmp>=x)cnt++;
            else break;
        }
        bool res=(cnt>=K);
        return res;
    };

    ll ok=1, ng=INF;
    while(ng-ok>1){
        ll m=(ok+ng)/2;
        // 負担量m以上でK台以上のトラックに分割できるか？
        if(check(m))ok=m;
        else ng=m;
    }
    out(ok);
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