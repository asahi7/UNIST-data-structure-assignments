
//
// assignment3.cpp
//
// Please write your name, your student ID, and your email here.
// Moreover, please describe the implementation of your functions here.
// You will have to submit this file.
//

// parsePostfixExpression: take lists of tokens, iterate throught it, if constant or variable push to the stack
// as a new LinkedBinaryTree, if operator, take two elements from the stack and attach as left and right subtrees to the
// operator

// print_inorder: deeps into the tree, and just does printing in order, code explains itself

// print_postorder: deeps into the tree, and just does printing in post-order manner, code explains itself

// findMinimumDepth: does DFS and searches for the symbol

// substitute: just goes over the tree, if encounters variable, makes it constant

// simplify_subtree: deeps to the bottom, then goes in the bottom-up manner, if encounters two constants as children,
// then make calculations and replaces the node. 

// Aibek Smagulov, 20142028, smagulovaybek@gmail.com

#include <iostream>
#include <stdexcept>
#include <list>
#include <stack>
#include <limits>
#include "LinkedBinaryTree.h"
#include "Symbol.h"
#include "assignment3.h"


LinkedBinaryTree<Symbol> parsePostfixExpression(list<string> tokens) {
    stack< LinkedBinaryTree<Symbol> > st;
    for(list<string>::iterator it = tokens.begin(); it != tokens.end(); it++){
        string token = (*it);
        Symbol new_sym(token);
        if(new_sym.isConstant() == true){
            LinkedBinaryTree<Symbol> lbt;
            lbt.addRoot();
            LinkedBinaryTree<Symbol>::Position pos = lbt.root();
            *pos = new_sym;
            st.push(lbt);
        }
        else if(new_sym.isVariable() == true){
            LinkedBinaryTree<Symbol> lbt;
            lbt.addRoot();
            LinkedBinaryTree<Symbol>::Position pos = lbt.root();
            *pos = new_sym;
            st.push(lbt);
        }
        else if(new_sym.isOperator() == true){
            LinkedBinaryTree<Symbol> lbt;
            lbt.addRoot();
            LinkedBinaryTree<Symbol> rch = st.top();
            st.pop();
            LinkedBinaryTree<Symbol> lch = st.top();
            st.pop();
            LinkedBinaryTree<Symbol>::Position pos = lbt.root();
            *pos = new_sym;
            lbt.attachLeftSubtree(pos, lch);
            lbt.attachRightSubtree(pos, rch);
            st.push(lbt);
        }
    }
    if(st.size() == 1) return (st.top());
    else throw runtime_error("Stack of LinkedBinaryTrees gives errors!");
}

void print_inorder_from_node(LinkedBinaryTree<Symbol>::Position root){
    if(root.isNull()) return;
    if(root.left().isNull() == false){
        cout << "( ";
        print_inorder_from_node(root.left());
    }
    cout << *root << " ";
    if(root.right().isNull() == false){
        print_inorder_from_node(root.right());
        cout << ") ";
    }
}

void print_inorder(const LinkedBinaryTree<Symbol>& tree) {
    //if(tree.empty()) throw runtime_error("Empty tree!");
    print_inorder_from_node(tree.root());
}

void print_postorder_from_node(LinkedBinaryTree<Symbol>::Position root){
    if(root.isNull()) return;
    if(root.left().isNull() == false) print_postorder_from_node(root.left());
    if(root.right().isNull() == false) print_postorder_from_node(root.right());
    cout << *root << " ";
}

void print_postorder(const LinkedBinaryTree<Symbol>& tree) {
    print_postorder_from_node(tree.root());
}

int findMinDepthFromNode(LinkedBinaryTree<Symbol>::Position root, const Symbol& sym, int depth){
    if(*root == sym) return depth;
    int mn = 1000000000;
    if(root.left().isNull() == false){
        mn = min(mn, findMinDepthFromNode(root.left(), sym, depth + 1));
    }
    if(root.right().isNull() == false){
        mn = min(mn, findMinDepthFromNode(root.right(), sym, depth + 1));
    }
    return mn;
}

int findMinimumDepth(const LinkedBinaryTree<Symbol>& tree, const Symbol& sym) {
    int res = findMinDepthFromNode(tree.root(), sym, 0);
    return (res == 1000000000 ? -1 : res);
}

void substituteFromNode(LinkedBinaryTree<Symbol>::Position root, const Symbol& variable, const Symbol& constant){
    if(*root == variable) *root = Symbol(constant.getConstant());
    if(root.left().isNull() == false) substituteFromNode(root.left(), variable, constant);
    if(root.right().isNull() == false) substituteFromNode(root.right(), variable, constant);
}

void substitute(const LinkedBinaryTree<Symbol>& tree, const Symbol& variable, const Symbol& constant) {
    substituteFromNode(tree.root(), variable, constant);
}

void simplify_subtree_from_node(LinkedBinaryTree<Symbol>::Position root, LinkedBinaryTree<Symbol>& tree){
    if(root.left().isNull() == false) simplify_subtree_from_node(root.left(), tree);
    if(root.right().isNull() == false) simplify_subtree_from_node(root.right(), tree);
    if(root.left().isNull() == false && root.right().isNull() == false && (*root.left()).isConstant() && (*root.right()).isConstant()){
        int l = (*root.left()).getConstant();
        int r = (*root.right()).getConstant();
        int res = (*root).compute(l, r);
        LinkedBinaryTree<Symbol>::Position pNode = root.parent();
        LinkedBinaryTree<Symbol> lbt;
        lbt.addRoot();
        (*lbt.root()) = Symbol(res);
        if(pNode.isNull() == true){
            tree.removeSubtree(root);
            tree.addRoot();
            *tree.root() = Symbol(res);
            return;
        }
        if(&(*pNode.left()) == &(*root)){
            tree.removeSubtree(root);
            tree.attachLeftSubtree(pNode, lbt);
        } 
        else{
            tree.removeSubtree(root);
            tree.attachRightSubtree(pNode, lbt);
        }
    }
}

void simplify_subtree(LinkedBinaryTree<Symbol>& tree) {
    simplify_subtree_from_node(tree.root(), tree);    
}
