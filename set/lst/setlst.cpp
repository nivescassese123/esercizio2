
namespace lasd {

  /* ************************************************************************** */
  
// constructor from TraversableContainer
  template <typename Data>
  SetLst<Data>::SetLst(const TraversableContainer<Data>& Tcon) {
    Tcon.Traverse(
      [this](const Data& dat) {
        this->Insert(dat); 
      }
    );
  }
  
  
// constructor from MappableContainer
  template <typename Data>
  SetLst<Data>::SetLst(MappableContainer<Data>&& Mcon) {
    Mcon.Map(
      [this](Data& dat) {
        this->Insert(std::move(dat));
      }
    );
  }
  

// Copy assignment
  template <typename Data>
  SetLst<Data>& SetLst<Data>::operator=(const SetLst<Data>& other) {
    List<Data>::operator=(other); 
    return *this;
  }
  
  
// Move assignment
  template <typename Data>
  SetLst<Data>& SetLst<Data>::operator=(SetLst<Data>&& other) noexcept {
    List<Data>::operator=(std::move(other)); 
    return *this;
  }
  
  /* ************************************************************************** */
  
//operator==
  template <typename Data>
  bool SetLst<Data>::operator==(const SetLst<Data>& other) const noexcept {
    return List<Data>::operator==(other); 
  }
 
 //operator!= 
  template <typename Data>
  bool SetLst<Data>::operator!=(const SetLst<Data>& other) const noexcept {
    return !(*this == other); 
  }
  
  
  // Specific member functions (inherited from OrderedDictionaryContainer)
  /* ************************************************************************** */

  template <typename Data>
  Data SetLst<Data>::Min() const {
    if (this->Empty()) throw std::length_error("Set is empty");
    return this->Front(); 
  }
  

  template <typename Data>
  Data SetLst<Data>::MinNRemove() {
    if (this->Empty()) throw std::length_error("Set is empty");
  
    Data minElem = this->Front(); 
    Remove(minElem); 
  
    return minElem;
  }
  

  template <typename Data>
  void SetLst<Data>::RemoveMin() {
    if (this->Empty()) throw std::length_error("Set is empty");
    Remove(this->Front()); 
  }
  
  
  
//Max
  /* ************************************************************************** */

  template <typename Data>
  Data SetLst<Data>::Max() const {
    if (this->Empty()) throw std::length_error("Set is empty");
    return this->Back(); 
  }
  
  
  template <typename Data>
  Data SetLst<Data>::MaxNRemove() {
    if (this->Empty()) throw std::length_error("Set is empty");
  
    Data maxElem = this->Back(); 
    Remove(maxElem); 
  
    return maxElem;
  }
  

  template <typename Data>
  void SetLst<Data>::RemoveMax() {
    if (this->Empty()) throw std::length_error("Set is empty");
    Remove(this->Back()); 
  }
  
  
/* ************************************************************************** */

template <typename Data>
Data SetLst<Data>::Predecessor(const Data& val) const {
    if (!this->Head)
        throw std::length_error("The list is empty.");

    auto* ptr = this->Head;
    const Data* result = nullptr;

    while (ptr && ptr->element < val) {
        result = &(ptr->element);
        ptr = ptr->next;
    }

    if (!result)
        throw std::length_error("No predecessor found.");

    return *result;
}


  template <typename Data>
  void SetLst<Data>::RemovePredecessor(const Data& elem) {
    Data predecessorElem = Predecessor(elem);
    Remove(predecessorElem);
  }
  
    template <typename Data>
  Data SetLst<Data>::PredecessorNRemove(const Data& elem) {
    Data predecessorElem = Predecessor(elem);
    Remove(predecessorElem);
    return predecessorElem;
  }
  

  /* ************************************************************************** */
 
//Successor
  template <typename Data>
  Data SetLst<Data>::Successor(const Data& elem) const {
    if (this->size < 2)
          throw std::length_error("Not enough elements for a successor.");
  
      typename List<Data>::Node* current = this->Head;
      const Data* successor = nullptr;
  
      while (current != nullptr) {
          if (current->element > elem) {
              if (successor == nullptr || current->element < *successor) {
                  successor = &(current->element);
              }
          }
          current = current->next;
      }
  
      if (successor == nullptr)
          throw std::length_error("No successor found (all elements are <= val).");
  
      return *successor;
  }
  

  template <typename Data>
  Data SetLst<Data>::SuccessorNRemove(const Data& elem) {
    Data successorElem = Successor(elem);
    Remove(successorElem);
    return successorElem;
  }
  
  
  template <typename Data>
  void SetLst<Data>::RemoveSuccessor(const Data& elem) {
    Data successorElem = Successor(elem);
    Remove(successorElem);
  }
  
//insert copy
template <typename Data>
bool SetLst<Data>::Insert(const Data& elem) {
    typename List<Data>::Node* node = new typename List<Data>::Node(elem);

    if (!this->Head) {
        this->Head = this->Tail = node;
        this->size = 1;
        return true;
    }

    typename List<Data>::Node* pred = nullptr;
    typename List<Data>::Node* curr = this->Head;

    while (curr && curr->element < elem) {
        pred = curr;
        curr = curr->next;
    }

    if (curr && curr->element == elem) {
        delete node;
        return false;
    }

    if (!pred) {
        node->next = this->Head;
        this->Head = node;
    } else {
        pred->next = node;
        node->next = curr;
        if (!curr) this->Tail = node;
    }

    ++this->size;
    return true;
}


  
  //Insert Move
template <typename Data>
bool SetLst<Data>::Insert(Data&& elem) {
    typename List<Data>::Node* newNode = new typename List<Data>::Node(std::move(elem));

    if (this->Head == nullptr) {
        this->Head = this->Tail = newNode;
        this->size = 1;
        return true;
    }

    typename List<Data>::Node* current = this->Head;
    typename List<Data>::Node* previous = nullptr;

    while (current != nullptr && current->element < newNode->element) {
        previous = current;
        current = current->next;
    }

    if (current != nullptr && current->element == newNode->element) {
        delete newNode;
        return false;
    }

    if (previous == nullptr) {
        newNode->next = this->Head;
        this->Head = newNode;
    } else if (current == nullptr) {
        previous->next = newNode;
        this->Tail = newNode;
    } else {
        previous->next = newNode;
        newNode->next = current;
    }

    this->size++;
    return true;
}

  
  
  //Remove
template <typename Data>
bool SetLst<Data>::Remove(const Data& elem) {
    if (this->Head == nullptr) {
        return false;
    }

    typename List<Data>::Node* current = this->Head;
    typename List<Data>::Node* previous = nullptr;

    while (current != nullptr && current->element != elem) {
        previous = current;
        current = current->next;
    }

    if (current == nullptr) {
        return false;
    }

    if (previous == nullptr) {
        this->Head = current->next;
        if (this->Head == nullptr) {
            this->Tail = nullptr;
        }
    } else {
        previous->next = current->next;
        if (current == this->Tail) {
            this->Tail = previous;
        }
    }

    typename List<Data>::Node* nodeToDelete = current;
    nodeToDelete->next = nullptr;
    current = nullptr;

    delete nodeToDelete;
    this->size--;

    return true;
}

  
//operator[]
template <typename Data>
const Data& SetLst<Data>::operator[](const unsigned long index) const {
    if (index >= this->size)
        throw std::out_of_range("Index out of range.");

    auto* ptr = this->Head;
    unsigned long pos = 0;

    while (pos < index) {
        ptr = ptr->next;
        ++pos;
    }

    return ptr->element;
}

  
  
//exists
template <typename Data>
bool SetLst<Data>::Exists(const Data& elem) const noexcept {
    typename List<Data>::Node* current = this->Head;

    while (current != nullptr) {
        if (current->element == elem) {
            return true;
        } else if (current->element > elem) {
            return false;
        }
        current = current->next;
    }

    return false;
}

//clear
  template <typename Data>
  void SetLst<Data>::Clear() noexcept {
      List<Data>::Clear(); 
  }
  
  
  /* ************************************************************************** */
  
  }
  

  

