
#ifndef HEAPVEC_HPP
#define HEAPVEC_HPP

/* ************************************************************************** */

#include "../heap.hpp"
#include "../../vector/vector.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class HeapVec :   public Heap<Data>,
                 public SortableVector<Data> {
 
private:

  
protected:

   using Vector<Data>::elements;

   using Vector<Data>::size;
   using Container::Empty;

 

public:


  // Default constructor
   HeapVec() = default;

  
   // Constructors 
   explicit HeapVec(const TraversableContainer<Data> &); 
   explicit HeapVec(const MappableContainer<Data> &&); 

  /* ************************************************************************ */

  // Copy constructor
   HeapVec(const HeapVec &);

  // Move constructor
   HeapVec(HeapVec &&) noexcept;

  /* ************************************************************************ */

  // Destructor
   ~HeapVec() = default;

  /* ************************************************************************ */

  // Copy assignment
  HeapVec& operator=(const HeapVec&); 

  // Move assignment
  HeapVec& operator=(HeapVec&&) noexcept;

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const HeapVec &) const noexcept;
  bool operator!=(const HeapVec &) const noexcept;

  /* ************************************************************************ */

  // Specific member functions (inherited from Heap)

   bool IsHeap() const  noexcept override; 

   void Heapify() override; 

  /* ************************************************************************ */

  // Specific member function (inherited from SortableLinearContainer)

  void Sort() noexcept override; 

protected:

  // Auxiliary functions, if necessary!

unsigned long Parent(unsigned long index) const noexcept {
    return (index == 0) ? 0 : (index - 1) / 2;
  }

  unsigned long LeftChild(unsigned long index) const noexcept {
    return (2 * index) + 1;
  }

  unsigned long RightChild(unsigned long index) const noexcept {
    return (2 * index) + 2;
  }

  void HeapifyDown(unsigned long);
  void HeapifyUp(unsigned long);


};

/* ************************************************************************** */

}

#include "heapvec.cpp"

#endif
