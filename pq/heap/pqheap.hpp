
#ifndef PQHEAP_HPP
#define PQHEAP_HPP

/* ************************************************************************** */

#include "../pq.hpp"
#include "../../heap/vec/heapvec.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class PQHeap :   public PQ<Data>,
                 public HeapVec<Data> {
  // Must extend PQ<Data>,
  // Could extend HeapVec<Data>

private:

  // ...

protected:

    using Container::Size;
    using Vector<Data>::elements;
    using Vector<Data>::size;
    using HeapVec<Data>::HeapifyDown;
    using HeapVec<Data>::HeapifyUp;
    
    

  // ...

public:

  // Default constructor
  PQHeap() = default;

  /* ************************************************************************ */

  // Specific constructors
  explicit PQHeap(const TraversableContainer<Data>&); // A priority queue obtained from a TraversableContainer
  explicit PQHeap(const MappableContainer<Data>&); // A priority queue obtained from a MappableContainer
  

  /* ************************************************************************ */

  // Copy constructor
  PQHeap(const PQHeap&);

  // Move constructor
  PQHeap(PQHeap&&) noexcept;

  /* ************************************************************************ */

  // Destructor
  ~PQHeap() = default;

  /* ************************************************************************ */

  // Copy assignment
  PQHeap& operator=(const PQHeap&);

  // Move assignment
  PQHeap& operator=(PQHeap&&) noexcept;

  /* ************************************************************************ */

  // Specific member functions (inherited from PQ)
//tip deve restituire il massimo, sarebbe la radice dell'heap
   virtual const Data& Tip() const override; // Override PQ member (must throw std::length_error when empty)
  
   //remove tip deve rimuovere il massimo e deve riorganizzare l'heap
   virtual void RemoveTip() override; // Override PQ member (must throw std::length_error when empty)
  
   //deve restituire e rimuovere il massimo
   virtual Data TipNRemove() override; // Override PQ member (must throw std::length_error when empty)

   virtual void Insert(const Data&) override; // Override PQ member (Copy of the value)
   virtual void Insert(Data&&) noexcept override; // Override PQ member (Move of the value)

   virtual void Change(unsigned long, const Data&) override; // Override PQ member (Copy of the value)
   virtual void Change(unsigned long, Data&&) noexcept  override; // Override PQ member (Move of the value)

protected:

  // Auxiliary functions, if necessary!
  
  void HeapifyUp(unsigned long index);

};

/* ************************************************************************** */

}

#include "pqheap.cpp"

#endif
