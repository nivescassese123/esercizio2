namespace lasd {

/* ************************************************************************** */
// Constructors
template <typename Data>
PQHeap<Data>::PQHeap(const TraversableContainer<Data>& container) : HeapVec<Data>(container) {
   this->Heapify();
}

template <typename Data>
PQHeap<Data>::PQHeap(const MappableContainer<Data>& container) : HeapVec<Data>(container) {
   this->Heapify();
}

template <typename Data>
PQHeap<Data>::PQHeap(const PQHeap<Data>& other) : HeapVec<Data>(other) { }

template <typename Data>
PQHeap<Data>::PQHeap(PQHeap<Data>&& other) noexcept : HeapVec<Data>(std::move(other)) { }

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

// Specific member Functions
template <typename Data>
const Data& PQHeap<Data>::Tip() const {
    if (this->Empty()) {
        throw std::length_error("Empty priority queue");
    }
    return elements[0];
}

template <typename Data>
void PQHeap<Data>::RemoveTip() {
    if (this->Empty()) {
        throw std::length_error("Empty priority queue");
    }

    elements[0] = std::move(elements[size - 1]);
    size--;

    if (!this->Empty()) {
        HeapifyDown(0);
    }
}

template <typename Data>
Data PQHeap<Data>::TipNRemove() {
    if (this->Empty()) {
        throw std::length_error("Empty priority queue");
    }

    Data tip = std::move(elements[0]);
    elements[0] = std::move(elements[size - 1]);
    size--;

    if (!this->Empty()) {
        HeapifyDown(0);
    }

    return tip;
}

template <typename Data>
void PQHeap<Data>::Insert(const Data& value) {
    Vector<Data>::Resize(size + 1);
    elements[size - 1] = value;
    HeapifyUp(size - 1);
}

template <typename Data>
void PQHeap<Data>::Insert(Data&& value) noexcept {
    Vector<Data>::Resize(size + 1);
    elements[size - 1] = std::move(value);
    HeapifyUp(size - 1);
}

template <typename Data>
void PQHeap<Data>::Change(unsigned long index, Data&& value) noexcept {
    if (index < size) {
        elements[index] = std::move(value);
        this->Heapify();
    }
    // Altrimenti non fa nulla (nessuna eccezione lanciata)
}


template <typename Data>
void PQHeap<Data>::Change(unsigned long index, const Data& value) {
    if (index >= size) {
        throw std::out_of_range("This Vector has not that many elements");
    }
    elements[index] = value;
    this->Heapify();
}

// Funzione ausiliaria per HeapifyUp (necessaria per Insert)
template <typename Data>
void PQHeap<Data>::HeapifyUp(unsigned long index) {
    if (index == 0) return;

    unsigned long parent = (index - 1) / 2;

    if (elements[index] > elements[parent]) {
        std::swap(elements[index], elements[parent]);
        HeapifyUp(parent);
    }
}

}
