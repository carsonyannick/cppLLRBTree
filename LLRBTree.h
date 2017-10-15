#include "LLRBNode.h"

template<class KeyT, class ValueT>
class LLRBTree
{
public:
    LLRBTree();
    void Insert( KeyT key, ValueT value );
    void Delete( KeyT key );
    ValueT * Search( KeyT key ) const;
private:
    void DeleteMin();
    bool isRed( LLRBNode<KeyT, ValueT> *node );
    bool isLeaf( LLRBNode<KeyT, ValueT> *node );
    void createNode( KeyT key, ValueT value, LLRBNode<KeyT, ValueT> **node );
    LLRBNode<KeyT, ValueT> * insertHelper( KeyT key, ValueT value, LLRBNode<KeyT, ValueT> *node );
    void colorFlip( LLRBNode<KeyT, ValueT> * node );
    LLRBNode<KeyT, ValueT> * rotateLeft	( LLRBNode<KeyT, ValueT> *node );
    LLRBNode<KeyT, ValueT> * rotateRight	( LLRBNode<KeyT, ValueT> *node );
    LLRBNode<KeyT, ValueT> * moveRedLeft	( LLRBNode<KeyT, ValueT> *node );
    LLRBNode<KeyT, ValueT> * moveRedRight( LLRBNode<KeyT, ValueT> *node );
    LLRBNode<KeyT, ValueT> * deleteHelper( KeyT key, LLRBNode<KeyT, ValueT> *node );
    LLRBNode<KeyT, ValueT> * deleteMinHelper( LLRBNode<KeyT, ValueT> *node );
    LLRBNode<KeyT, ValueT> * getMinNode( LLRBNode<KeyT, ValueT> *node );
    LLRBNode<KeyT, ValueT> * fixUp( LLRBNode<KeyT, ValueT> *node );

    LLRBNode<KeyT, ValueT> * m_root;
    LLRBNode<KeyT, ValueT> * m_leaf;
    int m_count;
};
