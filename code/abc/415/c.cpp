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

//#include "../../../ac-library-master/atcoder/dsu.hpp"
//#include <atcoder/all>
//using namespace atcoder;

using ll = long long;
using pll = pair<ll, ll>;
using vpll = vector<pll>;
using vl = vector<ll>;
using vvl = vector<vl>;
using vb = vector<bool>;
using vvb = vector<vb>;
using vs = vector<string>;

const ll INF = 1e18;
const ll MOD = 1000000007;
const string abc = "abcdefghijklmnopqrstuvwxyz";
const string ABC = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
const int dx[4] = {-1,0,1,0};
const int dy[4] = {0,1,0,-1}; // 4近傍、上右下左

#define rep(i, a, n) for (ll i = a; i < (int)(n); ++i)
#define rrep(i, a, n) for (ll i = (ll)(n) - 1; i >= a; --i)
#define all(x) (x).begin(), (x).end()
#define sz(x) (ll)(x).size()
#define Yes cout << "Yes" << endl
#define No cout << "No" << endl
#define out(x) cout << x << "\n"
#define fix cout << fixed <<  setprecision(10)
#define fi  first;
#define se  second;

template<class T> bool chmax(T &a, const T &b) {
    if (a < b) { a = b; return true; }
    return false;
}
template<class T> bool chmin(T &a, const T &b) {
    if (a > b) { a = b; return true; }
    return false;
}

/**
 * 薬品を混ぜる順番を全てシミュレーション -> O(N!)(N<=18)はダメ
 * 状態の遷移をグラフとして構築してDFSやBFSで探索し, 全て混ざった状態へ到達できるか判定する
 * 頂点数=状態数=2^N, 各状態からN本(くらい)の辺が出るからO(N*2^N)
 * 状態0:何も混ざっていない状態(安全)としてS='0'+Sと状態0を統合すると探索の始点として扱いやすい
 * 辺は安全な状態へ向けて張れば十分
 */

// DFSでの実装
// void solve() {
// // ロジックをちゃんと考える！！！
//     ll N; cin >> N;
//     string S; cin >> S;
//     S = '0' + S;
//     vvl G(1<<N);
//     rep(i, 0, 1<<N){
//         //状態iから生やす
//         rep(j, 0, N){
//             //薬品jを注げるか
//             if(!((i>>j)&1) && S[i|(1<<j)]=='0') G[i].push_back(i|(1<<j));
//         }
//     }
//     vb seen(1<<N, false);
//     auto dfs = [&](auto dfs, ll v) -> void {
//         seen[v]=true; //戻さなくていい
//         for(auto to : G[v]){
//             if(seen[to]) continue;
//             dfs(dfs, to);
//         }
//     };
//     dfs(dfs, 0);
//     seen[(1<<N)-1] ? Yes : No;
// }

// BFSでの実装
// void solve(){
//     ll N; cin >> N;
//     string S; cin >> S;
//     S = '0' + S;
//     vvl G(1<<N);
//     rep(i, 0, 1<<N){
//         //状態iから生やす
//         rep(j, 0, N){
//             //薬品jを注げるか
//             if(!((i>>j)&1) && S[i|(1<<j)]=='0') G[i].push_back(i|(1<<j));
//         }
//     }
//     vb seen(1<<N, false);
//     queue<ll> q;
//     q.push(0); seen[0]=true;
//     while(!q.empty()){
//         ll v = q.front(); q.pop();
//         for(auto to : G[v]){
//             if(seen[to]) continue;
//             q.push(to); seen[to] = true; //pushした瞬間にフラグを更新しないと同じ頂点が何度もpushされてMLEする
//         }
//     }
//     seen[(1<<N)-1] ? Yes : No;
// }

// DPでの実装
void solve(){
    ll N; cin >> N;
    string S; cin >> S;
    S = '0' + S;
    vb dp(1<<N, false);
    dp[0]=true;
    rep(i, 0, 1<<N){
        if(dp[i]){ //状態iが到達可能なときだけ考える
            rep(j, 0, N){
                //状態iから薬品jを混ぜる
                if(!((i>>j)&1) && S[i|(1<<j)]=='0') dp[i|(1<<j)] = true;
            }   
        }
    }
    dp[(1<<N)-1] ? Yes : No;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    // テストケースが1つの場合
    // solve();

    // テストケースが複数ある場合
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}