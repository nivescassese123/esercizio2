
#ifndef MAPPABLE_HPP
#define MAPPABLE_HPP

/* ************************************************************************** */

#include <functional>

/* ************************************************************************** */

#include "traversable.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class MappableContainer : virtual public TraversableContainer<Data> {  

private:

  

protected:

  

public:

  // Destructor
   virtual ~MappableContainer() = default;

  /* ************************************************************************ */

  // Copy assignment
    MappableContainer &operator=(const MappableContainer &) noexcept = delete;  

  // Move assignment
    MappableContainer &operator=(MappableContainer &&) noexcept = delete;   

  /* ************************************************************************ */

  // Comparison operators
    bool operator==(const MappableContainer &) const noexcept = delete;   
    bool operator!=(const MappableContainer &) const noexcept = delete;   

  /* ************************************************************************ */

  // Specific member function

    using MapFun = std::function<void(Data &)>;

    virtual void Map(MapFun) = 0;

};

/* ************************************************************************** */

template <typename Data>
class PreOrderMappableContainer: virtual public MappableContainer<Data>, 
                                 virtual public PreOrderTraversableContainer<Data>  {


private:

  

protected:

  

public:

  // Destructor
    virtual ~PreOrderMappableContainer() = default;

  /* ************************************************************************ */

  // Copy assignment
    PreOrderMappableContainer &operator=(const PreOrderMappableContainer &) = delete;   

  // Move assignment
    PreOrderMappableContainer &operator=(PreOrderMappableContainer &&) noexcept = delete;   

  /* ************************************************************************ */

  // Comparison operators
    bool operator==(const PreOrderMappableContainer &) const noexcept = delete;   
    bool operator!=(const PreOrderMappableContainer &) const noexcept = delete;   


  /* ************************************************************************ */

  // Specific member function

    using typename MappableContainer<Data>::MapFun;

    virtual void  PreOrderMap(const MapFun) = 0;

  /* ************************************************************************ */

  // Specific member function (inherited from MappableContainer)

    inline void  Map(const MapFun fun) override{ 
      PreOrderMap(fun); 
    }; 

};

/* ************************************************************************** */

template <typename Data>
class PostOrderMappableContainer : virtual public MappableContainer<Data>,
                                   virtual public PostOrderTraversableContainer<Data> {


private:

  

protected:

 

public:

  // Destructor
    virtual ~PostOrderMappableContainer() =  default;

  /* ************************************************************************ */

  // Copy assignment
  PostOrderMappableContainer &operator=(const PostOrderMappableContainer &) = delete;   

  // Move assignment
  PostOrderMappableContainer &operator=(PostOrderMappableContainer &&) noexcept = delete;   

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const PostOrderMappableContainer &) const noexcept = delete;  
  bool operator!=(const PostOrderMappableContainer &) const noexcept = delete;  

  /* ************************************************************************ */

  // Specific member function

  using typename MappableContainer<Data>::MapFun;

  virtual void  PostOrderMap(const MapFun) = 0;

  /* ************************************************************************ */

  // Specific member function (inherited from MappableContainer)

   inline void  Map(const MapFun fun) override{
    PostOrderMap(fun);
  }; 

};

/* ************************************************************************** */

}

#include "mappable.cpp"

#endif
