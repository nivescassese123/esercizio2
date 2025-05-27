#ifndef CONTAINER_HPP
#define CONTAINER_HPP


namespace lasd {


class Container {

private:


protected:

  unsigned long size = 0;


  // Default constructor
    Container() = default;

public:

  // Destructor
    virtual ~Container() = default;

  /* ************************************************************************ */

  // Copy assignment
    Container& operator=(const Container&) = delete; 


  // Move assignment
    Container& operator=(Container&&) = delete; 

  /* ************************************************************************ */


  // Comparison operators
    bool operator==(const Container&) = delete; 
    bool operator!=(const Container&) = delete; 

  /* ************************************************************************ */

  // Specific member functions 

    virtual bool Empty()const noexcept { return size==0; } ; 


    virtual unsigned long Size()const noexcept { return size; }

};


/* ************************************************************************** */
/* ************************************************************************** */

class ClearableContainer : virtual public Container {
  

private:


protected:

  using Container::size;

public:

  // Destructor
    ~ClearableContainer() = default;

  /* ************************************************************************ */

  // Copy assignment
  ClearableContainer& operator=(const ClearableContainer&) = delete;

  // Move assignment
  ClearableContainer& operator=(ClearableContainer&&) = delete;  

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const ClearableContainer&) = delete; 
  bool operator!=(const ClearableContainer&) = delete; 

  /* ************************************************************************ */

  // Specific member functions

    virtual void Clear() = 0;

};

/* ************************************************************************** */

class ResizableContainer: virtual public ClearableContainer {


private:

 

protected:

  using Container::size;

public:

  // Destructor
    ~ResizableContainer() = default;

  /* ************************************************************************ */

  // Copy assignment
    ResizableContainer& operator=(const ResizableContainer&) = delete;

  // Move assignment
    ResizableContainer& operator=(ResizableContainer&&) = delete;

  /* ************************************************************************ */

  // Comparison operators
    bool operator==(const ResizableContainer&) const = delete;
    bool operator!=(const ResizableContainer&) const = delete;

  /* ************************************************************************ */

  // Specific member functions


    virtual void Resize(unsigned long newSize) = 0;

  /* ************************************************************************ */


    void Clear() override{ Resize(0); }; 

};

/* ************************************************************************** */

}

#endif