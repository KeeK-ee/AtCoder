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
using pii = pair<int, int>;
using pll = pair<ll, ll>;
using vi = vector<int>;
using vl = vector<ll>;
using vvi = vector<vi>;
using vvl = vector<vl>;

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

template<class T> bool chmax(T &a, const T &b) {
    if (a < b) { a = b; return true; }
    return false;
}
template<class T> bool chmin(T &a, const T &b) {
    if (a > b) { a = b; return true; }
    return false;
}

/**
 * 愚直は無理<-112233332211のような(中央から消えて連鎖する)場合が最悪O(N^2)
 * 真ん中から消す->stackを思いつけるか(括弧列を空にできるかとかもそうだよね
 * 「4連続をどの場所から消してもよい」ことは直感的
 * std::stackにはtopより下の要素にアクセスする方法がない
 * ->方法は2つ
 * - stackとランレングス圧縮
 * - std::vectorのpop_backやdequeのpop_backを使う(dequeもランダムアクセス可能, vectorが簡単そう)
 */
void solve(){
    ll N; cin >> N;
    vl A;
    ll ans = N;
    rep(i, 0, N){
        ll a; cin >> a;
        if(sz(A)<3) A.push_back(a);
        else if(a==A[sz(A)-1]&&A[sz(A)-1]==A[sz(A)-2]&&A[sz(A)-2]==A[sz(A)-3]){
            rep(j, 0, 3) A.pop_back();
            ans -= 4;
        }
        else{
            A.push_back(a);
        }
    }
    out(ans);
}

/**
 * 考えていることは合っているが、実装が複雑かつロジックミスが見られる
 * アルゴリズムを思いついてもさらに簡単な実装がないか考える
 */
// void solve() {
//     ll N; cin >> N;
//     vl A(N);
//     rep(i, 0, N) cin >> A[i];
//     vector<pll> rle;
//     rle.push_back({A[0], 1});
//     rep(i, 1, N){
//         if(A[i]==rle[sz(rle)-1].first) rle[sz(rle)-1].second++;
//         else rle.push_back({A[i], 1});
//     }
//     stack<pll> st;
//     ll ans=N;
//     rep(i, 0, sz(rle)){
//         // if(st.empty()) continue;
//         // cout << st.top().first << " " << st.top().second << " ";
//         if(rle[i].second>=4){
//             ans -= rle[i].second-(rle[i].second%4);
//             rle[i].second = rle[i].second%4;
//             if(rle[i].second==0)continue;
//         }
//         if(st.empty()) continue;
//         // cout << st.top().first << " " << st.top().second <<  " ";
//         if(rle[i].first==st.top().first &&  rle[i].second + st.top().second>=4){
//             ans -= ((rle[i].second + st.top().second) - (rle[i].second + st.top().second)%4);
//             st.top().second =  (rle[i].second + st.top().second)%4;
//             if(st.top().second==0)st.pop();
//             continue;
//         }
//         else{
//             st.push(rle[i]);
//         }
//     }
//     out(ans);
// }

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