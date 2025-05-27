
#ifndef SETVEC_HPP
#define SETVEC_HPP

/* ************************************************************************** */

#include "../set.hpp"
#include "../../vector/vector.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class SetVec : virtual public Set<Data>,
               virtual public ResizableContainer {

private:

  

protected:

   using Container::size;

   Vector<Data> elements;

public:

  // Default constructor
     SetVec() = default;

  /* ************************************************************************ */

  // Specific constructors
    SetVec(const TraversableContainer<Data>&); 
    SetVec(MappableContainer<Data>&&); 

  /* ************************************************************************ */

  // Copy constructor
    SetVec(const SetVec<Data>&);

  // Move constructor
    SetVec(SetVec<Data>&&);

  /* ************************************************************************ */

  // Destructor
    virtual ~SetVec();

  /* ************************************************************************ */

  // Copy assignment
    inline SetVec<Data> &operator=(const SetVec<Data> &);

  // Move assignment
    inline SetVec<Data> &operator=(SetVec<Data> &&) noexcept;

  /* ************************************************************************ */

  // Comparison operators
    inline bool operator==(const SetVec<Data> &) const noexcept;
    inline bool operator!=(const SetVec<Data> &) const noexcept;

  /* ************************************************************************ */

   // Specific member functions (inherited from OrderedDictionaryContainer)

    Data Min()const override;
    Data MinNRemove()override; 
    void RemoveMin() override;    

    Data Max()const override;
    Data MaxNRemove()override;
    void RemoveMax() override;  
 
    Data Predecessor(const Data&)const override;  
    Data PredecessorNRemove(const Data&)override; 
    void RemovePredecessor(const Data&) override;   
  
    Data Successor(const Data&)const override;  
    Data SuccessorNRemove(const Data&)override; 
    void RemoveSuccessor(const Data&) override;   

  /* ************************************************************************ */

  // Specific member functions (inherited from DictionaryContainer)

    bool Insert(const Data&) override;  
    bool Insert(Data&&) override;   
    bool Remove(const Data&) override;  

  /* ************************************************************************ */

  // Specific member functions (inherited from LinearContainer)

   const Data& operator[](unsigned long index) const override;    

  /* ************************************************************************** */

  // Specific member function (inherited from TestableContainer)

    bool Exists(const Data&)const noexcept override;  

  /* ************************************************************************ */

  // Specific member function (inherited from ClearableContainer)

   void Clear() override; 

protected:

 long FindIndexHelper(const Data&) const;
 long FindIndex(const Data&) const;
 void Resize(unsigned long) override; 

};

/* ************************************************************************** */

}

#include "setvec.cpp"

#endif