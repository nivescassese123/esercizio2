
#ifndef SETLST_HPP
#define SETLST_HPP

/* ************************************************************************** */

#include "../set.hpp"
#include "../../list/list.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class SetLst : virtual public Set<Data>,
               virtual public List<Data> {


private:

 

protected:
   using List<Data>::Node;
   using List<Data>::Head;
   using List<Data>::Tail;
   using Container::size;
   
   

public:

  // Default constructor
    SetLst() = default;


  /* ************************************************************************ */

  // Specific constructors
    SetLst(const TraversableContainer<Data>&);  
    SetLst(MappableContainer<Data>&&);  

  /* ************************************************************************ */

  // Copy constructor
    SetLst(const SetLst<Data>& val) : 
    List<Data>(val) {

    }


  // Move constructor

    SetLst(SetLst<Data>&& val) noexcept :
     List<Data>(std::move(val)) {

     }

    

  /* ************************************************************************ */

  // Destructor
    ~SetLst() = default;


  /* ************************************************************************ */

  // Copy assignment
  SetLst& operator=(const SetLst<Data>&);

  // Move assignment
  SetLst& operator=(SetLst<Data>&&) noexcept;

  // Comparison operators
  bool operator==(const SetLst<Data>&) const noexcept;
  bool operator!=(const SetLst<Data>&) const noexcept;

  /* ************************************************************************ */

  // Specific member functions (inherited from OrderedDictionaryContainer)

    Data Min() const override;    
    Data MinNRemove() override;   
    void RemoveMin() override;  

    Data Max() const override;  
    Data MaxNRemove() override;   
    void RemoveMax() override;  

    Data Predecessor(const Data&) const;  
    Data PredecessorNRemove(const Data&);   
    void RemovePredecessor(const Data&);  

    Data Successor(const Data&) const override;   
    Data SuccessorNRemove(const Data&) override;  
    void RemoveSuccessor(const Data&) override;   

  /* ************************************************************************ */

  // Specific member functions (inherited from DictionaryContainer)

    bool Insert(const Data&) override;  
    bool Insert(Data&&) override;   
    bool Remove(const Data&) override;  

  /* ************************************************************************ */

  // Specific member functions (inherited from LinearContainer)

    const Data& operator[](const unsigned long index) const override;   

  /* ************************************************************************** */

  // Specific member function (inherited from TestableContainer)

    bool Exists(const Data&) const noexcept override; 

  /* ************************************************************************ */

  // Specific member function (inherited from ClearableContainer)

  void Clear() noexcept override;

protected:

  

};

/* ************************************************************************** */

}

#include "setlst.cpp"

#endif