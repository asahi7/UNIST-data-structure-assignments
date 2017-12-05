//
// LinkedBinaryTree.h
//
// Please write your name, your student ID, and your email here.
// Moreover, please describe the implementation of your functions here.
// You will have to submit this file.
//

// Aibek Smagulov, 20142028, smagulovaybek@gmail.com

#ifndef LINKED_BINARY_TREE_H
#define LINKED_BINARY_TREE_H

#include <iostream>
#include <stdexcept>
#include <cstdlib>
#include <list>

using namespace std;

template <class T>
class LinkedBinaryTree {
    public:
    struct Node{
        T data;
        Node* left;
        Node* right;
        Node* parent;
        Node() : data(), parent(NULL), left(NULL), right(NULL) {}
    };
    class Position{
        Node* v;
        public: 
        Position(Node* _v = NULL) : v(_v) {}
        T& operator*(){
            return v->data;
        }
        T& operator*() const{
            return v->data;
        }
        Position left() const {
            return Position(v->left);
        }
        Position right() const {
            return Position(v->right);
        }
        Position parent() const {
            return Position(v->parent);
        }
        bool isRoot() const {
            return (v->parent == NULL);
        }
        bool isExternal() const {
            return (v->left == NULL && v->right == NULL);
        }
        bool isNull() const {
            return (v == NULL); // 
        }
        friend class LinkedBinaryTree;
    };
    
    typedef std::list<Position> PositionList;

    LinkedBinaryTree();
    int size() const;
    bool empty() const;
    Position root() const;
    PositionList positions() const;
    void addRoot();
    void expandExternal(const Position& p);
    Position removeAboveExternal(const Position& p);
    int height() const;
    void attachLeftSubtree(const Position& p, LinkedBinaryTree& subtree);
    void attachRightSubtree(const Position& p, LinkedBinaryTree& subtree);
    void removeSubtree(const Position& p);
    private:
    Node* _root;
    int _size;

    void preorder(Node* v, PositionList& pl) const;
    int get_height(Node* v) const;
};

template<class T>
typename LinkedBinaryTree<T>::PositionList LinkedBinaryTree<T>::positions() const{
    PositionList pl;
    preorder(_root, pl);
    return PositionList(pl);
}

template<class T>
void LinkedBinaryTree<T>::preorder(Node* v, PositionList& pl) const{
    pl.push_back(Position(v));
    if(v->left != NULL){
        preorder(v->left, pl);
    }
    if(v->right != NULL){
        preorder(v->right, pl);
    }
}

template<class T>
LinkedBinaryTree<T>::LinkedBinaryTree() : _root(NULL), _size(0) {}

template<class T>
int LinkedBinaryTree<T>::size() const { return _size; }

template<class T>
bool LinkedBinaryTree<T>::empty() const { return (_size == 0); }

template<class T>
typename LinkedBinaryTree<T>::Position LinkedBinaryTree<T>::root() const { return Position(_root); }

template<class T>
void LinkedBinaryTree<T>::addRoot() { if(_root != NULL) throw runtime_error("Tree is not empty!"); _root = new Node; _size = 1; }

template<class T>
void LinkedBinaryTree<T>::expandExternal(const Position& p){
    if(p.isNull() == true) throw runtime_error("The position is null!");
    if(p.left().isNull() == false || p.right().isNull() == false) throw runtime_error("Expanding internal node!");
    Node* v = p.v;
    v->left = new Node;
    v->left->parent = v;
    v->right = new Node;
    v->right->parent = v;
    _size += 2;
}

template<class T>
typename LinkedBinaryTree<T>::Position LinkedBinaryTree<T>::removeAboveExternal(const Position& p){
    if(p.isNull() == true) throw runtime_error("The position is null!");
    if(p.parent().isNull() == true) throw runtime_error("Can not call removeAboveExternal onto root of the tree!"); 
    Node* w = p.v;
    Node* v = w->parent;
    Node* sib = (w == v->left ? v->right : v->left);
    if(v == _root){
        _root = sib;
        sib->par = NULL;
    }
    else{
        Node* gpar = v->parent;
        if(v == gpar->left) gpar->left = sib;
        else gpar->right = sib;
        sib->parent = gpar;
    }
    delete w;
    delete v;
    _size -= 2;
    return Position(sib);
}

template<class T>
int LinkedBinaryTree<T>::get_height(Node* v) const{
    if(v->left == NULL && v->right == NULL) return 0;
    int hl = 0, hr = 0; 
    if(v->left != NULL) hl = get_height(v->left) + 1;
    if(v->right != NULL) hr = get_height(v->right) + 1;
    return max(hl, hr);
}

template<class T>
int LinkedBinaryTree<T>::height() const {
    if(_size == 0) throw runtime_error("Empty tree"); //
    else return get_height(_root);
}

template<class T>
void LinkedBinaryTree<T>::attachLeftSubtree(const Position& p, LinkedBinaryTree& subtree){
    if(p.isNull() == true) throw runtime_error("The position is null!");
    if(subtree.empty() == true) throw runtime_error("The subtree is empty!");
    Node* v = p.v;
    Node* w = subtree.root().v;
    if(v->left != NULL) throw runtime_error("Left subtree is not NULL!"); //
    v->left = w;
    w->parent = v;
    _size += subtree.size();
}

template<class T>
void LinkedBinaryTree<T>::attachRightSubtree(const Position& p, LinkedBinaryTree& subtree){
    if(p.isNull() == true) throw runtime_error("The position is null!");
    if(subtree.empty() == true) throw runtime_error("The subtree is empty!");
    Node* v = p.v;
    Node* w = subtree.root().v;
    if(v->right != NULL) throw runtime_error("Right subtree is not NULL!"); //
    v->right = w;
    w->parent = v;
    _size += subtree.size();
}

template<class T>
void LinkedBinaryTree<T>::removeSubtree(const Position& p){
    if(p.isNull() == true) throw runtime_error("The position is null!");
    Node* v = p.v;
    if(v->left == NULL && v->right == NULL){
        if(v->parent == NULL) _root = NULL;
        v->parent = NULL;
        delete v;
        _size--;
        return;
    }
    if(v->left != NULL) removeSubtree(Position(v->left));
    if(v->right != NULL) removeSubtree(Position(v->right));
    if(v->parent != NULL){
        Node* p = v->parent;
        if(p->left == v) p->left = NULL;
        else p->right = NULL;
        v->parent = NULL;
    }
    else if(v->parent == NULL){
        _root = NULL;
    }
    delete v;
    _size--;
}

#endif
