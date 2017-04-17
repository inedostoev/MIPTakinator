#ifndef NODE_H_INCLUDED
#define NODE_H_INCLUDED

#include <stdio.h> 
#include <stdlib.h>
class Node
{
public:
inline          Node(Node* parent, char* data); 
    
                ~Node() {
                    free(data_);
                    if(left_) delete left_;
                    if(right_) delete right_;
                    parent_ = left_ = right_ = NULL;
                }
    Node*       parent_;
    char*       data_;
    Node*       left_;
    Node*       right_;

    Node&       operator = (const Node&);
                Node(const Node&);
};

Node::Node(Node* parent, char* data) :
    parent_     (parent),
    data_       (data),
    left_       (NULL),
    right_      (NULL)
{}
/*
Node::~Node() {
    if(!left_) delete left_;
    if(!right_) delete right_;
    parent_ = left_ = right_ = NULL; 
}
*/

#endif // !NODE_H_INCLUDED
