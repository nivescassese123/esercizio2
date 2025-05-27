
#ifndef HEAPVEC_HPP
#define HEAPVEC_HPP

/* ************************************************************************** */

#include "../heap.hpp"
#include "../../vector/vector.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class HeapVec :  public Heap<Data>,
                 public SortableVector<Data> {
  // Must extend Heap<Data>,
  // Could extend SortableVector<Data>

private:

  // se non estendo sortable, avrei dovuto riscrivere tante righe di codice e metterlo private

protected:

   using Container::Size;
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
   explicit HeapVec(const MappableContainer<Data> &); // A heap obtained from a MappableContainer

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

  virtual bool IsHeap() const  noexcept override; // Override Heap member

  virtual void Heapify() override; // Override Heap member

  /* ************************************************************************ */

  // Specific member function (inherited from SortableLinearContainer)

  void Sort() noexcept override; // Override SortableLinearContainer member

protected:

  // Auxiliary functions, if necessary!

    // Funzioni di utilità per la navigazione dell'heap
  unsigned long Parent(unsigned long idx) const {
      if (idx == 0) return 0; // La radice non ha genitore, o questo caso non dovrebbe essere chiamato
      return (idx - 1) / 2;
  }

  unsigned long LeftChild(unsigned long idx) const {
      return (2 * idx) + 1;
  }

  unsigned long RightChild(unsigned long idx) const {
      return (2 * idx) + 2;
  }
  
  void HeapifyDown(unsigned long index);
  void HeapifyUp(unsigned long index);
  

};

/* ************************************************************************** */

}

#include "heapvec.cpp"

#endif
