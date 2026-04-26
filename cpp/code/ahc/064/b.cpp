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
using vpll = vector<pair<ll, ll>>;
using vl = vector<ll>;
using vvl = vector<vl>;
const ll INF = 8'000'000'000'000'000'000LL; 

#define rep(i, a, n) for (ll i = a; i < (ll)(n); ++i)
#define sz(x) (ll)(x).size()
#define out(x) cout << x << "\n"

struct Move {
    ll type; // 0: DEP->SID, 1: SID->DEP
    ll i;    // DEP index
    ll j;    // SID index
    ll k;    // 個数
};

void solve() {
    vector<vector<Move>> ans;

    auto GreedyFinal = [&]() -> void {
        ll R; cin >> R;
        vvl DEP(R); 
        vvl SID(R); 
        rep(i, 0, R)rep(j, 0, 10){
            ll y; cin >> y;
            DEP[i].push_back(y);
        }

        // ==========================================
        // フェーズ1: 目的地ごとの待避線へ並列振り分け
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
            
            ll best_mask = 0, max_moved_cars = -1;
            rep(mask, 1, 1 << sz(cands)) {
                bool ok = true; ll last_j = -1, moved_cars = 0;
                rep(bit, 0, sz(cands)) {
                    if ((mask >> bit) & 1) {
                        if (cands[bit].j <= last_j) { ok = false; break; }
                        last_j = cands[bit].j; moved_cars += cands[bit].c;
                    }
                }
                if (ok && moved_cars > max_moved_cars) {
                    max_moved_cars = moved_cars; best_mask = mask;
                }
            }
            
            vector<Move> turn_moves;
            rep(bit, 0, sz(cands)) {
                if ((best_mask >> bit) & 1) {
                    ll i = cands[bit].i, j = cands[bit].j, c = cands[bit].c;
                    rep(step, 0, c) {
                        // フェイルセーフ
                        if (DEP[i].empty()) break;
                        ll val = DEP[i].back(); DEP[i].pop_back();
                        SID[j].push_back(val);
                    }
                    turn_moves.push_back({0, i, j, c});
                }
            }
            if (!turn_moves.empty()) ans.push_back(turn_moves);
            else break;
        }
  
        // ==========================================
        // フェーズ2: Lazy Restore の完全並列化 ＋ 安全装置
        // ==========================================
        vl target_val(R); 
        rep(i, 0, R) target_val[i] = 10 * i;

        while (true) {
            bool all_done = true;
            struct Task { ll type, i, j, priority, track_id; };
            vector<Task> potential_tasks;

            rep(i, 0, R) {
                if (target_val[i] >= 10 * (i + 1)) continue;
                all_done = false;

                ll target = target_val[i];
                ll loc_sid_top = -1, loc_dep_top = -1;
                ll loc_sid_buried = -1, loc_dep_buried = -1;

                rep(j, 0, R) {
                    if (!SID[j].empty() && SID[j].back() == target) loc_sid_top = j;
                    for (ll val : SID[j]) if (val == target) loc_sid_buried = j;
                    
                    if (j != i) { 
                        if (!DEP[j].empty() && DEP[j].back() == target) loc_dep_top = j;
                        for (ll val : DEP[j]) if (val == target) loc_dep_buried = j;
                    }
                }

                if (loc_sid_top != -1) {
                    potential_tasks.push_back({1, i, loc_sid_top, 3, i});
                } else if (loc_dep_top != -1) {
                    if (SID[i].size() < 20) {
                        potential_tasks.push_back({0, loc_dep_top, i, 2, i});
                    }
                } else if (loc_sid_buried != -1) {
                    if (SID[loc_sid_buried].empty()) continue; // 安全装置
                    ll v = SID[loc_sid_buried].back();
                    
                    ll best_buf = -1, best_score = -INF;
                    rep(k, 0, R) {
                        if (k != i && DEP[k].size() < 15) {
                            ll score = 0;
                            if (DEP[k].empty() || DEP[k].back() < 10*i) {
                                score = 100 + (15 - DEP[k].size());
                            } else {
                                ll top_v = DEP[k].back();
                                if (top_v > v) score = 1000 - (top_v - v); 
                                else score = -10000 - (v - top_v); 
                            }
                            if (score > best_score) { best_score = score; best_buf = k; }
                        }
                    }
                    if (best_buf != -1) potential_tasks.push_back({1, best_buf, loc_sid_buried, 1, i});
                } else if (loc_dep_buried != -1) {
                    if (DEP[loc_dep_buried].empty()) continue; // 安全装置
                    
                    ll best_sid = -1, best_score = -INF;
                    rep(k, 0, R) {
                        if (SID[k].size() < 20) {
                            ll score = 20 - SID[k].size();
                            if (k == i) score += 50; 
                            if (score > best_score) { best_score = score; best_sid = k; }
                        }
                    }
                    if (best_sid != -1) potential_tasks.push_back({0, loc_dep_buried, best_sid, 1, i});
                }
            }

            if (all_done) break;

            sort(potential_tasks.begin(), potential_tasks.end(), [](const Task& a, const Task& b){
                return a.priority > b.priority;
            });

            vector<Move> turn;
            vector<bool> d_used(R, false), s_used(R, false);
            vector<Task> selected;

            auto is_intersect = [&](const vector<Task>& current, Task next) {
                for (auto& c : current) {
                    if ((c.i < next.i && c.j >= next.j) || (c.i > next.i && c.j <= next.j)) return true;
                }
                return false;
            };

            for (auto& task : potential_tasks) {
                if (d_used[task.i] || s_used[task.j]) continue; 
                if (is_intersect(selected, task)) continue;     

                // 実行直前の超厳密な安全装置。空ならタスクをキャンセルしてスキップ
                if (task.type == 0 && DEP[task.i].empty()) continue;
                if (task.type == 1 && SID[task.j].empty()) continue;

                d_used[task.i] = s_used[task.j] = true;
                selected.push_back(task);
                
                if (task.type == 0) { // DEP -> SID
                    ll val = DEP[task.i].back(); DEP[task.i].pop_back();
                    SID[task.j].push_back(val);
                } else { // SID -> DEP
                    ll val = SID[task.j].back(); SID[task.j].pop_back();
                    DEP[task.i].push_back(val);
                    if (task.i == task.track_id && val == target_val[task.track_id]) {
                        target_val[task.track_id]++;
                    }
                }
                turn.push_back({task.type, task.i, task.j, 1}); 
            }

            // 完全デッドロック防止
            if (turn.empty()) break; 

            ans.push_back(turn);
        }
    }; GreedyFinal();

    out(sz(ans));
    for(auto turn : ans){
        out(sz(turn));
        for(auto m : turn){
            cout << m.type << " " << m.i << " " << m.j << " " << 1 << "\n";
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
    return 0;
}