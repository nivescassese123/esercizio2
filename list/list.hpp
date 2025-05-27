
#ifndef LIST_HPP
#define LIST_HPP

/* ************************************************************************** */

#include "../container/linear.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class List : virtual public MutableLinearContainer<Data>,
             virtual public ClearableContainer {


private:



protected:

    using Container::size;

  struct Node {

      Data element;
      Node* next = nullptr;

    /* ********************************************************************** */

    //Constructor
      inline Node() = default;

    // Specific constructors
    //dichiarazione e implementazione 
      inline Node(const Data &dat) :
       element(dat) {

       };

      inline Node(Data&&) noexcept;

    /* ********************************************************************** */

    // Copy constructor
      inline Node(const Node &nod) : 
      element(nod.element) {

      };

    // Move constructor
      inline Node(Node &&) noexcept ;

    /* ********************************************************************** */

    // Destructor
      virtual ~Node();

    /* ********************************************************************** */

    // Comparison operators
      inline bool operator==(const Node &) const noexcept; 

      inline bool operator!=(const Node &) const noexcept; 

    /* ********************************************************************** */

    // Specific member functions

      virtual Node * Clone(Node *);

  };

    Node *Tail= nullptr;
    Node *Head= nullptr;

public:

  // Default constructor
    List() = default;

  /* ************************************************************************ */

  // Specific constructor
    List(const TraversableContainer<Data> &);
    List(MappableContainer<Data> &&); 

  /* ************************************************************************ */

  // Copy constructor
    List(const List &);

  // Move constructor
    List(List &&) noexcept;

  /* ************************************************************************ */

  // Destructor
    virtual ~List();

  /* ************************************************************************ */

  // Copy assignment
    List &operator=(const List &);

  // Move assignment
    List &operator=(List &&) noexcept;

  /* ************************************************************************ */

  // Comparison operators
    inline bool operator==(const List &) const noexcept;
    inline bool operator!=(const List &) const noexcept;

  /* ************************************************************************ */

  // Specific member functions

  //Front
    void InsertAtFront(const Data&); 
    void InsertAtFront(Data&&);   
    void RemoveFromFront();   
    Data FrontNRemove();  

  //Back
    void InsertAtBack(const Data&);   
    void InsertAtBack(Data&&);  
    void RemoveFromBack();  
    Data BackNRemove() ;  

  /* ************************************************************************ */

  // Specific member functions (inherited from MutableLinearContainer)

    Data &operator[](const unsigned long) override;    

    Data &Front() override;     

    Data &Back() override;  

  /* ************************************************************************ */

  // Specific member functions (inherited from LinearContainer)

    const Data &operator[](const unsigned long) const override;   

    const Data &Front() const override;   

    const Data &Back() const override;   

  /* ************************************************************************ */

  // Specific member function (inherited from MappableContainer)

    using typename MappableContainer<Data>::MapFun;

    inline void Map(MapFun fun) override {
    PreOrderMap(fun);
    }

  /* ************************************************************************ */

  // Specific member function (inherited from PreOrderMappableContainer)

    inline void PreOrderMap(MapFun fun) override {
       PreOrderMap(fun, Head);
       } 

  /* ************************************************************************ */

  // Specific member function (inherited from PostOrderMappableContainer)

    inline void PostOrderMap(MapFun fun) override { 
      PostOrderMap(fun, Head);
     } 

  /* ************************************************************************ */

  // Specific member function (inherited from TraversableContainer)

    using typename TraversableContainer<Data>::TraverseFun;

    inline void Traverse(TraverseFun fun) const override {
    PreOrderTraverse(fun);
    }

  /* ************************************************************************ */

  // Specific member function (inherited from PreOrderTraversableContainer)

    inline void PreOrderTraverse(TraverseFun fun) const override {
    PreOrderTraverse(fun, Head);
    } 

  /* ************************************************************************ */

  // Specific member function (inherited from PostOrderTraversableContainer)

    inline void PostOrderTraverse(TraverseFun fun) const override {
      PostOrderTraverse(fun, Head);
    } 

  /* ************************************************************************ */

  // Specific member function (inherited from ClearableContainer)

    inline void Clear() noexcept override;  

    using TestableContainer<Data>::Exists;

protected:

  // Auxiliary functions, if necessary!

  void PreOrderTraverse(TraverseFun, Node *) const;

  void PostOrderTraverse(TraverseFun, Node *) const;

  void PreOrderMap(MapFun, Node *) const;

  void PostOrderMap(MapFun, Node *) const;

};

/* ************************************************************************** */

}

#include "list.cpp"

#endif
