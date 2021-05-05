/*
 * handycp - Some pretty handy stuff for Competitive Programming
 *
 * Binary Search Tree
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
#include <iostream>
#include <string>
#include <memory>

namespace handycp {
    template<typename T>
    class BSTree {
    public:
        BSTree(): root(nullptr) {}

        void Print() const;
        void Insert(T val);
        bool Contains(T val) const;
        void Remove(T val);
    private:
        struct TreeNode {
            T data;
            std::unique_ptr<TreeNode> left;
            std::unique_ptr<TreeNode> right;

            TreeNode(T data): data(data), left(nullptr), right(nullptr) {}
        };

        std::unique_ptr<TreeNode> root;
        std::string SubTreeAsString(const std::unique_ptr<TreeNode> & node) const;
        void Insert(T val, std::unique_ptr<TreeNode>& node);      
        bool Contains(T val, std::unique_ptr<TreeNode>& node) const; 
        void Remove(T val, std::unique_ptr<TreeNode>& node); 
        std::unique_ptr<TreeNode>& FindMin(std::unique_ptr<TreeNode>& node);
    };
};
