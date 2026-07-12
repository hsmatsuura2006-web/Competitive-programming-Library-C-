struct AhoCorasick {
    // 1つのノード（状態）を表す構造体
    struct Node {
        // next[c] : 文字 c ('a'〜'z' を 0〜25 に変換) が来たときの次のノードID。なければ -1
        int next[26];
        
        // fail : 最長サフィックス（接尾部）を表すノードのID（いわゆる失敗リンク）
        int fail = 0;
        
        // is_ng : このノード自体、あるいはサフィックスリンクの先が禁止ワードなら true
        bool is_ng = false;
        
        // デバッグ用：このノードが表している文字列（空文字なら ""）
        std::string str = "";

        Node() { std::fill(next, next + 26, -1); }
    };

    // オートマトン全体のノードの配列。nodes[0] がルート（空文字）
    std::vector<Node> nodes;

    AhoCorasick() {
        nodes.emplace_back(); // ルートノードを ID: 0 として作成
    }

    // ----------------------------------------------------
    // フェーズ 1: 通常のトライ木（プレフィックスツリー）の構築
    // ----------------------------------------------------
    void insert(const std::string& s) {
        int cur = 0; // ルートからスタート
        for (char c : s) {
            int idx = c - 'a';
            // 次の文字に対応するノードがまだなければ、新しく作る（中間ノードの生成）
            if (nodes[cur].next[idx] == -1) {
                nodes[cur].next[idx] = nodes.size();
                Node new_node;
                new_node.str = nodes[cur].str + c; // デバッグ用に文字列を記録
                nodes.push_back(new_node);
            }
            cur = nodes[cur].next[idx]; // 次のノードへ進む
        }
        nodes[cur].is_ng = true; // 単語の末尾なので禁止マークを付ける
    }

    // ----------------------------------------------------
    // フェーズ 2: サフィックス（失敗）リンクの構築（BFSによる平坦化）
    // ----------------------------------------------------
    void build() {
        std::queue<int> que;

        // 準備：ルート（長さ0）の直下にある、長さ1のノードをキューに入れる
        for (int i = 0; i < 26; i++) {
            if (nodes[0].next[i] != -1) {
                // 長さ1の文字列の「自分自身を除いた最長サフィックス」は空文字（ルート）
                nodes[nodes[0].next[i]].fail = 0; 
                que.push(nodes[0].next[i]);
            } else {
                // ルートからその文字への遷移がない場合は、ルート自身に戻るようにしておく
                nodes[0].next[i] = 0;
            }
        }

        // 幅優先探索（BFS）で短いノードから順にリンクを決定していく
        while (!que.empty()) {
            int cur = que.front();
            que.pop();

            // 【道連れ判定】
            // もし自分の最長サフィックスの先（fail）がNGワードなら、自分自身もNGにする
            if (nodes[nodes[cur].fail].is_ng) {
                nodes[cur].is_ng = true;
            }

            // 子ノード（次の文字）へのリンクを確定させる
            for (int i = 0; i < 26; i++) {
                if (nodes[cur].next[i] != -1) {
                    int child = nodes[cur].next[i];
                    // 子ノードの最長サフィックス先は、「親のサフィックス先から、同じ文字 i で進んだ場所」
                    nodes[child].fail = nodes[nodes[cur].fail].next[i];
                    que.push(child);
                } else {
                    // もし文字 i の遷移がなければ、「サフィックス先が文字 i で行くはずだった場所」をコピーして先回りしておく
                    // ※これによって、実行時に一発で正しいサフィックスにワープできるようになります（平坦化）
                    nodes[cur].next[i] = nodes[nodes[cur].fail].next[i];
                }
            }
        }
    }
};

int main() {
    AhoCorasick ac;
    
    // 禁止ワードを登録してみる
    ac.insert("abc");
    ac.insert("bc");

    // 最長サフィックスリンク（オートマトン）を構築
    ac.build();

    // 構築されたノードの状態を覗いてみよう！
    std::cout << "--- 構築されたノードとサフィックスリンクの一覧 ---" << std::endl;
    for (size_t i = 0; i < ac.nodes.size(); i++) {
        auto& node = ac.nodes[i];
        std::cout << "ノードID: " << i 
                  << " | 表す文字列: \"" << node.str << "\""
                  << " | サフィックスリンク先(fail): " << node.fail 
                  << " (\"" << ac.nodes[node.fail].str << "\")"
                  << " | NG判定: " << (node.is_ng ? "NG!" : "安全") 
                  << std::endl;
    }
    return 0;
}
