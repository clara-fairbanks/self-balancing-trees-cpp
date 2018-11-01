//
//  BST.cpp
//  AVLTree
//
//  Created by Clara Fairbanks on 10/2/18.
//  Copyright © 2018 Clara Fairbanks. All rights reserved.
//

#include "BST.hpp"
#include <string>
#include <fstream>
#include <iomanip> //for fomatting the output


template<class Comparable>
BST<Comparable>::BST() {
    
    root = nullptr;
}

template<class Comparable>
BST<Comparable>::BST( const BST & originalTree ) {
    
    copyTree( root, originalTree.root );
}

template<class Comparable>
BST<Comparable>::BST( BST && originalTree ) {
    
    copyTree( root, move( originalTree.root ) );
}

template<class Comparable>
void BST<Comparable>::operator=( const BST& originalTree ) {

    if ( this != &originalTree ){
        if( !isEmpty() )
            destroy( root );
        if( !originalTree.isEmpty() )
            copyTree( root, originalTree.root );
    }
    
}

template <class Comparable>
void BST<Comparable>:: copyTree( Node*& copy, const Node * originalTree) {
    
    if (originalTree == nullptr)
        copy = nullptr;
    else
    {
        copy = new Node;
        copy->data = originalTree->data;
        copyTree(copy->left, originalTree->left);
        copyTree(copy->right, originalTree->right);
    }
}


template<class Comparable>
BST<Comparable>::~BST() {
    
    if( root != nullptr )
        destroy(root);
}

// tree is empty; nodes have been deallocated.
template<class Comparable>
void BST<Comparable>::destroy( Node*& p) {
    
    if ( p != nullptr ){
        
        destroy( p->left );
        destroy( p->right );
        delete p;
    }
    else return;
}

template<class Comparable>
bool BST<Comparable>::isEmpty()const {
    
    return ( root == nullptr );
}

template <class Comparable>
int BST<Comparable>::getlength(){
    
    return size( root );
}

template <class Comparable>
int BST<Comparable>::size( Node *p ){
   
    if ( p == nullptr )
        return 0;
    else
        return( size(p->left) + 1 + size(p->right) );
}

template <class Comparable>
int BST<Comparable>::maxHeight( Node* p ){
    
    if ( p ){
    
        int lheight = maxHeight( p->left );
        int rheight = maxHeight( p->right );
        
        if ( lheight > rheight )
            return( lheight + 1 );
        else return( rheight + 1 );
    }
    else return 0;
    
}

// Sets data to the data member of the right-most node in tree.
template <class Comparable>
void BST<Comparable>:: getPredecessor( Node* p, Comparable& data){
    
    while ( p->right != nullptr )
        p = p->right;
    data = p->data;
}

template <class Comparable>
void BST<Comparable>:: deleteNode( Node*& p ) {
    
    Comparable data;
    Node* tempPtr;
    
    tempPtr = p;
    if ( p->left == nullptr )
    {
        p = p->right;
        delete tempPtr;
    }
    else if ( p->right == nullptr )
    {
        p = p->left;
        delete tempPtr;
    }
    else
    {
        getPredecessor( p->left, data );
        p->data = data;
        deleteNode( p->left, data );
    }
    
}

template <class Comparable>
void BST<Comparable>:: deleteNode( Node *& p, Comparable item )
{
    
    if( p == nullptr )
        return;
    if ( item < p->data )
        deleteNode( p->left, item );
    else if ( item == p->data )
        deleteNode( p );
    else
        deleteNode( p->right, item );
}

// Calls recursive function Insert to insert item into tree.
template<class Comparable>
void BST<Comparable>::insert( const Comparable & item ) {
    
    insert( root, item );
}

template <class Comparable>
void BST<Comparable>::insert( Comparable && val ){
    
    insert( root, move(val) );
}

template <class Comparable>
void BST<Comparable>:: insert( Node *& p, Comparable item ) {
    
    if ( p == nullptr )
        p = new Node{ item, nullptr, nullptr, 1 };
    else if ( item < p->data )
        insert( p->left, item );
    else if ( item > p->data )
        insert( p->right, item );
    
    p->height = maxHeight( p );

}

template <class Comparable>
void BST<Comparable>:: insert( Node && p , Comparable item ) {
    
    if ( p == nullptr )
        p = new Node{ item, nullptr, nullptr };
    else if ( item < p->data )
        insert( p->left, move( item ) );
    else if ( item > p->data )
        insert( p->right, move( item ) );
    
    p->height = maxHeight( p );
}

// Calls recursive function Delete to delete item from tree.
template<class Comparable>
void BST<Comparable>::deleteItem( Comparable item ) {
   
    deleteNode( root, item );
}

// Recursively searches tree for item.
template<class Comparable>
Comparable BST<Comparable>::GetItem( Comparable item, bool& found )
{
    Node* p;
    p = root;
    found = false;
    while ( !found && p != nullptr )
    {
        if ( item < p->data )
            p = p->left;
        else if ( item == p->data )
        {
            item = p->data;
            found = true;
        }
        else
            p = p->right;
    }
    return item;
}

template <class Comparable>
int BST<Comparable>::treeHeight(){
    
    return maxHeight( root );
}


// displays the tree items in inorder.
template <class Comparable>
void BST<Comparable>::inOrderPrint( Node* p ) {
    
    if( p == nullptr )
        return;
    inOrderPrint( p->left );
    cout << p->data << " ";
    inOrderPrint( p->right );
}

template <class Comparable>
void BST<Comparable>::display(){
    
    if( root != nullptr )
        inOrderPrint( root );
};

template <class Comparable>
bool BST<Comparable>::contains( const Comparable & val) const{
    
    return contains( root, val );
}

template <class Comparable>
bool BST<Comparable>::contains( Node * n, const Comparable & val) const{
    if( n == nullptr )
        return false;
    else if( val < n->data )
        return contains( n->left, val );
    else if( val > n->data )
        return contains( n->right, val );
    else
        return true;
            
}

template <class Comparable>
void BST<Comparable>::operator[]( Comparable && index ){
    
    findItemById( root , index, 0 );
};

template <class Comparable>
void BST<Comparable>::findItemById( Node *p, int id ,int cnt){
    
    //checks if node is null, returns nothing
    if( !p )
        return ;
    
    //checks if id is > tree size
    if( id > size( root ) )
        return ;
    //check if count == id
    if( id == cnt ){
        cout<< p->data <<endl;
        return;
    }
    //if not, increment counter, move to p->left/right in order
    else{
        return( findItemById(p->left, id, cnt++) + findItemById(p->left, id, cnt++) );
    }
    
}

