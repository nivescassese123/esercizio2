
namespace lasd {

  /* ************************************************************************** */
  
  template<typename Data>
  Vector<Data>::Vector(const unsigned long newsize){
      size = newsize;
      elements = new Data[size]{};
  }
  

  
  template <typename Data>
  inline Vector<Data>::Vector(Vector<Data> &&vec) {
    std::swap(size, vec.size);
    std::swap(elements, vec.elements);
  }


  template <typename Data>
  inline Vector<Data>::Vector(const Vector<Data> &vec) : Vector(vec.size) {
    std::uninitialized_copy(vec.elements, vec.elements + size, elements);
  }
  

  template<typename Data>
  Vector<Data>::Vector(const TraversableContainer<Data> &Tcon ): Vector(Tcon.Size()) {
    unsigned long i{0};
    Tcon.Traverse(
        [this, &i](const Data &currData) { elements[i++] = currData; });
  }
  
  

  template <typename Data>
  inline Vector<Data>::Vector(MappableContainer<Data> &&con): Vector(con.Size()) {
    unsigned long i{0};
    con.Map(
        [this, &i](Data &currData) { elements[i++] = std::move(currData); });
  }
  
  
  
  template<typename Data>
  Vector<Data>::~Vector(){
      delete[] elements;
  }
  
  
  //Assignment
  /* ************************************************************************** */
  
  //Copy Assignment
  template<typename Data>
  Vector<Data> & Vector<Data>::operator=(const Vector<Data> &vec){
    Vector<Data> temp{vec};
    if(temp.size > size){
      Resize(vec.Size());
      std::swap(temp, *this);
      return *this;
    } 
    std::swap(temp, *this);
    return *this;
  }
  
  
  //Move Assignment
  template <typename Data>
  inline Vector<Data> &Vector<Data>::operator=(Vector<Data> &&vec) noexcept {
    std::swap(size, vec.size);
    std::swap(elements, vec.elements);
    return *this;
  }
  
  
  // Comparison operators
  /* ************************************************************************** */
  
  //Operator ==
  template <typename Data>
  bool Vector<Data>::operator==(const Vector<Data> &vector) const noexcept {
    if (size != vector.size) {
      return false;
    }
  
    for (unsigned int i = 0; i < size; i++) {
      if (elements[i] != vector[i]) {
        return false;
      }
    }
    return true;
  }
  
  
  //Operator !=
  template <typename Data>
  inline bool Vector<Data>::operator!=(const Vector<Data> &vector) const noexcept {
    return !(*this == vector);
  }
  
  
  /* ************************************************************************** */
  
  //Mutable Operator[]
  template <typename Data>
  inline Data &Vector<Data>::operator[](unsigned long i) {
    if (i >= size) {
      throw std::out_of_range("This Vector has not that many elements");
    }
    return elements[i];
  }
  
  
  //Mutable Front
  template <typename Data> inline Data &Vector<Data>::Front() {
    if (size != 0)
      return elements[0];
    throw std::length_error("The Vector is empty");
  }
  
  
  //Mutable Back
  template <typename Data> inline Data &Vector<Data>::Back() {
    if (size != 0)
      return elements[size - 1];
    throw std::length_error("The Vector is empty");
  }
  
  
  
  
  // Specific member functions (inherited from LinearContainer)
  /* ************************************************************************** */
  
  
  //Linear Operator[]
  template <typename Data>
  inline const Data &Vector<Data>::operator[](unsigned long i) const {
    if (i >= size) {
      throw std::out_of_range("This Vector has not that many elements");
    }
    return elements[i];
  }
  
  
  
  //Linear Front
  template <typename Data> inline const Data &Vector<Data>::Front() const {
    if (size != 0)
      return elements[0];
    throw std::length_error("The Vector is empty");
  }
  
  
  //Linear Back
  template <typename Data> inline const Data &Vector<Data>::Back() const {
    if (size != 0)
      return elements[size - 1];
    throw std::length_error("The Vector is empty");
  }
  

  //Clear
  template <typename Data>
  void Vector<Data>::Clear(){
     delete[] elements;
     elements = nullptr;
     size = 0;
     
  }
  
  //Resize
  template <typename Data>
  void Vector<Data>::Resize(const unsigned long newSize) {
  
      if(newSize == 0){
        Clear();
      }
      else if(size != newSize){
          unsigned int limit = (size < newSize) ? size : newSize;
          Data* tempElems = new Data[newSize] {};
  
          for(unsigned long i = 0; i < limit; i++){
  
              std::swap(elements[i], tempElems[i]);
          }
  
          std::swap(elements, tempElems);
          size = newSize;
          delete[] tempElems;
  
      }
        
  }
  
  //Copy Assignment
  template <typename Data>
  inline SortableVector<Data> &
  SortableVector<Data>::operator=(const SortableVector<Data> &Svec) {
    Vector<Data>::operator=(Svec);
    return *this;
  }
  
  //Move Assignment
  template <typename Data>
  inline SortableVector<Data> &
  SortableVector<Data>::operator=(SortableVector<Data> &&Svec) noexcept {
    Vector<Data>::operator=(std::move(Svec));
    return *this;
  }
  
  
  /* ************************************************************************** */
  
  }
  