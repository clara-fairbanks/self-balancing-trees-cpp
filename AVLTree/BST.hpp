//
//  BST.hpp
//  AVLTree
//
//  Created by Clara Fairbanks on 10/2/18.
//  Copyright © 2018 Clara Fairbanks. All rights reserved.
//

#ifndef BST_hpp
#define BST_hpp

#include <stdio.h>
#include <iostream>

using namespace std;

template <class Comparable>
class BST{
protected:
    class Node{
    public:
        Comparable data;
        Node *left;
        Node *right;
        int height ;
        
        Node( const Comparable & item, Node *lc, Node *rc, int h = 0 )
            : data{ item }, left{ lc }, right{ rc }, height{ h }{};
        
        Node( Comparable && item, Node *lc, Node *rc, int h= 0 )
            : data { move(item) }, left{ lc }, right{ rc }, height{ h }{};
        
        Node(): left{nullptr}, right{nullptr}, height{0}{};
    };
    Node *root ;
    void insert( Node *& , Comparable );
    void insert( Node && , Comparable );
    void copyTree( Node *& , const Node * );
    bool contains( Node *, const Comparable & ) const ;
    int size( Node * );
    int maxHeight( Node * );
    void deleteNode( Node *& , Comparable );
    void deleteNode( Node *& );
    void getPredecessor( Node *, Comparable&);
    void destroy( Node *& );
    void inOrderPrint( Node * );
public:
    BST();
    BST( const BST & );
    BST( BST && );
    ~BST();
    void operator=( const BST & );
    bool isEmpty() const;
    bool contains( const Comparable & ) const ;
    
    void operator[] (  Comparable && );
    void findItemById ( Node *, int , int );
    int getlength();
    
    Comparable GetItem( Comparable , bool& );
    void insert( const Comparable &  );
    void insert( Comparable && );
    void deleteItem( Comparable  );
    void display();
    int treeHeight();

};
#endif /* BST_hpp */
