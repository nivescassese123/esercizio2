namespace lasd {

/* ************************************************************************** */

// Constructors

template <typename Data>
PQHeap<Data>::PQHeap(const TraversableContainer<Data>& container)
  : HeapVec<Data>(container) {
  this->Heapify();
}

template <typename Data>
PQHeap<Data>::PQHeap(const MappableContainer<Data>& container)
  : HeapVec<Data>(container) {
  this->Heapify();
}

template <typename Data>
PQHeap<Data>::PQHeap(const PQHeap<Data>& other)
  : HeapVec<Data>(other) { }

template <typename Data>
PQHeap<Data>::PQHeap(PQHeap<Data>&& other) noexcept
  : HeapVec<Data>(std::move(other)) { }

// Assignment operators

template <typename Data>
PQHeap<Data>& PQHeap<Data>::operator=(const PQHeap<Data>& other) {
  HeapVec<Data>::operator=(other);
  return *this;
}

template <typename Data>
PQHeap<Data>& PQHeap<Data>::operator=(PQHeap<Data>&& other) noexcept {
  HeapVec<Data>::operator=(std::move(other));
  return *this;
}

/* ************************************************************************** */

// Specific member functions

template <typename Data>
const Data& PQHeap<Data>::Tip() const {
  if (this->Empty()) {
    throw std::length_error("Tip: Empty priority queue");
  }
  return this->elements[0];
}

template <typename Data>
void PQHeap<Data>::RemoveTip() {
  if (this->Empty()) {
    throw std::length_error("RemoveTip: Empty priority queue");
  }

  this->elements[0] = std::move(this->elements[this->size - 1]);
  this->size--;

  if (!this->Empty()) {
    this->HeapifyDown(0);
  }
}

template <typename Data>
Data PQHeap<Data>::TipNRemove() {
  if (this->Empty()) {
    throw std::length_error("TipNRemove: Empty priority queue");
  }

  Data tip = std::move(this->elements[0]);
  this->elements[0] = std::move(this->elements[this->size - 1]);
  this->size--;

  if (!this->Empty()) {
    this->HeapifyDown(0);
  }

  return tip;
}

template <typename Data>
void PQHeap<Data>::Insert(const Data& value) {
  lasd::Vector<Data>::Resize(this->size + 1);
  this->elements[this->size - 1] = value;
  HeapifyUp(this->size - 1);
}

template <typename Data>
void PQHeap<Data>::Insert(Data&& value) noexcept {
  lasd::Vector<Data>::Resize(this->size + 1);
  this->elements[this->size - 1] = std::move(value);
  HeapifyUp(this->size - 1);
}

template <typename Data>
void PQHeap<Data>::Change(unsigned long index, const Data& value) {
  if (index >= this->size) {
    throw std::out_of_range("Change (copy): Index out of range");
  }
  this->elements[index] = value;
  this->Heapify();
}

template <typename Data>
void PQHeap<Data>::Change(unsigned long index, Data&& value) noexcept {
  if (index >= this->size) {
    // Per coerenza con la versione const: ignora oppure logga
    return;
  }
  this->elements[index] = std::move(value);
  this->Heapify();
}

/* ************************************************************************** */

// Auxiliary function: HeapifyUp

template <typename Data>
void PQHeap<Data>::HeapifyUp(unsigned long index) {
  while (index > 0) {
    unsigned long parent = (index - 1) / 2;
    if (this->elements[index] > this->elements[parent]) {
      std::swap(this->elements[index], this->elements[parent]);
      index = parent;
    } else {
      break;
    }
  }
}

}
