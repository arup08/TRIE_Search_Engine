#ifndef TRIE_H
#define TRIE_H

#include <bits/stdc++.h>
using namespace std;

class TrieNode {
public:
    unordered_map<char, TrieNode*> children;
    bool isEndOfWord;

    TrieNode();
};

class Trie {
public:
    TrieNode *root;

    Trie();

    void insert(string str);
    TrieNode* search_exact(string str);
    vector<string> search_pre(string str);
    void remove(string str);
    void draw(TrieNode *current = nullptr, int depth = 0);
private:
    bool _remove(TrieNode *current, string str, int index);
};

#endif
