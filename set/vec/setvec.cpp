
#include <limits>
#include "setvec.hpp"

namespace lasd {

/* ************************************************************************** */



template <typename Data>
SetVec<Data>::SetVec(MappableContainer<Data>&& Mcon) {
    Mcon.Traverse([this](const Data& elem) {
        if (!Exists(elem)) {
            Insert(elem);
        }
    });
}


template <typename Data>
SetVec<Data>::SetVec(const TraversableContainer<Data>& Tcon) {
    Tcon.Traverse([this](const Data& elem) {
        if (!Exists(elem)) {
            Insert(elem);
        }
    });
}


template <typename Data>
SetVec<Data>::SetVec(const SetVec<Data>& other) {
    for (unsigned long i = 0; i < other.Size(); ++i) {
        Insert(other[i]);  
    }
}


template <typename Data>
SetVec<Data>::SetVec(SetVec<Data>&& Setvec) {
    elements = Setvec.elements;
    size = Setvec.size;

    Setvec.Clear();
    
}


template <typename Data>
SetVec<Data>::~SetVec() {
  Clear();  
}



template <typename Data>
SetVec<Data>& SetVec<Data>::operator=(const SetVec<Data>& other) {
    if (this != &other) {
        Clear();
        for (unsigned long i = 0; i < other.Size(); ++i) {
            Insert(other[i]);
        }
    }
    return *this;
}




template <typename Data>
SetVec<Data>& SetVec<Data>::operator=(SetVec<Data>&& other) noexcept {
    if (this != &other) {  
        Clear();
        elements = std::move(other.elements);  
        size = other.size;  
        other.Clear();  
    }
    return *this;
}




template <typename Data>
bool SetVec<Data>::operator==(const SetVec<Data>& other) const noexcept {
    if (size != other.size) {
        return false;
    }
    for (unsigned long i = 0; i < size; ++i) {
        if (elements[i] != other.elements[i]) {
            return false;
        }
    }
    
    return true;

}




template <typename Data>
bool SetVec<Data>::operator!=(const SetVec<Data>& other) const noexcept {
    return !(*this == other);
}



/* ************************************************************************ */
template <typename Data>
Data SetVec<Data>::Min() const {
    if (size == 0) {
        throw std::length_error("SetVec is empty");
    }
    return elements[0];
}


template <typename Data>
Data SetVec<Data>::MinNRemove() {
    Data val = Min();
    Remove(val);
    return val;
}


template <typename Data>
void SetVec<Data>::RemoveMin() {
    if (size == 0) {
        throw std::length_error("SetVec is empty");
    }
    Remove(elements[0]);
}



/* ************************************************************************ */
template <typename Data>
Data SetVec<Data>::Max() const {
    if (size == 0) {
        throw std::length_error("SetVec is empty");
    }
    return elements[size - 1];
}


template <typename Data>
Data SetVec<Data>::MaxNRemove() {
    Data val = Max();
    Remove(val);
    return val;
}

template <typename Data>
void SetVec<Data>::RemoveMax() {
    if (size == 0) {
        throw std::length_error("SetVec is empty");
    }
    Remove(elements[size - 1]);
}

/* ************************************************************************ */

template <typename Data>
Data SetVec<Data>::Predecessor(const Data& val) const {
    if (size == 0) throw std::length_error("Empty container");

    long idx = -1;
    for (unsigned long i = 0; i < size && elements[i] < val; ++i) {
        idx = i;
    }

    if (idx == -1) throw std::length_error("No predecessor");

    return elements[idx];
}




template <typename Data>
Data SetVec<Data>::PredecessorNRemove(const Data& val) {
    if (size < 2) throw std::length_error("Too few elements");

    unsigned long i = 0;
    while (i < size && elements[i] < val) ++i;

    if (i == 0) throw std::length_error("No predecessor");

    Data pred = elements[i - 1];
    Remove(pred);
    return pred;
}


template <typename Data>
void SetVec<Data>::RemovePredecessor(const Data& val) {
    if (size < 2) throw std::length_error("Too few elements");

    unsigned long i = 0;
    while (i < size && elements[i] < val) ++i;

    if (i == 0) throw std::length_error("No predecessor");

    Remove(elements[i - 1]);
}


/* ************************************************************************ */


template <typename Data>
Data SetVec<Data>::Successor(const Data& val) const {
    if (size < 2) throw std::length_error("Too few elements");

    for (unsigned long i = 0; i < size; ++i) {
        if (elements[i] > val) return elements[i];
    }

    throw std::length_error("No successor");
}




template <typename Data>
Data SetVec<Data>::SuccessorNRemove(const Data& value) {
    Data successor = Successor(value);
    Remove(successor);
    return successor;
}




template <typename Data>
void SetVec<Data>::RemoveSuccessor(const Data& value) {
    Data successor=Successor(value);
    Remove(successor);
}



/* ************************************************************************ */


template <typename Data>
bool SetVec<Data>::Insert(const Data& val) {
    if (Exists(val)) return false;

    Resize(++size);

    unsigned long i = 0;
    while (i < size - 1 && elements[i] < val) ++i;

    for (auto j = size - 1; j > i; --j) {
        elements[j] = std::move(elements[j - 1]);
    }

    elements[i] = val;
    return true;
}



template <typename Data>
bool SetVec<Data>::Insert(Data&& val) {
    if (Exists(val)) return false;

    Resize(++size);

    unsigned long i = 0;
    while (i < size - 1 && elements[i] < val) ++i;

    for (unsigned long j = size - 1; j > i; --j) {
        elements[j] = std::move(elements[j - 1]);
    }

    elements[i] = std::move(val);
    return true;
}




template <typename Data>
bool SetVec<Data>::Remove(const Data& val) {
    unsigned long i = 0;
    while (i < size && elements[i] != val) ++i;

    if (i == size) return false;

    for (; i < size - 1; ++i) {
        elements[i] = std::move(elements[i + 1]);
    }

    Resize(size - 1);
    return true;
}



/* ************************************************************************ */


template <typename Data>
const Data& SetVec<Data>::operator[](unsigned long index) const {
    if (index >= size) {
        throw std::out_of_range("Index out of range");
    }
    return elements[index];
}



/* ************************************************************************** */


template <typename Data>
bool SetVec<Data>::Exists(const Data& val) const noexcept {
    for (unsigned long i = 0; i < size; ++i) {
        if (elements[i] == val) {
            return true;
        }
    }
    return false;
}


/* ************************************************************************ */


template <typename Data>
void SetVec<Data>::Clear() {
    elements.Clear();
    size = 0;
}


  

//Auxilary function
/* ************************************************************************** */

//FindIndexHelper
template <typename Data>
long SetVec<Data>::FindIndexHelper(const Data& val) const {
    for (unsigned long i = 0; i < size; ++i) {
        if (elements[i] == val) {
            return i;
        }
    }
    return -1;
}

//FindIndex
template <typename Data>
long SetVec<Data>::FindIndex(const Data& val) const {
    long index = FindIndexHelper(val);
    return index;
}

template <typename Data>
void lasd::SetVec<Data>::Resize(unsigned long newSize) {
    elements.Resize(newSize);
    size = newSize;
}



}