
namespace lasd {

/* ************************************************************************** */
 // Default constructor




 // Specific constructors
template <typename Data>
HeapVec<Data>::HeapVec(const TraversableContainer<Data>& Tcon) : Vector<Data>(Tcon) {
    
     Heapify();
}

template <typename Data>
HeapVec<Data>::HeapVec(const MappableContainer<Data>& Mcon) : Vector<Data>(Mcon) {
      Heapify();
}

 // Copy constructor
template <typename Data>
HeapVec<Data>::HeapVec(const HeapVec<Data>& heap) : Vector<Data>(heap) {
    // Non serve chiamare Heapify() perché stiamo copiando da un heap già valido
}

 // Move constructor
template <typename Data>
HeapVec<Data>::HeapVec(HeapVec<Data>&& heap) noexcept : Vector<Data>(std::move(heap)) {
    // Non serve chiamare Heapify() perché stiamo spostando un heap già valido
}

 // Copy assignment
template <typename Data>
HeapVec<Data>& HeapVec<Data>::operator=(const HeapVec<Data>& heap) {
    SortableVector<Data>::operator=(heap);
    return *this;
}

 // Move assignment 
template <typename Data>
HeapVec<Data>& HeapVec<Data>::operator=(HeapVec<Data>&& heap) noexcept {
    SortableVector<Data>::operator=(std::move(heap));
    return *this;
}


// comparison operators
template <typename Data>
bool HeapVec<Data>::operator==(const HeapVec<Data>& other) const noexcept {
    if (size != other.size) {
        return false;
    }
    for (unsigned long i = 0; i < size; i++) {
        if (elements[i] != other.elements[i]) {
            return false;
        }
    }
    return true;
}

template <typename Data>
bool HeapVec<Data>::operator!=(const HeapVec<Data>& other) const noexcept {
    return !(*this == other);
}

// Specific member functions (inherited from Heap)
template <typename Data>
bool HeapVec<Data>::IsHeap() const noexcept {
    if (this->size <= 1) { // Un heap con 0 o 1 elemento è sempre un heap
        return true;
    }

    // Iteriamo solo sui nodi non-foglia
    // L'ultimo nodo non-foglia ha indice (this->size / 2) - 1
    for (unsigned long i = 0; i <= (this->size / 2) - 1; ++i) {
        // Puoi anche usare this->LeftChild(i) e this->RightChild(i) qui
        unsigned long left_child = (2 * i) + 1;
        unsigned long right_child = (2 * i) + 2;

        // Controlla il figlio sinistro: se esiste e il genitore è minore, non è un heap
        if (left_child < this->size && this->elements[i] < this->elements[left_child]) {
            return false;
        }

        // Controlla il figlio destro: se esiste e il genitore è minore, non è un heap
        if (right_child < this->size && this->elements[i] < this->elements[right_child]) {
            return false;
        }
    }
    return true; // Se nessun genitore è minore dei suoi figli, è un heap
}

template <typename Data>
void HeapVec<Data>::Heapify() {
    // Implementazione dell'algoritmo di heapify per max-heap
    if (size <= 1) return;
    
    // Partire dall'ultimo nodo interno e andare verso la radice
    for (long i = (size / 2) - 1; i >= 0; i--) {
        HeapifyDown(i);
    }
}

// Funzione ausiliaria per heapify down
//mi serve per mantenere la proprietà di max heap altrimenti ho violato l'heap e mi crusha il test di heap int
template <typename Data>
void HeapVec<Data>::HeapifyDown(unsigned long index) {
    unsigned long largest = index;
    unsigned long left = (2 * index) + 1;
    unsigned long right = (2 * index) + 2;

    if (left < size && elements[left] > elements[largest]) {
        largest = left;
    }
    if (right < size && elements[right] > elements[largest]) {
        largest = right;
    }

    if (largest != index) {
        std::swap(elements[index], elements[largest]);
        HeapifyDown(largest); // Ricorsione per continuare la heapify
    }
}

//heapifyup
template <typename Data>
void HeapVec<Data>::HeapifyUp(unsigned long index) {
    // Continua finché il nodo non è la radice (index > 0)
    // E il valore del nodo corrente è maggiore del valore del suo genitore (per un Max-Heap)
    while (index > 0 && this->elements[index] > this->elements[Parent(index)]) {
        unsigned long parent_index = Parent(index); // Ottieni l'indice del genitore
        std::swap(this->elements[index], this->elements[parent_index]); // Scambia
        index = parent_index; // Sposta l'indice corrente al genitore per continuare a salire
    }
}

// Sort() - HeapSort implementation
template <typename Data>
void HeapVec<Data>::Sort() noexcept {
    if (size <= 1) return;
    
    // Prima assicurati che sia un heap
    Heapify();
    
    // HeapSort: sposta il massimo alla fine e riduce la dimensione dell'heap
    for (unsigned long i = size - 1; i > 0; i--) {
        std::swap(elements[0], elements[i]);
        
        // Riaggiusta l'heap ridotto (da 0 a i-1)
        unsigned long current = 0;
        while (true) {
            unsigned long largest = current;
            unsigned long left = (2 * current) + 1;
            unsigned long right = (2 * current) + 2;
            
            if (left < i && elements[left] > elements[largest]) {
                largest = left;
            }
            if (right < i && elements[right] > elements[largest]) {
                largest = right;
            }
            
            if (largest == current) {
                break;
            }
            
            std::swap(elements[current], elements[largest]);
            current = largest;
        }
    }
}


/* ************************************************************************** */

}
