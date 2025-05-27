
namespace lasd {

  /* ************************************************************************** */


  template <typename Data>
  bool LinearContainer<Data>::operator==(
      const LinearContainer<Data> &Lcon) const noexcept {
    if (size != Lcon.size) { return false; }
  
    for (unsigned int i = 0; i < size; ++i) {
      if ((*this)[i] != Lcon[i]) {
        return false;
      }
    }
    return true;
  }
  
  template <typename Data>
  bool LinearContainer<Data>::operator!=(
      const LinearContainer<Data> &Lcon) const noexcept {
    return !(*this == Lcon);
  }
  
  template <typename Data> inline const Data &LinearContainer<Data>::Front() const {
    if (size == 0) {
      throw std::out_of_range("Empty structure.");
    }
    return (*this)[0];
  }
  
  template <typename Data>
  inline const Data &LinearContainer<Data>::Back() const {
    if (size == 0) {
      throw std::out_of_range("Empty structure.");
    }
    return (*this)[size - 1];
  }


  template <typename Data>
  void LinearContainer<Data>::Traverse(const TraverseFun fun) const {
    PreOrderTraverse(fun);
  } 


  template <typename Data>
  void LinearContainer<Data>::PostOrderTraverse(const TraverseFun fun) const {
  
    for (unsigned int i = size; i > 0;) {
      fun((*this)[--i]);
    }
  }
  

  template <typename Data>
  void LinearContainer<Data>::PreOrderTraverse(const TraverseFun fun) const {
    for (unsigned int i = 0; i < size; ++i) {
      fun((*this)[i]);
    }
  }
  

  template <typename Data>Data &MutableLinearContainer<Data>::Front() {
    if (size != 0) {
      throw std::out_of_range("Empty structure.");
    }
    return (*this)[0];
  }
  
  template <typename Data>Data &MutableLinearContainer<Data>::Back() {
    if (size == 0) {
      throw std::out_of_range("Empty structure.");
    }
    return (*this)[size - 1];
  }
  
    template <typename Data> void MutableLinearContainer<Data>::PreOrderMap(MapFun fun) {
    for (unsigned int i= 0; i < size; ++i) {
      fun((*this)[i]);
    }
  }

  template <typename Data> void MutableLinearContainer<Data>::Map(MapFun fun) {
    PreOrderMap(fun);
  } 
  
  template <typename Data> void MutableLinearContainer<Data>::PostOrderMap(MapFun fun) {
    for (unsigned int i = size; i > 0;) {
      fun((*this)[--i]);
    }
  }



template <typename Data>
void SortableLinearContainer<Data>::quickSort(unsigned long start, unsigned long end) noexcept {
  
  if (start >= end) {
    return;
  }

  if (end - start < 16) {
    insertionSort(start, end);
    return;
  }

  unsigned long pivot_position = partition(start, end);

  quickSort(start, pivot_position);
  quickSort(pivot_position + 1, end);
}

template <typename Data>
void SortableLinearContainer<Data>::insertionSort(unsigned long start,
                                                  unsigned long end) noexcept {
  
  Data currentValue;
  unsigned long currentIndex;

  for (unsigned long i = start + 1; i <= end; i++) {
    
    currentValue = (*this)[i];
    currentIndex = i;

    while (currentIndex > start && (*this)[currentIndex - 1] > currentValue) {
      (*this)[currentIndex] = (*this)[currentIndex - 1];
      --currentIndex;
    }
  
    (*this)[currentIndex] = currentValue;
  }
}

template <typename Data>
unsigned long SortableLinearContainer<Data>::partition(unsigned long start, unsigned long end) noexcept {
    
    unsigned long left = start - 1;
    unsigned long right = end + 1;
    unsigned long pivotIndex = getRandomIndex(start, end);
    
    Data pivot = (*this)[pivotIndex];

    while (true) {

        do {
            --right;
        } while ((*this)[right] > pivot);
        
        do {
            ++left;
        } while ((*this)[left] < pivot);
        
        if (left >= right) {
            return right;
        }
      
        std::swap((*this)[left], (*this)[right]);
    }
}

template <typename Data>
unsigned long SortableLinearContainer<Data>::getRandomIndex(unsigned long start, unsigned long end) 
const noexcept {
    
    std::default_random_engine generator(std::random_device{}());
    
    std::uniform_int_distribution<unsigned long> distribution(start, end);
    return distribution(generator);
}

} 
