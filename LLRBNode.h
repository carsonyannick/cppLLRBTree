#include <iostream>
template<class KeyT, class ValueT>
class LLRBNode
{
public:
    LLRBNode(KeyT key, ValueT value);

/* private: */
    KeyT *m_key;
    ValueT *m_value;
    LLRBNode * m_left;
    LLRBNode * m_right;
    bool m_color;
};
