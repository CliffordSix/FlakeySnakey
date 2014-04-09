#include "../inc/list.hpp"
#include <iostream>

List::~List()
{
    while(!empty() ) {

    }

}

void List::pushBack( const point& midpoint )
{
   tail_ = new Node( midpoint, tail_ );

   if( !head_ ) {
      head_ = tail_;
   }

   ++size_;
}
void List::popBack()
{
    if( empty() ) {
        std::cout << "The snake has no body to lose" << std::endl;
        return;
    }

    Node* old_tail = tail_;

    tail_ = tail_->prev_;

    if( !tail_ ) {
        head_ = nullptr;
    }
    else{
        tail_->next_ = nullptr;
    }

    delete old_tail;

    --size_;

}
Node::Node( const point& midpoint, Node* prev, Node* next ) : midpoint_( midpoint ), prev_( prev ), next_( next )
{
}
