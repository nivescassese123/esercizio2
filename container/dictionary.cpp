namespace lasd {

  /* ************************************************************************** */
 
  template <typename Data>
  inline bool DictionaryContainer<Data>::InsertAll(const TraversableContainer<Data> &Tcon) {
    bool res = true;
    Tcon.Traverse([this, &res](const Data &currData) {
      res &= this->Insert(currData);
    });
    return res;
  }
  
  template <typename Data>
  inline bool DictionaryContainer<Data>::InsertAll(MappableContainer<Data> &&Mcon) {
    bool res = true;
    Mcon.Map([this, &res](const Data &currData) {
      res &= this->Insert(std::move(currData));
    });
    return res;
  }
  
  template <typename Data>
  inline bool DictionaryContainer<Data>::InsertSome(MappableContainer<Data> &&Mcon) {
    bool res = false;
    Mcon.Map([this, &res](const Data &currData) {
      res |= this->Insert(std::move(currData));
    });
    return res;
  }
  
  template <typename Data>
  inline bool DictionaryContainer<Data>::RemoveAll(const TraversableContainer<Data> &Tcon) {
    bool res = true;
    Tcon.Traverse([this, &res](const Data &currData) {
      res &= this->Remove(currData);
    });
    return res;
  }
  
  template <typename Data>
  inline bool DictionaryContainer<Data>::InsertSome(const TraversableContainer<Data> &Tcon) {
    bool res = false;
    Tcon.Traverse([this, &res](const Data &currData) {
      res |= this->Insert(currData);
    });
    return res;
  }

  template <typename Data>
  inline bool DictionaryContainer<Data>::RemoveSome(const TraversableContainer<Data> &Tcon) {
    bool res = false;
    Tcon.Traverse([this, &res](const Data &currData) {
      res |= this->Remove(currData);
    });
    return res;
  }
  
  /* ************************************************************************** */
  
  }
  