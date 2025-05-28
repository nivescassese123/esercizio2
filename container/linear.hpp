
#ifndef LINEAR_HPP
#define LINEAR_HPP


#include "mappable.hpp"
#include <algorithm>
#include <climits>
#include <random>


namespace lasd {

/* ************************************************************************** */

template <typename Data>
class LinearContainer : virtual public PreOrderTraversableContainer<Data>,
                        virtual public PostOrderTraversableContainer<Data> {
 

private:



protected:

  using Container::size;

public:

  // Destructor
  virtual ~LinearContainer() = default;

  /* ************************************************************************ */

  // Copy assignment
  LinearContainer &operator=(const LinearContainer &) = delete; 

  // Move assignment
  LinearContainer &operator=(LinearContainer &&) noexcept = delete; 

  /* ************************************************************************ */

  // Comparison operators
  inline bool operator==(const LinearContainer &) const noexcept; 
  inline bool operator!=(const LinearContainer &) const noexcept; 

  /* ************************************************************************ */

  // Specific member functions

  virtual const Data &operator[](unsigned long) const = 0;

  virtual inline  const Data &Front() const; 

  virtual inline const Data &Back() const; 

  /* ************************************************************************ */

  // Specific member function (inherited from TraversableContainer)

  using typename TraversableContainer<Data>::TraverseFun;

  inline void Traverse(TraverseFun) const override; 

  /* ************************************************************************ */

  // Specific member function (inherited from PreOrderTraversableContainer)

  inline void PreOrderTraverse(TraverseFun) const override; 
  /* ************************************************************************ */

  // Specific member function (inherited from PostOrderTraversableContainer)

  inline void PostOrderTraverse(TraverseFun) const override; 

};

/* ************************************************************************** */

template <typename Data>
class MutableLinearContainer : virtual public LinearContainer<Data>,
                               virtual public PreOrderMappableContainer<Data>,
                               virtual public PostOrderMappableContainer<Data> { 


private:


protected:

  using Container::size;

public:

  // Destructor
  virtual ~MutableLinearContainer() = default;

  /* ************************************************************************ */

  // Copy assignment
  MutableLinearContainer &operator=(const MutableLinearContainer &) = delete; 

  // Move assignment
  MutableLinearContainer &operator=(MutableLinearContainer &&) noexcept = delete; 

  /* ************************************************************************ */

  // Specific member functions
  using LinearContainer<Data>::operator[];
  using LinearContainer<Data>::Front;
  using LinearContainer<Data>::Back;

  virtual inline Data &operator[](unsigned long) = 0;     

  virtual Data &Front();  

  virtual Data &Back(); 

  /* ************************************************************************ */

  // Specific member function (inherited from MappableContainer)

  using typename MappableContainer<Data>::MapFun;

  inline void Map(MapFun fun) override;

  /* ************************************************************************ */

  // Specific member function (inherited from PreOrderMappableContainer)

  void PreOrderMap(MapFun) override;

  /* ************************************************************************ */

  // Specific member function (inherited from PostOrderMappableContainer)

  void PostOrderMap(MapFun) override; 

};

template <typename Data>
class SortableLinearContainer : virtual public MutableLinearContainer<Data> {
  

private:


protected:

  using Container::size;  

public:

  // Destructor
  virtual ~SortableLinearContainer() = default;

  /* ************************************************************************ */

  SortableLinearContainer &operator=(const SortableLinearContainer &) noexcept = delete;

  SortableLinearContainer &operator=(SortableLinearContainer &&) noexcept = delete;

  /* ************************************************************************ */

  // Specific member function

   virtual void Sort() noexcept {
    quickSort(0, size - 1);
  }; 
  

protected:

  // Auxiliary member functions

  void quickSort(unsigned long, unsigned long) noexcept;

  void insertionSort(unsigned long, unsigned long) noexcept;

  unsigned long partition(unsigned long, unsigned long) noexcept;

  unsigned long getRandomIndex(unsigned long, unsigned long) const noexcept;

};

}
/* ************************************************************************** */


#include "linear.cpp"

#endif
