#include <iostream>
#include <vector>
#include <numeric>

using namespace std;
using ll = long long;

// 重み付きUnion-Find
struct PotentializedUnionFind {
    vector<int> par;
    vector<ll> weight;

    PotentializedUnionFind(int n) {
        par.resize(n);
        iota(par.begin(), par.end(), 0);
        weight.assign(n, 0);
    }

    int find(int x) {
        if (par[x] == x) {
            return x;
        }
        int root = find(par[x]);
        weight[x] += weight[par[x]];
        return par[x] = root;
    }

    void merge(int x, int y, ll w) {
        int rx = find(x);
        int ry = find(y);
        if (rx == ry) return;
        par[ry] = rx;
        weight[ry] = w + weight[x] - weight[y];
    }

    bool same(int x, int y) {
        return find(x) == find(y);
    }

    ll diff(int x, int y) {
        // yの重み - xの重み (B_y - B_x)
        return weight[y] - weight[x];
    }
};