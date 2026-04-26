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
#define fix cout << fixed <<  setprecision(15)
#define se second
#define fi first

ll ceilDiv (ll x, ll y){if(x >= 0){return (x+y-1)/y;}else{return x/y;}}
ll floorDiv (ll x, ll y){if(x >= 0){return x/y;}else{return (x-y+1)/y;}}

template <typename T>
void debug_print(const vector<T>& v) {
    for (int i = 0; i < (int)v.size(); ++i) {
        cerr << v[i] << (i == (int)v.size() - 1 ? "" : " ");
    }
    cerr << "\n";
}
template <typename T>
void debug_print(const vector<vector<T>>& v) {
    for (const auto& row : v) {
        debug_print(row);
    }
}

template<class T> bool chmax(T &a, const T &b) {
    if (a < b) { a = b; return true; }
    return false;
}
template<class T> bool chmin(T &a, const T &b) {
    if (a > b) { a = b; return true; }
    return false;
}

struct Move
{
    ll type;
    ll i;
    ll j;
    ll k;
};

void solve() {
    // ロジックをちゃんと考える！！！

    vector<vector<Move>> ans;

    /**
     * 正の得点を獲得する
     */
    // auto ZERO = []() -> void {
    //     out(0);
    // }; ZERO();

    /**
     * 毎ターンK=1として簡単に実装する
     * 左の出発線上の車両から「目的の出発線に対する待避線」へ移動させる
     * 左の待避線上の車両から「目的の出発線」へ移動させる 邪魔な車両は一時的に空き容量のある他の出発線（バッファ）に退避させる
     */
    // auto Greedy1 = [&]() -> void {
    //     // 入力
    //     ll R; cin >> R;
    //     vvl DEP(R); // 出発線
    //     vvl SID(R); // 待避線
    //     rep(i, 0, R)rep(j, 0, 10){
    //         ll y; cin >> y;
    //         DEP[i].push_back(y);
    //     }

    //     rep(i, 0, R){
    //         while(!DEP[i].empty()){
    //             ll v=DEP[i].back(); DEP[i].pop_back();
    //             SID[v/10].push_back(v);
    //             ans.push_back(Move{0, i, v/10, 1});
    //         }
    //     }
  
    //     rep(i, 0, R){
    //         rep(target, 10*i, 10*(i+1)){
    //             vl history;
    //             while (!SID[i].empty()) {
    //                 ll v=SID[i].back(); SID[i].pop_back();
                    
    //                 if (v==target) {
    //                     // ターゲットが見つかったら、本命の出発線 j に入れる
    //                     DEP[i].push_back(v);
    //                     ans.push_back({1, i, i, 1});
    //                     break;
    //                 } else {
    //                     // ターゲットでない場合、空き容量のある他の出発線（バッファ）に一時退避
    //                     ll buf_i=-1;
    //                     rep(k, 0, R) {
    //                         if (k != i && DEP[k].size() < 15) {
    //                             buf_i=k; break;
    //                         }
    //                     }
    //                     DEP[buf_i].push_back(v);
    //                     ans.push_back({1, buf_i, i, 1});
    //                     history.push_back(buf_i); // どこに退避したか記録
    //                 }
    //             }
                
    //             // ターゲットを移動し終えたら、一時退避していた車両を待避線 j に戻す
    //             while (!history.empty()) {
    //                 ll buf_i = history.back(); history.pop_back();
                    
    //                 ll v=DEP[buf_i].back();
    //                 DEP[buf_i].pop_back();
                    
    //                 SID[i].push_back(v);
    //                 ans.push_back({0, buf_i, i, 1});
    //             }
    //         }
    //     }
    // }; Greedy1();

    /**
     * k車両をまとめて移動
     */
    // auto Greedy2 = [&]() -> void {
    //     // 入力
    //     ll R; cin >> R;
    //     vvl DEP(R); // 出発線
    //     vvl SID(R); // 待避線
    //     rep(i, 0, R)rep(j, 0, 10){
    //         ll y; cin >> y;
    //         DEP[i].push_back(y);
    //     }

    //     rep(i, 0, R){
    //         while(!DEP[i].empty()){
    //             ll v=DEP[i].back(); DEP[i].pop_back();
    //             SID[v/10].push_back(v);
    //             ll c=1;
    //             while(!DEP[i].empty() && DEP[i].back()/10==v/10){
    //                 v=DEP[i].back(); DEP[i].pop_back();
    //                 SID[v/10].push_back(v);
    //                 c++;
    //             }
    //             ans.push_back(Move{0, i, v/10, c});
    //         }
    //     }
  
    //     rep(i, 0, R){
    //         rep(target, 10*i, 10*(i+1)){
    //             vpll history;
    //             // ターゲット車両の位置を探す
    //             ll target_idx=-1;
    //             rep(p, 0, sz(SID[i])) {
    //                 if (SID[i][p] == target) {
    //                     target_idx = p; break;
    //                 }
    //             }
    //             // ターゲットの上に乗っている「邪魔な車両」の数
    //             ll block_k=sz(SID[i])-1-target_idx;

    //             // 邪魔な車両をバッファにまとめて退避させる
    //             while (block_k>0) {
    //                 ll best_buf = -1;
    //                 ll max_space = -1;
                    
    //                 // 最も空き容量の大きい出発線（バッファ）を探す
    //                 rep(k, 0, R) {
    //                     if (k != i) {
    //                         ll space = 15 - sz(DEP[k]);
    //                         if (space > max_space) {
    //                             max_space = space;
    //                             best_buf = k;
    //                         }
    //                     }
    //                 }

    //                 // バッファの空き容量か、退避させたい数のうち「小さい方」の数だけ一気に動かす
    //                 ll move_k = min(block_k, max_space);
                    
    //                 // 1両ずつのpop/pushを繰り返してブロック移動をシミュレーション
    //                 rep(step, 0, move_k) {
    //                     ll val = SID[i].back(); SID[i].pop_back();
    //                     DEP[best_buf].push_back(val);
    //                 }
                    
    //                 ans.push_back({1, best_buf, i, move_k});
    //                 history.push_back({best_buf, move_k});
    //                 block_k -= move_k;
    //             }
                
    //             // ターゲットが一番上に来たので、本命の出発線に入れる
    //             ll v = SID[i].back(); SID[i].pop_back();
    //             DEP[i].push_back(v);
    //             ans.push_back({1, i, i, 1});
                
    //             // 履歴を逆順に辿って、バッファから待避線へまとめて戻す
    //             while (!history.empty()) {
    //                 auto [buf_i, move_k] = history.back(); history.pop_back();
                    
    //                 // これも1両ずつのpop/pushで完璧にシミュレーション
    //                 rep(step, 0, move_k) {
    //                     ll val = DEP[buf_i].back(); DEP[buf_i].pop_back();
    //                     SID[i].push_back(val);
    //                 }
                    
    //                 ans.push_back({0, buf_i, i, move_k});
    //             }
    //         }
    //     }
    // }; Greedy2();

    auto GreedyMult = [&]() -> void {
        // 入力
        ll R; cin >> R;
        vvl DEP(R); // 出発線
        vvl SID(R); // 待避線
        rep(i, 0, R)rep(j, 0, 10){
            ll y; cin >> y;
            DEP[i].push_back(y);
        }

        // ==========================================
        // フェーズ1: 目的地ごとの待避線へ振り分け（並列実行版）
        // ==========================================
        while (true) {
            struct Cand { ll i, j, c; };
            vector<Cand> cands;
            
            // 1. 各出発線の末尾を確認し、移動候補をリストアップ
            rep(i, 0, R){
                if(!DEP[i].empty()){
                    ll target_siding = DEP[i].back() / 10;
                    ll c = 0;
                    // 同じ待避線に行く車両がいくつ連続しているか数える
                    while(c < sz(DEP[i]) && DEP[i][sz(DEP[i]) - 1 - c] / 10 == target_siding){
                        c++;
                    }
                    cands.push_back({i, target_siding, c});
                }
            }
            
            // すべての出発線が空になればフェーズ1終了
            if (cands.empty()) break;
            
            // 2. 交差しない（jが単調増加になる）最大の組み合わせをbit全探索で探す
            ll best_mask = 0;
            ll max_moved_cars = -1;
            
            rep(mask, 1, 1 << sz(cands)) {
                bool ok = true;
                ll last_j = -1;
                ll moved_cars = 0;
                
                rep(bit, 0, sz(cands)) {
                    if ((mask >> bit) & 1) {
                        // 出発線iは昇順で登録されているため、待避線jが単調増加なら交差しない
                        if (cands[bit].j <= last_j) {
                            ok = false;
                            break;
                        }
                        last_j = cands[bit].j;
                        moved_cars += cands[bit].c;
                    }
                }
                
                // より多くの車両を動かせる組み合わせを記録
                if (ok && moved_cars > max_moved_cars) {
                    max_moved_cars = moved_cars;
                    best_mask = mask;
                }
            }
            
            // 3. 選ばれた操作を1ターンとしてまとめて実行
            vector<Move> turn_moves;
            rep(bit, 0, sz(cands)) {
                if ((best_mask >> bit) & 1) {
                    ll i = cands[bit].i;
                    ll j = cands[bit].j;
                    ll c = cands[bit].c;
                    
                    // ブロック移動のシミュレーション
                    rep(step, 0, c) {
                        ll val = DEP[i].back(); DEP[i].pop_back();
                        SID[j].push_back(val);
                    }
                    turn_moves.push_back({0, i, j, c});
                }
            }
            ans.push_back(turn_moves);
        }
  
        // --- フェーズ2: 各線独立した状態マシンによる並列ソート ---
        vl target_val(R); 
        for(ll i=0; i<R; ++i) target_val[i] = 10 * i;
        
        // 各線の作業状態: 0:ターゲット待ち/退避中, 1:復元待ち
        vl mode(R, 0); 
        vector<vector<pair<ll, ll>>> history(R); // {buf_i, count}

        while (true) {
            bool all_done = true;
            struct Task { ll type, i, j, k, track_id; };
            vector<Task> potential_tasks;

            for (ll t = 0; t < R; ++t) {
                if (target_val[t] >= 10 * (t + 1)) continue;
                all_done = false;

                if (mode[t] == 0) {
                    // ターゲットを探す
                    ll idx = -1;
                    for (ll p = 0; p < (ll)SID[t].size(); ++p) if (SID[t][p] == target_val[t]) { idx = p; break; }

                    if (idx == (ll)SID[t].size() - 1) {
                        // ターゲットが先頭にある -> 出発線へ
                        potential_tasks.push_back({1, t, t, 1, t});
                    } else {
                        // 邪魔な車を退避
                        ll block_k = (ll)SID[t].size() - 1 - idx;
                        ll best_buf = -1, max_s = -1;
                        for (ll b = 0; b < R; ++b) {
                            if (b == t) continue;
                            ll s = 15 - (ll)DEP[b].size();
                            if (s > max_s) { max_s = s; best_buf = b; }
                        }
                        ll move_k = min(block_k, max_s);
                        if (move_k > 0) potential_tasks.push_back({1, best_buf, t, move_k, t});
                    }
                } else {
                    // 復元モード
                    if (!history[t].empty()) {
                        auto [buf_i, count] = history[t].back();
                        potential_tasks.push_back({0, buf_i, t, count, t});
                    } else {
                        mode[t] = 0; // 次のターゲットへ
                    }
                }
            }
            if (all_done) break;

            // 欲張りに交差しないタスクを選択 (DEPとSIDの重複使用も禁止)
            vector<Move> turn;
            vector<bool> d_used(R, false), s_used(R, false);
            
            // 交差判定のために i(DEP) と j(SID) をチェック
            // Task内の i=出発線, j=待避線
            auto is_intersect = [&](const vector<Task>& current, Task next) {
                for (auto& c : current) {
                    // (i1 < i2 かつ j1 >= j2) または (i1 > i2 かつ j1 <= j2) なら交差
                    if ((c.i < next.i && c.j >= next.j) || (c.i > next.i && c.j <= next.j)) return true;
                }
                return false;
            };

            vector<Task> selected;
            for (auto& task : potential_tasks) {
                if (d_used[task.i] || s_used[task.j]) continue;
                if (is_intersect(selected, task)) continue;

                // 実行
                d_used[task.i] = s_used[task.j] = true;
                selected.push_back(task);
                
                if (task.type == 1) { // SID -> DEP
                    for (ll s = 0; s < task.k; ++s) { DEP[task.i].push_back(SID[task.j].back()); SID[task.j].pop_back(); }
                    if (task.i == task.j) target_val[task.track_id]++; // ターゲット移動成功
                    else history[task.track_id].push_back({task.i, task.k}); // 退避
                    
                    // 全てのターゲットを入れ終えたら復元モードへ（または継続）
                    if (task.i == task.j && target_val[task.track_id] % 10 == 0) mode[task.track_id] = 1;
                    else if (task.i == task.j) {} // 次のターゲットを探す
                } else { // DEP -> SID
                    for (ll s = 0; s < task.k; ++s) { SID[task.j].push_back(DEP[task.i].back()); DEP[task.i].pop_back(); }
                    history[task.track_id].pop_back();
                }
                turn.push_back({task.type, task.i, task.j, task.k});
            }
            if (!turn.empty()) ans.push_back(turn);
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