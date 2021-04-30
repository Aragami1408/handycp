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

#include <bstree.h>

template <typename T>
void handycp::BSTree<T>::Print() const {
    if(this->root == nullptr){
        std::cout << "{}" << std::endl;
    } else{
        std::cout << this->SubTreeAsString(this->root) << std::endl;
    }
}

template <typename T>
std::string handycp::BSTree<T>::SubTreeAsString(const std::unique_ptr<TreeNode>& node) const {
    std::string leftStr = (node->left == nullptr) ? "{}" : SubTreeAsString(node->left);
    std::string rightStr = (node->right == nullptr) ? "{}" : SubTreeAsString(node->right);
    std::string result = "{" + std::to_string(node->data) + ", " + leftStr + ", " + rightStr + "}";
    return result;
}

template <typename T>
void handycp::BSTree<T>::Insert(T val) {
    this->Insert(val, this->root);
}

template <typename T>
void handycp::BSTree<T>::Insert(T val, std::unique_ptr<TreeNode>& node) {

    if(node == nullptr){
        // Case: node is a nullptr
        // Make a new TreeNode for it to point to
        node = std::make_unique<TreeNode>(val);
    } else{
        if(val < node->data){
            // Case: val is < node's data
            this->Insert(val, node->left);
        } else if(val > node->data){
            // Case: val is > node's data
            this->Insert(val, node->right);
        } else{
            // Case: val is equal to node's data
            std::cout << "Warning: Value already exists, so nothing will be done." << std::endl;
        }
    }
}

template <typename T>
bool handycp::BSTree<T>::Contains(T val) const {
    return Contains(val, this->root);
}

template <typename T>
bool handycp::BSTree<T>::Contains(T val, std::unique_ptr<TreeNode>& node) const {
    if(node == nullptr){
        return false;
    } else if(val == node->data){
        return true;
    } else if(val < node->data){
        return this->Contains(val, node->left);
    } else{
        return this-Contains(val, node->right);
    }
}

template <typename T>
void handycp::BSTree<T>::Remove(T val) {
    this->Remove(val, this->root);
}


template <typename T>
void handycp::BSTree<T>::Remove(T val, std::unique_ptr<TreeNode>& node) {
    if(node == nullptr){
        // Case: nullptr

        std::cout << "val not found in tree" << std::endl;

    } else if(val == node->data){
        // Found value

        if(node->left == nullptr && node->right == nullptr){
            // Case: node is a leaf

            node = nullptr;

        } else if(node->left != nullptr && node->right == nullptr){
            // Case: node has a left subtree (but not right)
            // Point node's parent at node's left subtree

            node = std::move(node->left);

        } else if(node->left == nullptr && node->right != nullptr){
            // Case: node has a right subtree (but not left)

            node = std::move(node->right);

        } else{
            // Case: node has left and right subtrees

            std::unique_ptr<TreeNode>& minNode = this->FindMin(node->right); // returns a reference to the actual pointer in the tree
            node->data = minNode->data;
            this->Remove(minNode->data, minNode);
        }

    } else if(val < node->data){
        // Case: remove val from this node's left subtree
        this->Remove(val, node->left);
    } else{
        // Case: remove val from this node's right subtree
        this->Remove(val, node->right);
    }
}

template <typename T>
std::unique_ptr<typename handycp::BSTree<T>::TreeNode>& handycp::BSTree<T>::FindMin(std::unique_ptr<TreeNode>& node) {
    if(node == nullptr){
        throw "Min value not found";
    } else if(node->left == nullptr){
        return node;
    } else{
        return this->FindMin(node->left);
    }
}
