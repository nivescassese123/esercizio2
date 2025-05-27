
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
  // Must extend Heap<Data>,
  // Could extend SortableVector<Data>

private:

  // se non estendo sortable, avrei dovuto riscrivere tante righe di codice e metterlo private

protected:

   
   using Vector<Data>::elements;
   
   using Vector<Data>::size;
   using Container::Empty;

  // ...

public:

  // Default constructor
   HeapVec() = default;

  /* ************************************************************************ */

  // Specific constructors
   explicit HeapVec(const TraversableContainer<Data> &); // A heap obtained from a TraversableContainer
   explicit HeapVec(const MappableContainer<Data> &&); // A heap obtained from a MappableContainer

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
  HeapVec& operator=(const HeapVec&); //li devo implementare quindi niente = delete

  // Move assignment
  HeapVec& operator=(HeapVec&&) noexcept;

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const HeapVec &) const noexcept;
  bool operator!=(const HeapVec &) const noexcept;

  /* ************************************************************************ */

  // Specific member functions (inherited from Heap)

   bool IsHeap() const  noexcept override; // Override Heap member

   void Heapify() override; // Override Heap member

  /* ************************************************************************ */

  // Specific member function (inherited from SortableLinearContainer)

  void Sort() noexcept override; // Override SortableLinearContainer member

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
