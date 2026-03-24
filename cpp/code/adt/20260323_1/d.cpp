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

void solve() {
    // ロジックをちゃんと考える！！！
    ll N, X, Y, Z; cin >> N >> X >> Y >> Z;
    vl A(N), B(N);
    rep(i, 0, N) cin >> A[i];
    rep(i, 0, N) cin >> B[i];

    vl idx;
    set<pll> s1;
    rep(i, 0, N){
        s1.insert({-A[i], i});
    }
    auto it=s1.begin();
    ll i=0;
    while(it!=s1.end()){
        if(i==X) break;
        auto[k, v] = *it;
        idx.push_back(v);
        s1.erase(it++); i++;
    }
    set<pll> s2;
    for(auto[k, v] : s1){
        s2.insert({-B[v], v});
    }
    it=s2.begin();
    i=0;
    while(it!=s2.end()){
        if(i==Y) break;
        auto[k, v] = *it;
        idx.push_back(v);
        s2.erase(it++); i++;
    }
    set<pll> s3;
    for(auto[k, v] : s2){
        s3.insert({-A[v]-B[v], v});
    }
    it=s3.begin();
    i=0;
    while(it!=s3.end()){
        if(i==Z) break;
        auto[k, v] = *it;
        idx.push_back(v);
        s3.erase(it++); i++;
    }

    sort(all(idx));
    for(auto i : idx) out(i+1);
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