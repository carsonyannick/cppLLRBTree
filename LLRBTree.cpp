/* #include "stdafx.h" */
#include "LLRBTree.h"
#define BLACK false
#define RED true


#include <iostream> 
using namespace std;

template class LLRBTree<int, int>;

/* LLLRBTree<KeyT, ValueT>::LRBTree<KeyT, ValueT>() */
template<class KeyT, class ValueT>
/* LLRBTree<KeyT, ValueT>::LLRBTree<KeyT, ValueT>() */
/* LLRBTree<KeyT, ValueT>() */
LLRBTree<KeyT, ValueT>::LLRBTree()
{
    createNode(0,0, &m_leaf);
    m_root = m_leaf;
    m_count = 0;
}

// insert or overwrite a value with given key
template<class KeyT, class ValueT>
void LLRBTree<KeyT, ValueT>::Insert( KeyT key, ValueT value )
{
	m_root = insertHelper( key, value, m_root );
	m_root->m_color = BLACK;
}

template<class KeyT, class ValueT>
void LLRBTree<KeyT, ValueT>::DeleteMin()
{
	m_root = deleteMinHelper( m_root );
	m_root->m_color = BLACK;
}


// delete the node with a given key
template<class KeyT, class ValueT>
void LLRBTree<KeyT, ValueT>::Delete( KeyT key )
{
	m_root = deleteHelper( key, m_root );
	m_root->m_color = BLACK;
}



// Find and return a value with given key
template<class KeyT, class ValueT>
ValueT * LLRBTree<KeyT, ValueT>::Search( KeyT key ) const
{
	LLRBNode<KeyT, ValueT> *node = m_root;
	while( node != m_leaf )
	{
		if ( *(node->m_key) == key )
		{
			return node->m_value;
		}
		if ( key < *(node->m_key) )
		{
			node = node->m_left;
		}
		else
		{
			node = node->m_right;
		}
	}
	return nullptr;
}



// PRIVATE: -----------------------------------------------------------------------------

template<class KeyT, class ValueT>
bool LLRBTree<KeyT, ValueT>::isRed( LLRBNode<KeyT, ValueT> *node )
{
	return node->m_color == RED;
}


template<class KeyT, class ValueT>
bool LLRBTree<KeyT, ValueT>::isLeaf( LLRBNode<KeyT, ValueT> *node )
{
	return node == m_leaf;
}


template<class KeyT, class ValueT>
void LLRBTree<KeyT, ValueT>::createNode( KeyT key, ValueT value, LLRBNode<KeyT, ValueT> **node )
{
	*node = new LLRBNode<KeyT, ValueT>( key, value );
	(*node)->m_right	= m_leaf;
	(*node)->m_left		= m_leaf;
}


template<class KeyT, class ValueT>
LLRBNode<KeyT, ValueT> *LLRBTree<KeyT, ValueT>::insertHelper( KeyT key, ValueT value, LLRBNode<KeyT, ValueT> *node )
{
		LLRBNode<KeyT, ValueT> newnode(key, value);
	if ( node == m_leaf )
	{
		m_count += 1;
		LLRBNode<KeyT, ValueT> *newnode = 0;
        /* newnode = new LLRBNode<KeyT, ValueT>( key, value ); */
		createNode( key, value, &newnode );
		return newnode;


	}
	if ( isRed( node->m_left ) && isRed( node->m_right ) )
	{
		colorFlip( node );
	}
	
	if ( key == *(node->m_key) )
	{
		*(node->m_value) = value;
	}
	else if ( key < *(node->m_key) )
	{
		node->m_left = insertHelper( key, value, node->m_left );
	}
	else
	{
		node->m_right = insertHelper( key, value, node->m_right );
	}

	if ( !isRed( node->m_left ) && isRed( node->m_right ) )
	{
		node = rotateLeft( node );
	}

	if ( isRed( node->m_left ) && isRed( node->m_left->m_left ) )
	{
		node = rotateRight( node );
	}
	
	return node;
}


template<class KeyT, class ValueT>
void LLRBTree<KeyT, ValueT>::colorFlip( LLRBNode<KeyT, ValueT> * node )
{
	node->m_color = !node->m_color;
	node->m_left->m_color = !node->m_left->m_color;
	node->m_right->m_color = !node->m_right->m_color;
}


template<class KeyT, class ValueT>
LLRBNode<KeyT, ValueT> *LLRBTree<KeyT, ValueT>::rotateLeft	( LLRBNode<KeyT, ValueT> *node )
{
	LLRBNode<KeyT, ValueT> *othernode;

	othernode = node->m_right;
	node->m_right = othernode->m_left;
	othernode->m_left = node;
	othernode->m_color = node->m_color;
	node->m_color = RED;
	return othernode;
}


template<class KeyT, class ValueT>
LLRBNode<KeyT, ValueT> *LLRBTree<KeyT, ValueT>::rotateRight	( LLRBNode<KeyT, ValueT> *node )
{
	LLRBNode<KeyT, ValueT> *othernode;

	othernode = node->m_left;
	node->m_left = othernode->m_right;
	othernode->m_right = node;
	othernode->m_color = node->m_color;
	node->m_color = RED;
	return othernode;
}


template<class KeyT, class ValueT>
LLRBNode<KeyT, ValueT> *LLRBTree<KeyT, ValueT>::moveRedLeft	( LLRBNode<KeyT, ValueT> *node )
{
	colorFlip( node );
	if ( isRed( node->m_right->m_left ) )
	{
		node->m_right = rotateRight( node->m_right );
		node = rotateLeft( node );
		colorFlip( node );
	}
	return node;
}


template<class KeyT, class ValueT>
LLRBNode<KeyT, ValueT> *LLRBTree<KeyT, ValueT>::moveRedRight( LLRBNode<KeyT, ValueT> *node )
{
	colorFlip( node );
	if ( isRed( node->m_left->m_left ) )
	{
		node = rotateRight( node );
		colorFlip( node );
	}
	return node;
}



template<class KeyT, class ValueT>
LLRBNode<KeyT, ValueT> *LLRBTree<KeyT, ValueT>::deleteHelper( KeyT key, LLRBNode<KeyT, ValueT> *node )
{
	if ( isLeaf( node ) )
	{
		return node;
	}

	if ( key < *(node->m_key) )
	{
		if (	!isRed( node->m_left ) &&
				!isLeaf( node->m_left ) &&
				!isLeaf( node->m_right ) &&
				!isRed( node->m_left->m_left ) )
		{
			node = moveRedLeft( node );
		}
		node->m_left = deleteHelper( key, node->m_left );
	}
	else
	{
        cout << __LINE__;
		if ( isRed( node->m_left ) )
		{
			node = rotateRight( node );
		}

		if ( key == *(node->m_key) && node->m_right == m_leaf )
		{
			delete node;
			--m_count;
			return m_leaf;
		}
		if (	!isRed( node->m_right ) &&
				!isLeaf(node->m_right) &&
				!isLeaf(node->m_left) &&
				!isRed( node->m_right->m_left ) )
		{
			node = moveRedRight( node );
		}

		if ( key == *(node->m_key) )
		{
			LLRBNode<KeyT, ValueT> *leftmostNode = getMinNode( node->m_right );
			*(node->m_key)		= *(leftmostNode->m_key);
			*(node->m_value)	= *(leftmostNode->m_value);
			node->m_right = deleteMinHelper( node->m_right );
		}
		else
		{
			node->m_right = deleteHelper( key, node->m_right );
		}
	}
	return fixUp( node );
}


template<class KeyT, class ValueT>
LLRBNode<KeyT, ValueT> *LLRBTree<KeyT, ValueT>::deleteMinHelper( LLRBNode<KeyT, ValueT> *node )
{
	if ( node->m_left == m_leaf )
	{
		delete node;
		--m_count;
		return m_leaf;
	}
	if (	!isRed( node->m_left ) &&
			!isLeaf( node->m_left ) &&
			!isLeaf( node->m_right ) &&
			!isRed( node->m_left->m_left ) )
	{
		node = moveRedLeft( node );
	}
	node->m_left = deleteMinHelper( node->m_left );
	return fixUp( node );
}


template<class KeyT, class ValueT>
LLRBNode<KeyT, ValueT> *LLRBTree<KeyT, ValueT>::getMinNode( LLRBNode<KeyT, ValueT> *node )
{
	if ( node->m_left == m_leaf )
	{
		return node;
	}
	return getMinNode( node->m_left );
}



template<class KeyT, class ValueT>
LLRBNode<KeyT, ValueT> *LLRBTree<KeyT, ValueT>::fixUp( LLRBNode<KeyT, ValueT> *node )
{
	if ( !isRed( node->m_left ) && isRed( node->m_right ) )
	{
		node = rotateLeft( node );
	}

	if ( isRed( node->m_left ) && isRed( node->m_left->m_left ) )
	{
		node = rotateRight( node );
	}
	return node;
}