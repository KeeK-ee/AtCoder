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

#include <boost/multiprecision/cpp_int.hpp>
using namespace boost::multiprecision;

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
using vc = vector<char>;
using vvc = vector<vc>;
using pq = priority_queue<ll>;
using pq_min = priority_queue<ll, vector<ll>, greater<ll>>; //小さい順
using mint = modint998244353;
using bint = cpp_int;

const ll INF = 8'000'000'000'000'000'000LL; // 8*10^18
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

/**
 * 乱択アルゴリズム
 * 過半数を通る直線が存在するとき, 適当に2点選んだ時にその2点を通る直線(一意に定まる)が答えである確率は1/4
 * ->つまり答えとなる直線が存在するとき1/4で見つかる
 * ->これを十分な回数(100回程度)繰り返し, 一度も見つからなかった場合は存在しないとする
 * 繰り返す回数をTとしてO(T*N)
 * 
 * 2点を通る直線の方程式(https://manabitimes.jp/math/894)
 * (x2-x1)(y-y1)=(y2-y1)*(x-x1)
 */
void solve() {
    // ロジックをちゃんと考える！！！
    ll N; cin >> N;
    vl X(N), Y(N);
    rep(i, 0, N) cin >> X[i] >> Y[i];

    ll t=100;
    rep(ti, 0, t){
        ll i=-1, j=-1;
        do{
            i=rand()%N; j=rand()%N;
        }while(i==j);
        ll a=Y[j]-Y[i];
        ll b=X[i]-X[j];
        ll c=X[j]*Y[i]-X[i]*Y[j];
        ll cnt=0;
        rep(k, 0, N){
            if(a*X[k]+b*Y[k]+c==0) cnt++;
        }
        if(cnt>=(N+1)/2){
            Yes;
            cout << a << " " << b << " " << c << '\n';
            return;
        }
    }
    No;
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