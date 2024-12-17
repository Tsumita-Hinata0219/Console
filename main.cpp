#include <iostream>
#include <string>
#include <memory>
#include <vector>
#include <algorithm>
#include <queue>
#include <map>
using namespace std;




void get_distribution(string s, map<char, int>& dist) {
    for (int i = 0; i < (int)s.length(); i++) {
        dist[s[i]]++;
    }
}

void init_huffman_tree(map<char, int>& dist, vector<tuple<int, vector<int>, string> >& T) {
    int i = 0;
    vector<int> temp = {};
    for (auto itr : dist) {
        T[i] = make_tuple(dist[itr.first], temp, "");
        i++;
    }
}

void init_priority_queue(map<char, int>& dist, priority_queue<pair<int, int>, vector<pair<int, int> >, greater<pair<int, int> > >& pque) {
    int i = 0;
    for (auto itr : dist) {
        pque.push(make_pair(itr.second, i));
        i++;
    }
}

void make_huffman_tree(map<char, int>& dist, vector<tuple<int, vector<int>, string> >& T, priority_queue<pair<int, int>, vector<pair<int, int> >, greater<pair<int, int> > >& pque) {
    for (int i = (int)dist.size(); i < 2 * dist.size() - 1; i++) {
        pair<int, int> temp1 = pque.top();
        pque.pop();
        pair<int, int> temp2 = pque.top();
        pque.pop();
        pair<int, int> temp3 = make_pair(temp1.first + temp2.first, i);
        pque.push(temp3);
        vector<int> temp4 = { temp1.second, temp2.second };
        T[i] = make_tuple(temp3.first, temp4, "");
    }
}

void huffman_tree_dfs(vector<tuple<int, vector<int>, string> >& T, int v) {
    vector<int> temp1 = {};
    if (get<1>(T[v]) != temp1) {
        for (int i = 0; i < 2; i++) {
            string temp2 = get<2>(T[v]) + (char)(i + '0');
            int idx = get<1>(T[v])[i];
            T[idx] = make_tuple(get<0>(T[idx]), get<1>(T[idx]), temp2);
            huffman_tree_dfs(T, idx);
        }
    }
}



int main(int argc, char* argv[]) {

    // 入力
    string s;
    cin >> s;

    // 文字の出現頻度を求める
    map<char, int> dist;
    get_distribution(s, dist);
    int N = int(dist.size());

    // 種類数が1の場合はダミーの文字を入れる必要がある
    bool dummy_flag = false;
    if (N == 1) {
        dummy_flag = true;
        N++;
        char dummy = (char)(s[0] + 1);
        dist[dummy] = 0;
    }

    // 各文字に対応するノードを1つずつ作る
    vector<tuple<int, vector<int>, string> > T(2 * N - 1);
    init_huffman_tree(dist, T);

    // 親を持たないノードのうち、出現頻度が小さい2つのノードを選ぶ
    priority_queue<pair<int, int>, vector<pair<int, int> >, greater<pair<int, int> > > pque;
    init_priority_queue(dist, pque);

    // その2つの出現頻度を足し合わせたノードを新たに作る
    // 新たなノードをその2つのノードの親とする
    // すべてのノードがつながれるまで繰り返す
    make_huffman_tree(dist, T, pque);

    // マフマン木エッジに0と1を当てはめていく
    // ハフマン木の根の部分からノードをたどってできたビット列が符合語となる
    huffman_tree_dfs(T, 2 * N - 2);

    // コードを生成する
    map<char, string> codeword;
    int i = 0;
    for (auto itr : dist) {
        if (i < N) {
            if (dummy_flag && itr.second == 0) continue; // ダミー文字は無視する
            codeword[itr.first] = get<2>(T[i]);
            i++;
        }
    }

    // 0~9を順番に出力し、存在しない場合はnullを出力
    for (char c = '0'; c <= '9'; c++) {
        if (codeword.count(c)) {
            cout << c << " " << codeword[c] << endl;
        }
        else {
            cout << c << " null" << endl;
        }
    }

    return 0;

    return 0;
}
