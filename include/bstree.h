#pragma once
#include <iostream>
#include <string>
#include <memory>
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
