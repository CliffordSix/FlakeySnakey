#pragma once
#if !defined   STACK_USING_COMPOSITION_HPP
#define        STACK_USING_COMPOSITION_HPP

#include "../inc/body.hpp"

namespace stack_composition {

class Stack {
public:
   void push( const std::string& data )
   {
      list_.pushFront( data );
   }

   void pop()
   {
      list_.popFront();
   }

   std::string top()
   {
      return list_.front();
   }

   int size()
   {
      return list_.size();
   }

   bool empty()
   {
      return list_.empty();
   }

private:
   List list_;
};

}

#endif // STACK_HPP
