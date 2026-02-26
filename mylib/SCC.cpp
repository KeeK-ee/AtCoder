#include <vector>

struct scc_graph {
    int n;
    std::vector<std::vector<int>> g, rg;
    std::vector<int> order;
    std::vector<bool> used;

    // コンストラクタ: n頂点のグラフを初期化
    scc_graph(int _n) : n(_n), g(_n), rg(_n) {}

    // 有向辺を追加 (計算量: O(1))
    void add_edge(int from, int to) {
        g[from].push_back(to);
        rg[to].push_back(from); // 逆辺も張る
    }

    // 1回目のDFS用 (帰りがけ順を記録)
    void dfs(int v) {
        used[v] = true;
        for (int u : g[v]) {
            if (!used[u]) dfs(u);
        }
        order.push_back(v);
    }

    // 2回目のDFS用 (逆辺を使って強連結成分を抽出)
    void rdfs(int v, std::vector<int>& comp) {
        used[v] = true;
        comp.push_back(v);
        for (int u : rg[v]) {
            if (!used[u]) rdfs(u);
        }
    }

    // 強連結成分分解を実行し、トポロジカルソートされた成分のリストを返す
    // 計算量: O(V + E)
    std::vector<std::vector<int>> scc() {
        used.assign(n, false);
        order.clear();
        // 1回目のDFS
        for (int i = 0; i < n; i++) {
            if (!used[i]) dfs(i);
        }
        
        used.assign(n, false);
        std::vector<std::vector<int>> res;
        // 記録した帰りがけ順の逆順に2回目のDFS
        for (int i = n - 1; i >= 0; i--) {
            int v = order[i];
            if (!used[v]) {
                std::vector<int> comp;
                rdfs(v, comp);
                res.push_back(comp);
            }
        }
        return res;
    }
};