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

const ll INF = 1e18;
const ll MOD = 998244353;
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
#define fix cout << fixed <<  setprecision(10)

template<class T> bool chmax(T &a, const T &b) {
    if (a < b) { a = b; return true; }
    return false;
}
template<class T> bool chmin(T &a, const T &b) {
    if (a > b) { a = b; return true; }
    return false;
}

/**
 * 制約から長さNの文字列は2^Nしかない
 * checkも含めてO(N*2^N)で間に合う
 * 
 * 括弧列の判定はstackを使用する方法と, (を+1, )を-1とした時に文字列を走査して値を足していき最終結果が0かつ一度も負にならない方法(以下で実装されている. ABC428Cもそう)
 * https://github.com/E869120/kyopro_educational_90/blob/main/sol/002.cpp
 */
void solve() {
// ロジックをちゃんと考える！！！
    ll N; cin >> N;
    if(N%2) return;

    auto check = [&](string s) -> bool {
        deque<char> q;
        rep(i, 0, sz(s)){
            if(q.empty()){
                if(s[i]=='(')q.push_back('(');
                else return false;
            }
            else {
                if(s[i]=='('){
                    q.push_back('(');
                }
                else{
                    if(q.back()=='('){
                        q.pop_back();
                    }
                    else return false;
                }
            }
        }
        if(q.empty()) return true;
        else return false;
    };
    
    rep(i, 0, (1<<N)){
        string s;
        rep(j, 0, N){
            if((i>>j)&1) s = ")" + s;
            else s = "(" + s;
        }
        if(check(s))out(s);
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