
#ifndef SET_HPP
#define SET_HPP

/* ************************************************************************** */

#include "../container/dictionary.hpp"
#include "../container/traversable.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class Set : virtual public OrderedDictionaryContainer<Data>,
            virtual public LinearContainer<Data>,
            virtual public ClearableContainer {


private:

 

protected:

 

public:

  // Destructor
   ~Set() = default;

  /* ************************************************************************ */

  // Copy assignment
  Set& operator=(const Set&) noexcept = delete; 

  // Move assignment
  Set& operator=(Set&&) noexcept = delete; 

};

/* ************************************************************************** */

}

#endif
