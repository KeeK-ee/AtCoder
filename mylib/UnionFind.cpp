#include <vector>
#include <numeric>
#include <utility>

struct UnionFind {
    // 根の場合は -1 * (そのグループのサイズ) を格納し、
    // それ以外の場合は親のインデックスを格納する
    std::vector<int> parent_or_size;

    // コンストラクタ: n頂点で初期化
    UnionFind(int n) : parent_or_size(n, -1) {}

    // 頂点 a の代表元を返す (経路圧縮)
    int leader(int a) {
        if (parent_or_size[a] < 0) {
            return a; // 自分が根
        }
        // 親をたどりながら根に直接つなぎ直す
        return parent_or_size[a] = leader(parent_or_size[a]);
    }

    // 頂点 a と b を連結する (サイズによるマージ)
    // ACLに合わせて、マージ後の代表元を返す
    int merge(int a, int b) {
        int x = leader(a);
        int y = leader(b);
        if (x == y) return x; // すでに同じグループ
        
        // サイズが大きい方に小さい方をくっつける
        if (-parent_or_size[x] < -parent_or_size[y]) {
            std::swap(x, y);
        }
        
        parent_or_size[x] += parent_or_size[y]; // サイズを更新
        parent_or_size[y] = x; // yの親をxにする
        return x;
    }

    // 頂点 a と b が同じ連結成分に属するか判定
    bool same(int a, int b) {
        return leader(a) == leader(b);
    }

    // 頂点 a が属する連結成分のサイズを返す
    int size(int a) {
        return -parent_or_size[leader(a)];
    }

    // グラフを連結成分に分け、「1つの連結成分の頂点番号のリスト」のリストを返す
    // 計算量: O(N)
    std::vector<std::vector<int>> groups() {
        int n = parent_or_size.size();
        std::vector<int> leader_buf(n), group_size(n);
        for (int i = 0; i < n; i++) {
            leader_buf[i] = leader(i);
            group_size[leader_buf[i]]++;
        }
        
        std::vector<std::vector<int>> result(n);
        for (int i = 0; i < n; i++) {
            result[i].reserve(group_size[i]); // メモリの再確保を防ぐ
        }
        for (int i = 0; i < n; i++) {
            result[leader_buf[i]].push_back(i);
        }
        
        // 空のリストを除外して詰める
        std::vector<std::vector<int>> final_result;
        for (int i = 0; i < n; i++) {
            if (!result[i].empty()) {
                final_result.push_back(std::move(result[i]));
            }
        }
        return final_result;
    }
};