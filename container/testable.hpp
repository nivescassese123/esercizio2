
#ifndef TESTABLE_HPP
#define TESTABLE_HPP

/* ************************************************************************** */

#include "container.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class TestableContainer : virtual public Container {
  

private:

  

protected:

  
public:

  // Destructor
  ~TestableContainer() = default;

  /* ************************************************************************ */

  // Copy assignment
  TestableContainer& operator=(const TestableContainer &) = delete; 

  // Move assignment
  TestableContainer& operator=(TestableContainer &&) = delete;

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const TestableContainer &) const = delete;
  bool operator!=(const TestableContainer &) const = delete;

  /* ************************************************************************ */

  // Specific member function

  virtual bool Exists(const Data &) const noexcept = 0; 
};

/* ************************************************************************** */

}

#endif
