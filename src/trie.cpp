#include "trie.h"

handycp::TrieNode::TrieNode(char data) {
    for(int i=0;i<ALPHA_SIZE;i++) {
        this->children[i] = nullptr;
    }
    this->is_leaf = 0;
    this->data = data;
}

handycp::TrieNode::~TrieNode() {
    for(int i=0;i<ALPHA_SIZE;i++) {
        if(this->children[i] != nullptr) {
            delete this->children[i];
        }
        else {
            continue;
        }
    }
    delete this;
}

void handycp::TrieNode::insertNode(std::string word) {
    TrieNode *temp = this;

    for (int i=0; i < word.length(); i++) {
        int idx = (int) word[i] - 'a';
        if (temp->children[idx] == NULL) {
            temp->children[idx] = new TrieNode(word[i]);
        }
        temp = temp->children[idx];
    }
    temp->is_leaf = 1;
}

bool handycp::TrieNode::searchNode(std::string word) {
    TrieNode *temp = this;
    for(int i=0; i < word.length(); i++) {
        int pos = word[i] - 'a';
        if(temp->children[pos] == nullptr) {
            return false;
        }
        temp = temp->children[pos];
    } 
    if(temp != nullptr && temp->is_leaf == true) {
        return true;
    }
    return false;
}

void handycp::TrieNode::traverseNode(TrieNode *root) {
    if(!root)
        return;

    std::cout << this->data << " -> ";
    for(int i=0;i<ALPHA_SIZE; i++)
        traverseNode(this->children[i]);
}

bool handycp::TrieNode::isLeaf(std::string word) {
    TrieNode *temp = this;
    for(int i=0; i < word.size(); i++) {
        int pos = (int) word[i] - 'a';
        if(temp->children[pos]) {
            temp = temp->children[pos];
        }
    }
    return temp->is_leaf;

}

void handycp::TrieNode::deleteNode(std::string word) {

}

std::string handycp::TrieNode::longestPrefix(std::string word) {
    if(word.empty()) {
        return nullptr;
    }
    int len = word.size();
    std::string longestPrefix = word;
    
    return longestPrefix;
}
