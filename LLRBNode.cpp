#include "LLRBNode.h"

template class LLRBNode<int, int>;

template<class KeyT, class ValueT>
LLRBNode<KeyT, ValueT>::LLRBNode(KeyT key, ValueT value)
{
    m_value = new ValueT(value);
    m_key = new KeyT(key);
    m_color = false;
}
