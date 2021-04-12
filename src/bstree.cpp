#include "bstree.h"

template <typename T>
void BSTree<T>::Print() const {
    if(this->root == nullptr){
        std::cout << "{}" << std::endl;
    } else{
        std::cout << this->SubTreeAsString(this->root) << std::endl;
    }
}

template <typename T>
std::string BSTree<T>::SubTreeAsString(const std::unique_ptr<TreeNode>& node) const {
    std::string leftStr = (node->left == nullptr) ? "{}" : SubTreeAsString(node->left);
    std::string rightStr = (node->right == nullptr) ? "{}" : SubTreeAsString(node->right);
    std::string result = "{" + std::to_string(node->data) + ", " + leftStr + ", " + rightStr + "}";
    return result;
}

template <typename T>
void BSTree<T>::Insert(T val) {
    this->Insert(val, this->root);
}

template <typename T>
void BSTree<T>::Insert(T val, std::unique_ptr<TreeNode>& node) {

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
bool BSTree<T>::Contains(T val) const {
    return Contains(val, this->root);
}

template <typename T>
bool BSTree<T>::Contains(T val, std::unique_ptr<TreeNode>& node) const {
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
void BSTree<T>::Remove(T val) {
    this->Remove(val, this->root);
}


template <typename T>
void BSTree<T>::Remove(T val, std::unique_ptr<TreeNode>& node) {
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
std::unique_ptr<typename BSTree<T>::TreeNode>& BSTree<T>::FindMin(std::unique_ptr<TreeNode>& node) {
    if(node == nullptr){
        throw "Min value not found";
    } else if(node->left == nullptr){
        return node;
    } else{
        return this->FindMin(node->left);
    }
}
