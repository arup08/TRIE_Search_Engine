#include "trie.h"
#include <chrono>
using namespace std;

TrieNode::TrieNode() {
    isEndOfWord = false;
}

Trie::Trie() {
    root = new TrieNode();
}

void Trie::insert(string str) {
    TrieNode *current = root;
    for (char ch : str) {
        if (!current->children.count(ch)) {
            current->children[ch] = new TrieNode();
        }
        current = current->children[ch];
    }
    current->isEndOfWord = true;
}

TrieNode* Trie::search_exact(string str) {
    TrieNode *current = root;
    auto start = chrono::high_resolution_clock::now();

    for (char ch : str) {
        if (!current->children.count(ch)) {
            return NULL;
        }
        current = current->children[ch];
    }

    auto stop = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::nanoseconds>(stop - start);
    cout << "\033[32m\n"
         << current->isEndOfWord << " results in " << double(duration.count()) / 1e6 << " ms.\033[0m\n\n";

    return current->isEndOfWord ? current : NULL;
}

void get_words_dfs(TrieNode *current, string pre, vector<string> &results) {
    if (!current) return;
    if (current->isEndOfWord) results.push_back(pre);

    for (auto &p : current->children) {
        get_words_dfs(p.second, pre + p.first, results);
    }
}

vector<string> Trie::search_pre(string str) {
    auto start = chrono::high_resolution_clock::now();

    TrieNode *current = root;
    vector<string> results;

    for (char ch : str) {
        if (!current->children.count(ch)) {
            return results;
        }
        current = current->children[ch];
    }

    get_words_dfs(current, str, results);

    auto stop = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::nanoseconds>(stop - start);
    cout << "\033[32m\n"
         << results.size() << " results in " << double(duration.count()) / 1e6 << " ms.\033[0m\n\n";

    return results;
}

void Trie::remove(string str) {
    _remove(root, str, 0);
}

bool Trie::_remove(TrieNode *current, string str, int index) {
    if (index == str.length()) {
        if (!current->isEndOfWord) return false;
        current->isEndOfWord = false;
        return current->children.empty();
    }

    char ch = str[index];
    if (!current->children.count(ch)) return false;

    bool shouldDelete = _remove(current->children[ch], str, index + 1);
    if (shouldDelete) {
        delete current->children[ch];
        current->children.erase(ch);
        return current->children.empty();
    }
    return false;
}

void Trie::draw(TrieNode *current, int depth) {
    if (!current) current = root;
    for (auto &p : current->children) {
        for (int i = 0; i < depth; i++) cout << "_ ";
        cout << p.first << "\n";
        draw(p.second, depth + 1);
    }
}
