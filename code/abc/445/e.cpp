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
 * ロジックは合っていたが実装しきれず
 * - A[i]を素因数分解して指数のmaxとmaxから2番目(maxと同じ値が複数あるならそれを2番目とする)を計算
 * - Aに含まれる全素数について, その素数^指数maxの総積を計算(=A全ての項のLCM)
 * - A[i]に対してA[i]の各素数がmaxならmaxから2番目を採用(その差で割る), maxでないならcontinue
 */

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    // テストケースが1つの場合
    // solve();

    // テストケースが複数ある場合
    int t;
    cin >> t;
    // 1e7以下の数に対するエラトステネスの篩
    vl erato; // 素数
    vb deleted(10'000'000LL); //true:すでにチェック済み
    rep(i, 2, 10'000'000LL+1){
        if(deleted[i])continue;
        erato.push_back(i);
        for(int j=i+i;j<10'000'000LL+1;j+=i) deleted[j]=true;
    }
    while (t--) {

    ll N; cin >> N;
    vl A(N); rep(i, 0, N) cin >> A[i];

    vector<map<ll, ll>> expo(N);
    map<ll, ll> maxexp, max2exp;

    rep(i, 0, N){
        ll t=A[i];
        rep(j, 0, sz(erato)){
            if(erato[j]*erato[j]>A[i]) break;
            while(t%erato[j]==0){
                expo[i][erato[j]]++;
                t/=erato[j];
            }
            if(expo[i].count(erato[j])){
                if(expo[i][erato[j]]>=maxexp[erato[j]]){
                    max2exp[erato[j]]=maxexp[erato[j]];
                    maxexp[erato[j]]=expo[i][erato[j]];
                }
                else if(expo[i][erato[j]]>=max2exp[erato[j]]){
                    max2exp[erato[j]]=expo[i][erato[j]];
                }
            }
        }
        if(t!=1)expo[i][t]++;
        if(expo[i].count(t)){
            if(expo[i][t]>=maxexp[t]){
                max2exp[t]=maxexp[t];
                maxexp[t]=expo[i][t];
            }
            else if(expo[i][t]>=max2exp[t]){
                max2exp[t]=expo[i][t];
            }
        }
    }

    mint pro=1; // 総積
    for(auto[k, v] : maxexp){
        mint a=k;
        pro *= a.pow(v);
    }

    rep(k, 0, N){
        //A[k]以外のlcm%m
        mint b=1;
        for(auto[e, v] : expo[k]){
            mint a=e;
            if(maxexp[e]==v){
                b *= a.pow(maxexp[e]-max2exp[e]);
            }
        }
        mint ans=pro*b.pow(998244353-2);
        out(ans.val());
    }

    }
    return 0;
}