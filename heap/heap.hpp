
#ifndef HEAP_HPP
#define HEAP_HPP

/* ************************************************************************** */

#include "../container/linear.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class Heap : virtual public SortableLinearContainer<Data>, 
             virtual public ClearableContainer {
 

private:

protected:

public:

  // Destructor
  virtual ~Heap() = default;

  /* ************************************************************************ */

  // Copy assignment
  Heap& operator=(const Heap&) = delete; 

  // Move assignment
  Heap& operator=(Heap&&) = delete; 

  /* ************************************************************************ */

  // Specific member functions
  //funzione che dovrebbe verificare se la proprietà è soddisfatta 
  virtual bool IsHeap() const noexcept = 0; //se lo è, allora true

  virtual void Heapify() = 0; //riorganizza la struttura 

};

/* ************************************************************************** */

}

#endif
