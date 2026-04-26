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

#include <atcoder/all>
using namespace atcoder;

using ll = long long;
using ull = unsigned long long;
using int128 = __int128_t;
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

const ll INF = 8'000'000'000'000'000'000LL; // 8*10^18
const ll MOD = 998244353;
const ld pi = 3.141592653589793238;
const string abc = "abcdefghijklmnopqrstuvwxyz";
const string ABC = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
const int dy4[4] = {-1,0,1,0};
const int dx4[4] = {0,1,0,-1};
const int dy8[8] = {-1, -1, 0, 1, 1, 1, 0, -1};
const int dx8[8] = {0, 1, 1, 1, 0, -1, -1, -1};
const string dir = "URDL";

#define rep(i, a, n) for (ll i = a; i < (ll)(n); ++i)
#define rrep(i, a, n) for (ll i = (ll)(n) - 1; i >= a; --i)
#define all(x) (x).begin(), (x).end()
#define sz(x) (ll)(x).size()
#define Yes cout << "Yes" << endl
#define No cout << "No" << endl
#define out(x) cout << x << "\n"

struct Move
{
    ll type;
    ll i;
    ll j;
    ll k;
};

void solve() {
    vector<vector<Move>> ans;

    auto GreedyMult = [&]() -> void {
        ll R; cin >> R;
        vvl DEP(R); // 出発線
        vvl SID(R); // 待避線
        rep(i, 0, R)rep(j, 0, 10){
            ll y; cin >> y;
            DEP[i].push_back(y);
        }

        // ==========================================
        // フェーズ1: 目的地ごとの待避線へ振り分け（超高速・並列実行版）
        // ==========================================
        while (true) {
            struct Cand { ll i, j, c; };
            vector<Cand> cands;
            
            rep(i, 0, R){
                if(!DEP[i].empty()){
                    ll target_siding = DEP[i].back() / 10;
                    ll c = 0;
                    while(c < sz(DEP[i]) && DEP[i][sz(DEP[i]) - 1 - c] / 10 == target_siding){
                        c++;
                    }
                    cands.push_back({i, target_siding, c});
                }
            }
            
            if (cands.empty()) break;
            
            ll best_mask = 0;
            ll max_moved_cars = -1;
            
            rep(mask, 1, 1 << sz(cands)) {
                bool ok = true;
                ll last_j = -1;
                ll moved_cars = 0;
                
                rep(bit, 0, sz(cands)) {
                    if ((mask >> bit) & 1) {
                        if (cands[bit].j <= last_j) {
                            ok = false;
                            break;
                        }
                        last_j = cands[bit].j;
                        moved_cars += cands[bit].c;
                    }
                }
                
                if (ok && moved_cars > max_moved_cars) {
                    max_moved_cars = moved_cars;
                    best_mask = mask;
                }
            }
            
            vector<Move> turn_moves;
            rep(bit, 0, sz(cands)) {
                if ((best_mask >> bit) & 1) {
                    ll i = cands[bit].i;
                    ll j = cands[bit].j;
                    ll c = cands[bit].c;
                    
                    rep(step, 0, c) {
                        ll val = DEP[i].back(); DEP[i].pop_back();
                        SID[j].push_back(val);
                    }
                    turn_moves.push_back({0, i, j, c});
                }
            }
            ans.push_back(turn_moves);
        }
  
        // ==========================================
        // フェーズ2: Lazy Restore (放置) & Smart Buffering (整理)
        // ==========================================
        rep(i, 0, R){
            rep(target, 10*i, 10*(i+1)){
                
                // 1. ターゲットがどこかのバッファ(DEP)の先頭に露出しているか探す
                ll found_in_dep = -1;
                rep(k, 0, R) {
                    if (k != i && !DEP[k].empty() && DEP[k].back() == target) {
                        found_in_dep = k;
                        break;
                    }
                }

                if (found_in_dep != -1) {
                    // バッファにあった場合：直接DEP->DEPはルール上できないので、SID[i]を経由する
                    ll val = DEP[found_in_dep].back(); DEP[found_in_dep].pop_back();
                    SID[i].push_back(val);
                    ans.push_back(vector<Move>{{0, found_in_dep, i, 1}});
                    
                    val = SID[i].back(); SID[i].pop_back();
                    DEP[i].push_back(val);
                    ans.push_back(vector<Move>{{1, i, i, 1}});
                } else {
                    // 2. ターゲットはSID[i]の中に埋まっているはずなので、出るまでバッファへ退避する
                    while (!SID[i].empty() && SID[i].back() != target) {
                        ll v = SID[i].back(); SID[i].pop_back();
                        
                        ll best_buf = -1;
                        ll best_score = -INF;
                        
                        // 降順（ストレート）になるような美しいバッファ先を選ぶ
                        rep(k, 0, R) {
                            if (k != i && DEP[k].size() < 15) {
                                ll score = 0;
                                if (DEP[k].empty() || DEP[k].back() < 10*i) {
                                    // このグループの車両がまだ積まれていない綺麗な場所
                                    score = 100 + (15 - DEP[k].size());
                                } else {
                                    ll top_v = DEP[k].back();
                                    if (top_v > v) {
                                        // 降順に積める（後で小さいターゲットから先に取り出せる大正解の形）
                                        score = 1000 - (top_v - v);
                                    } else {
                                        // 昇順に積むと、後でターゲットが埋もれるので大減点
                                        score = -10000 - (v - top_v);
                                    }
                                }
                                if (score > best_score) {
                                    best_score = score;
                                    best_buf = k;
                                }
                            }
                        }
                        
                        // 選んだバッファへ退避（戻さず、放置！）
                        DEP[best_buf].push_back(v);
                        ans.push_back(vector<Move>{{1, best_buf, i, 1}});
                    }
                    
                    // ターゲットがSID[i]の先頭に露出したので、本命DEP[i]に入れる
                    ll val = SID[i].back(); SID[i].pop_back();
                    DEP[i].push_back(val);
                    ans.push_back(vector<Move>{{1, i, i, 1}});
                }
            }
        }
    }; GreedyMult();

    out(sz(ans));
    for(auto turn : ans){
        out(sz(turn));
        for(auto m : turn){
            cout << m.type << " " << m.i << " " << m.j << " " << m.k << "\n";
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
    return 0;
}