// =====================================================================
//  cycle.hpp - Cycle Detection Library for Competitive Programming
// ---------------------------------------------------------------------
//  - 有向グラフ・無向グラフどちらにも対応
//  - 0-indexed で頂点番号を扱う（add_edge は 0-indexed で渡す）
//  - has_cycle()  : サイクルが存在するかを bool で返す
//  - find_cycle() : サイクルの頂点列を vector<int> で返す（無ければ空）
//                   有向: v0 -> v1 -> ... -> vk -> v0  （v0 は 1 度だけ含む）
//                   無向: v0 - v1 - ... - vk - v0
//  - 計算量 O(N + M)
//  - 反復DFSで実装しているのでスタックオーバーフロー耐性あり
//  - 自己ループ・多重辺どちらも正しく検出
// =====================================================================
#include <bits/stdc++.h>

struct CycleDetection {
    int n;                                                     // 頂点数
    bool directed;                                             // true: 有向, false: 無向
    std::vector<std::vector<std::pair<int, int>>> g;           // g[u] = {(to, edge_id), ...}
    int m;                                                     // 辺数

    explicit CycleDetection(int n_, bool directed_)
        : n(n_), directed(directed_), g(n_), m(0) {}

    // 辺を追加 (0-indexed)。自己ループ u==v も OK（有向・無向どちらでもサイクル扱い）
    void add_edge(int u, int v) {
        g[u].emplace_back(v, m);
        if (!directed) g[v].emplace_back(u, m);
        ++m;
    }

    // サイクル(閉路)を構成する頂点列を返す。無ければ空 vector。
    std::vector<int> find_cycle() {
        std::vector<int> color(n, 0);    // 0:未訪問, 1:訪問中(灰), 2:訪問済(黒)
        std::vector<int> par(n, -1);     // DFS 親
        std::vector<int> par_eid(n, -1); // u に入ってきた辺の id（無向で逆走を防ぐため）
        std::vector<int> cycle;

        for (int s = 0; s < n; ++s) {
            if (color[s] != 0) continue;

            std::vector<std::pair<int, int>> stk; // {頂点, 次に見る隣接の index}
            stk.emplace_back(s, 0);
            color[s] = 1;

            while (!stk.empty()) {
                auto& [u, i] = stk.back();
                if (i == (int)g[u].size()) {
                    color[u] = 2;
                    stk.pop_back();
                    continue;
                }
                auto [v, eid] = g[u][i++];

                // 無向では「来た辺そのもの」を逆走しない（多重辺は別 eid なので別扱い）
                if (!directed && eid == par_eid[u]) continue;

                if (color[v] == 0) {
                    color[v] = 1;
                    par[v] = u;
                    par_eid[v] = eid;
                    stk.emplace_back(v, 0);
                } else if (color[v] == 1) {
                    // 後退辺発見: v -> ... -> u -> v が閉路
                    cycle.push_back(v);
                    int cur = u;
                    while (cur != v) {
                        cycle.push_back(cur);
                        cur = par[cur];
                    }
                    std::reverse(cycle.begin(), cycle.end());
                    return cycle;
                }
                // 有向で color[v]==2 は cross/forward edge なので無視
            }
        }
        return {};
    }

    bool has_cycle() { return !find_cycle().empty(); }
};

// =====================================================================
//  使い方サンプル
// ---------------------------------------------------------------------
//  // 有向グラフ
//  CycleDetection cd(N, true);
//  for (auto [u, v] : edges) cd.add_edge(u, v);   // u, v は 0-indexed
//  auto cyc = cd.find_cycle();
//  if (cyc.empty()) cout << "No cycle\n";
//  else {
//      cout << "Cycle length = " << cyc.size() << "\n";
//      for (int v : cyc) cout << v + 1 << " ";    // 1-indexed で出力するなら +1
//  }
//
//  // 無向グラフ
//  CycleDetection cd(N, false);
//  for (auto [u, v] : edges) cd.add_edge(u, v);
//  bool ok = cd.has_cycle();
// =====================================================================
