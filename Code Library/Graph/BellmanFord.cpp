#include <iostream>
#include <vector>
#include <limits>
#include <stdexcept>
#include <algorithm>

class BellmanFord {
public:
    // 辺を表す構造体
    struct Edge {
        int from;
        int to;
        long long weight;
    };

private:
    int numVertices;                 // 頂点数
    std::vector<Edge> edges;         // 辺のリスト
    std::vector<long long> dist;     // 最短距離
    std::vector<int> prevVertex;     // 経路復元用の直前の頂点
    bool hasNegativeCycle;           // グラフ全体に負閉路が存在するか
    std::vector<bool> negAffected;   // その頂点が負閉路の影響を受けるか（距離が-∞になるか）

    static constexpr long long INF = std::numeric_limits<long long>::max() / 2;

public:
    explicit BellmanFord(int n)
        : numVertices(n), hasNegativeCycle(false) {
        if (n <= 0) {
            throw std::invalid_argument("頂点数は1以上である必要があります");
        }
    }

    // 有向辺を追加 (from -> to, 重み weight)
    void addEdge(int from, int to, long long weight) {
        edges.push_back({from, to, weight});
    }

    // 無向辺を追加したい場合はこちらを使う（両方向に辺を張る）
    void addUndirectedEdge(int from, int to, long long weight) {
        addEdge(from, to, weight);
        addEdge(to, from, weight);
    }

    // startを始点として最短距離を計算する
    // 戻り値: true=正常終了, false=負閉路検出
    bool solve(int start) {
        dist.assign(numVertices, INF);
        prevVertex.assign(numVertices, -1);
        negAffected.assign(numVertices, false);
        dist[start] = 0;
        hasNegativeCycle = false;

        // V-1回、全辺を緩和
        for (int i = 0; i < numVertices - 1; ++i) {
            bool updated = false;
            for (const auto& e : edges) {
                if (dist[e.from] == INF) continue;
                if (dist[e.from] + e.weight < dist[e.to]) {
                    dist[e.to] = dist[e.from] + e.weight;
                    prevVertex[e.to] = e.from;
                    updated = true;
                }
            }
            if (!updated) break; // これ以上更新がなければ終了
        }

        // V回目でまだ緩和できる辺の終点は、負閉路の影響を直接受ける頂点
        for (const auto& e : edges) {
            if (dist[e.from] == INF) continue;
            if (dist[e.from] + e.weight < dist[e.to]) {
                hasNegativeCycle = true;
                negAffected[e.to] = true;
            }
        }

        // 影響をグラフ全体に伝播させる（負閉路→そこから到達できる頂点は全て距離が-∞扱い）
        for (int i = 0; i < numVertices; ++i) {
            bool updated = false;
            for (const auto& e : edges) {
                if (negAffected[e.from] && !negAffected[e.to] && dist[e.to] < INF) {
                    negAffected[e.to] = true;
                    updated = true;
                }
            }
            if (!updated) break;
        }

        return !hasNegativeCycle;
    }

    // 負閉路が検出されたかどうか
    bool hasNegativeCycleDetected() const {
        return hasNegativeCycle;
    }

    // 頂点vへの最短距離を取得（到達不可ならINFを返す）
    long long getDistance(int v) const {
        if (v < 0 || v >= numVertices) {
            throw std::out_of_range("頂点番号が範囲外です");
        }
        return dist[v];
    }

    // 到達可能かどうか
    bool isReachable(int v) const {
        return dist[v] < INF;
    }

    // solve(start) 実行後に呼ぶ。
    // start から v への経路が負閉路の影響を受けるか（＝最短距離が定義不能=-∞相当）を判定する。
    // true の場合、start→v間には「通過することで距離をいくらでも小さくできる負閉路」が存在する。
    bool isPathAffectedByNegativeCycle(int v) const {
        if (v < 0 || v >= numVertices) {
            throw std::out_of_range("頂点番号が範囲外です");
        }
        return negAffected[v];
    }

    // startからvまでの経路を復元（頂点番号の列）
    std::vector<int> getPath(int v) const {
        std::vector<int> path;
        if (!isReachable(v)) return path; // 空

        for (int cur = v; cur != -1; cur = prevVertex[cur]) {
            path.push_back(cur);
        }
        std::reverse(path.begin(), path.end());
        return path;
    }

    static long long infinity() { return INF; }
};

// ---------------- 使用例 ----------------

int main() {
    // ---- 例1: 全体に負閉路があっても、影響を受けない頂点もある例 ----
    // 頂点構成:
    //   0 -> 1 (負閉路 1<->2 が存在)
    //   0 -> 3 (負閉路を通らずに行ける独立した経路)
    //
    //   0 --5--> 1 --(-3)--> 2 --1--> 1   (1<->2 が負閉路: -3+1=-2)
    //   0 --10--> 3                      (3は負閉路と無関係)
    BellmanFord bf(4);
    bf.addEdge(0, 1, 5);
    bf.addEdge(1, 2, -3);
    bf.addEdge(2, 1, 1);   // 1 -> 2 -> 1 のサイクルの合計重みは -3+1 = -2 (負閉路)
    bf.addEdge(0, 3, 10);  // 3へは負閉路を経由せず到達できる

    int start = 0;
    bf.solve(start);

    std::cout << "=== 例1: 部分的な負閉路の影響 ===\n";
    std::cout << "全体として負閉路あり: " << (bf.hasNegativeCycleDetected() ? "あり" : "なし") << "\n";

    for (int v = 0; v < 4; ++v) {
        std::cout << "  " << start << " -> " << v << " : ";
        if (bf.isPathAffectedByNegativeCycle(v)) {
            std::cout << "負閉路の影響あり（距離は-∞、最短距離未定義）\n";
        } else if (bf.isReachable(v)) {
            std::cout << "最短距離 = " << bf.getDistance(v) << "\n";
        } else {
            std::cout << "到達不可\n";
        }
    }
    // 期待結果: 0->1, 0->2 は影響あり。0->3 は負閉路と無関係なので影響なし（距離10）。

    std::cout << "\n=== 例2: 元のグラフ（負閉路なし） ===\n";
    BellmanFord bf2(5);
    bf2.addEdge(0, 1, 6);
    bf2.addEdge(0, 2, 7);
    bf2.addEdge(1, 2, 8);
    bf2.addEdge(1, 3, 5);
    bf2.addEdge(1, 4, -4);
    bf2.addEdge(2, 3, -3);
    bf2.addEdge(2, 4, 9);
    bf2.addEdge(3, 1, -2);
    bf2.addEdge(4, 3, 7);
    bf2.addEdge(4, 0, 2);

    if (bf2.solve(0)) {
        for (int v = 0; v < 5; ++v) {
            if (bf2.isReachable(v)) {
                std::cout << "  -> " << v << " : " << bf2.getDistance(v);
                std::cout << "  経路: ";
                for (int p : bf2.getPath(v)) std::cout << p << " ";
                std::cout << "\n";
            } else {
                std::cout << "  -> " << v << " : 到達不可\n";
            }
        }
    } else {
        std::cout << "負閉路が検出されました。\n";
    }

    return 0;
}
