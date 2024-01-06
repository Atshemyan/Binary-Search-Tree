#include "TreeNode.hpp"
#include <iostream>

template <typename T>
class BST
{
private:
    TreeNode<T> *root {};

    //helpers
    TreeNode<T> *helperInsert(TreeNode<T>*, T);
    bool helperSearch(TreeNode<T> *node, T val);
    void levelorderTraversalRecursive(TreeNode<T> *node, int level, std::function<void(T&)> functor);

public:
    TreeNode<T> *getRoot() const;
    void insert(T);
    bool search(T);

    void preorderTraversal(TreeNode<T> *node, std::function<void(T&)>);
    void inorderTraversal(TreeNode<T> *node, std::function<void(T&)>);
    void postorderTraversal(TreeNode<T> *node, std::function<void(T&)>);
    void levelorderTraversal(TreeNode<T> *node, std::function<void(T&)>);

    int getHeight(TreeNode<T> *node);
    TreeNode<T> *getMin(TreeNode<T> *node);
    TreeNode<T> *getMax(TreeNode<T> *node);
    TreeNode<T> *getSuccessor(TreeNode<T> *node);
    TreeNode<T> *getPredecessor(TreeNode<T> *node);


};



template <typename T>
TreeNode<T> *BST<T>::getRoot() const
{
    return root;
}

template <typename T>
void BST<T>::insert(T val)
{
    root = helperInsert(root, val);
}

template <typename T>
bool BST<T>::search(T val)
{
    return helperSearch(root, val);
}

template <typename T>
TreeNode<T>* BST<T>::getMax(TreeNode<T>* node)
{
    if (!node || !node->right)
    {
        return node;
    }
    return getMax(node->right);
}

template <typename T>
TreeNode<T>* BST<T>::getMin(TreeNode<T>* node)
{
    if (!node ||!node->left)
    {
        return node;
    }
    return getMin(node->left);
}

template <typename T>
TreeNode<T>* BST<T>::getSuccessor(TreeNode<T> *node)
{
    if (!node) return nullptr;
    if (node->right) return getMin(node->right);

    TreeNode<T> *succesor {};
    TreeNode<T> *ancestor {getRoot()};
    while (ancestor != node)
    {
        if (node->val < ancestor->val)
        {
            succesor = ancestor;
            ancestor = ancestor->left;
        }
        else
        {
            ancestor = ancestor->right;
        }
    }
    return succesor;
    
}

template <typename T>
TreeNode<T>* BST<T>::getPredecessor(TreeNode<T> *node) // from minimums get maximum
{
    if (!node) return nullptr;
    if (node->left) return getMax(node->left);

    TreeNode<T> *predecessor {};
    TreeNode<T> *ancestor {getRoot()};
    while (ancestor != node)
    {
        predecessor = ancestor;
        ancestor = ancestor->left;
        
    }
    return predecessor;
}



template <typename T>
int BST<T>::getHeight(TreeNode<T> *node)
{
    if (!node) {return -1;}

    return std::max(getHeight(node->left), getHeight(node->right)) + 1;
}


template <typename T>
void BST<T>::levelorderTraversal(TreeNode<T> *node, std::function<void(T&)> functor)
{ 
    int height = getHeight(getRoot());
    for (int i = 0; i <= height; ++i)
    {
        levelorderTraversalRecursive(node, i, functor);
    }
   

}


template <typename T>
void BST<T>::preorderTraversal(TreeNode<T> *node, std::function<void(T&)> functor)
{ 
    if (!node) {return;}
    functor(node->val);
    preorderTraversal(node->left, functor);
    preorderTraversal(node->right, functor);

}

template <typename T>
void BST<T>::inorderTraversal(TreeNode<T> *node, std::function<void(T&)> functor)
{
    if (!node) {return;}
    inorderTraversal(node->left, functor);
    functor(node->val);
    inorderTraversal(node->right, functor);

}

template <typename T>
void BST<T>::postorderTraversal(TreeNode<T> *node, std::function<void(T&)> functor)
{
    if (!node) {return;}
    preorderTraversal(node->left, functor);
    preorderTraversal(node->right, functor);
    functor(node->val);
}

//helpers realizations

template <typename T>
TreeNode<T> *BST<T>::helperInsert(TreeNode<T>* node, T val)
{
    if (!node) {return new TreeNode<T>(val);}

    if (val > node->val)
    {
        node->right = helperInsert(node->right, val);
    }
    else
    {
        node->left = helperInsert(node->left, val);
    }
    
    return node;
}

template <typename T>
bool BST<T>::helperSearch(TreeNode<T> *node, T val)
{
    if (!node) {return false;}
    if (node->val == val)
    {
        return true;
    }

    if (val > node->val)
    {
        return helperSearch(node->right, val);
    }

    else
    {
        return helperSearch(node->left, val);
    }
    
}

template <typename T>
void BST<T>::levelorderTraversalRecursive(TreeNode<T> *node, int level, std::function<void(T&)> functor)
{
    if (!node || level < 0)
        return;

    if (level == 0)
    {
        functor(node->val);
    }
    else
    {
        levelorderTraversalRecursive(node->left, level - 1, functor);
        levelorderTraversalRecursive(node->right, level - 1, functor);
    }
}