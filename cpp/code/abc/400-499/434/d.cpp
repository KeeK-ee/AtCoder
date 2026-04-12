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
#include <random>
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
 * 二次元imos*二次元累積和
 */
void solve() {
    // ロジックをちゃんと考える！！！
    ll N; cin >> N;
    vl U(N), D(N), L(N), R(N);
    rep(i, 0, N) {
        cin >> U[i] >> D[i] >> L[i] >> R[i];
        U[i]--; D[i]--; L[i]--; R[i]--;
    }

    vvl sky(2001, vl(2001));
    rep(i, 0, N){
        sky[U[i]][L[i]]++; sky[D[i]+1][R[i]+1]++;
        sky[U[i]][R[i]+1]--; sky[D[i]+1][L[i]]--;
    }
    rep(i, 0, 2001){
        rep(j, 1, 2001) sky[i][j]+=sky[i][j-1];
    }
    rep(j, 0, 2001){
        rep(i, 1, 2001) sky[i][j]+=sky[i-1][j];
    }

    ll z=0;
    rep(i, 0, 2000)rep(j, 0, 2000) if(sky[i][j]==0) z++;

    vvl only1(2001, vl(2001));
    rep(i, 0, 2000)rep(j, 0, 2000){
        if(sky[i][j]==1) only1[i][j]=1;
    }
    rep(i, 0, 2001){
        rep(j, 1, 2001) only1[i][j]+=only1[i][j-1];
    }
    rep(j, 0, 2001){
        rep(i, 1, 2001) only1[i][j]+=only1[i-1][j];
    }

    rep(i, 0, N){
        ll c=0;
        c+=only1[D[i]][R[i]];
        if(U[i]-1>=0&&L[i]-1>=0) c+=only1[U[i]-1][L[i]-1];
        if(L[i]-1>=0) c-=only1[D[i]][L[i]-1];
        if(U[i]-1>=0) c-=only1[U[i]-1][R[i]];
        out(c+z);
    }
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