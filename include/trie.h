/*
 * handycp - Some pretty handy stuff for Competitive Programming
 *
 * Trie
 *
 *
 * Copyright © 2021 Aragami1408/D6E093 <vucaominh1408@gmail.com>

 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the “Software”),
 * to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER 
 * DEALINGS IN THE SOFTWARE.
 *
 */
#pragma once
#include <string>
#include <iostream>
#define ALPHA_SIZE 26

namespace handycp {

    struct TrieNode {
        char data;
        TrieNode *children[ALPHA_SIZE];
        bool is_leaf;

        TrieNode(char data);
        ~TrieNode();
        void insertNode(std::string word);
        bool searchNode(std::string word);
        void traverseNode(TrieNode *root);
        bool isLeaf(std::string word);
        void deleteNode(std::string word);
        std::string longestPrefix(std::string word);
    };
};

