namespace lasd {

  /* ************************************************************************** */
  
  template<typename Data>
  List<Data>::Node::Node(Data && dat)noexcept{
      std::swap(element , dat);
  }
  
  
  template<typename Data>
  List<Data>::Node::~Node() { delete next; }
 

  template<typename Data>
  List<Data>::Node::Node(Node && nod)noexcept{
  std::swap(element,nod.element);
  std::swap(next,nod.next);
  
  }
  

  template <typename Data>
  inline bool List<Data>::Node::operator==(const Node &var) const noexcept {
    return element == var.element;
  }
  
  
  template <typename Data>
  inline bool List<Data>::Node::operator!=(const Node &var) const noexcept {
    return !((*this) == var);
  }
  

  template <typename Data>
  typename List<Data>::Node * List<Data>::Node::Clone(Node * Tail){
    if(next == nullptr){
      return Tail;
    }else{
      Node * node = new Node(element);
      this->next = next->Clone(Tail);
  
      return node;
    }
  }
  


  template <typename Data>
  List<Data>::List(const TraversableContainer<Data> &con) {
    con.Traverse([this](const Data &currData) { InsertAtBack(currData); });
  }
  
 

  template <typename Data> List<Data>::List(MappableContainer<Data> &&con) {
    con.Map([this](Data &currData) { InsertAtBack(std::move(currData)); });
  }
  
  
 
  template <typename Data> List<Data>::List(const List<Data> &l) {
    if (!(size = l.size))
      return;
  
    Head = new Node(*(l.Head));
    Tail = Head;
  
    Node *temp = l.Head->next;
  
    while (temp) {
      Tail->next = new Node(*temp);
      Tail = Tail->next;
      temp = temp->next;
    }
  }
  
  
  template <typename Data>
  List<Data>::List(List && l) noexcept {
    std::swap(size, l.size);
    std::swap(Head, l.Head);
    std::swap(Tail, l.Tail);
  }
  

  template <typename Data> List<Data>::~List() {
    delete Head;
    Head = Tail = nullptr;
    size = 0;
  }
  

  template <typename Data>
  List<Data> &List<Data>::operator=(const List<Data> &l) {
  
    if (!l.size) {
      Clear();
      return *this;
    }
  
    if (!size) {
      List<Data> temp{l};
      std::swap(temp, *this);
      return *this;
    }
  
    Node *wl{l.Head};
    Tail = Head;
  
    Tail->element = wl->element;
  
    while (Tail->next && wl->next) {
      Tail = Tail->next;
      wl = wl->next;
  
      Tail->element = wl->element;
    }
  
    if (Tail->next) {
      delete Tail->next;
      Tail->next = nullptr;
    } else
      for (wl = wl->next; wl; wl = wl->next) {
        InsertAtBack(wl->element);
      }
    size = l.size;
    return *this;
  }



  template <typename Data>
  List<Data> &List<Data>::operator=(List<Data> &&l) noexcept {
    std::swap(size, l.size);
    std::swap(Head, l.Head);
    std::swap(Tail, l.Tail);
    return *this;
  }
  


  template <typename Data>
  inline bool List<Data>::operator==(const List<Data> &l) const noexcept {
    if (size != l.size)
      return false;
  
    Node *temp = Head, *temp2 = l.Head;
  
    while (temp != nullptr) {
      if (temp->element != temp2->element)
        return false;
      temp = temp->next;
      temp2 = temp2->next;
    }
    return true;
  }
  
  

  template <typename Data>
  inline bool List<Data>::operator!=(const List<Data> &l) const noexcept {
    return !(*this == l);
  }
  
 

  template <typename Data> void List<Data>::InsertAtFront(const Data &dat) {
    Node *temp = new Node(dat);
    temp->next = Head;
    Head = temp;
    if (Tail == nullptr)
      Tail = Head;
    ++size;
  }
  
  
  
  template <typename Data> void List<Data>::InsertAtFront(Data &&d) {
    Node *temp = new Node(std::move(d));
    temp->next = Head;
    Head = temp;
    if (Tail == nullptr)
      Tail = Head;
    ++size;
  }
  
 

  template <typename Data> void List<Data>::RemoveFromFront() {
    if (!Head)
      throw std::length_error("Cannot remove from an empty list");
    
    Node *temp{Head};
    if (Head == Tail) {
      Head = Tail = nullptr;
    } else {
      Head = Head->next;
    }
    temp->next = nullptr;
    delete temp;
    --size;
  }

  
  template <typename Data> void List<Data>::InsertAtBack(const Data &dat) {
    Node *temp{new Node(dat)};
    size++ ? Tail->next = temp : Head = Tail = temp;
    Tail = temp;
  }
  
 template <typename Data> Data List<Data>::FrontNRemove() {
    if (!size)
      throw std::length_error("Cannot remove from Empty list");
    Node *temp{Head};
    Head == Tail ? Head = Tail = nullptr : Head = Head->next;
    temp->next = nullptr;
    Data d{std::move(temp->element)};
    delete temp;
    --size;
    return d;
  }
  


  template <typename Data> void List<Data>::InsertAtBack(Data &&dat) {
    Node *temp{new Node(std::move(dat))};
    size++ ? Tail->next = temp : Head = Tail = temp;
    Tail = temp;
  }
  
  

  template <typename Data>
  Data List<Data>::BackNRemove() {
    if (!size)
      throw std::length_error("Cannot remove from Empty list");
  
    Data dat;
  
    if (Head == Tail) {
      dat = std::move(Head->element);
      delete Head;
      Head = Tail = nullptr;
    } else {
      Node* prev = Head;
      while (prev->next != Tail) {
        prev = prev->next;
      }
  
      dat = std::move(Tail->element);
      delete Tail;
      Tail = prev;
      Tail->next = nullptr;
    }
  
    --size;
    return dat;
  }
  
  
  template <typename Data>
  void List<Data>::RemoveFromBack() {
    if (!Head)
      throw std::length_error("Cannot remove from an empty list");
  
    if (Head == Tail) {
      delete Head;
      Head = Tail = nullptr;
    } else {
      Node* current = Head;
      while (current->next != Tail) {
        current = current->next;
      }
      delete Tail;
      Tail = current;
      Tail->next = nullptr;
    }
    --size;
  }

  template <typename Data>
  inline Data &List<Data>::operator[](unsigned long ind) {
    if (ind >= size)
      throw std::length_error("List does not have enough elements");
  
    Node *temp{Head};
    for (unsigned int i{0}; i < ind; ++i, temp = temp->next)
      ;
    return temp->element;
  }
  
  

  template <typename Data> inline Data &List<Data>::Front() {
    if (size)
      return Head->element;
    throw std::length_error("Empty List");
  }
  
  

  template <typename Data> inline Data &List<Data>::Back() {
    if (size)
      return Tail->element;
    throw std::length_error("Empty List");
  }
  
  

  template <typename Data> inline const Data &List<Data>::Front() const {
    if (size)
      return Head->element;
    throw std::length_error("Empty List");
  }
  
    template <typename Data>
  inline const Data &List<Data>::operator[](unsigned long ind) const {
    if (ind >= size)
      throw std::length_error("List does not have enough elements");
  
    Node *temp{Head};
    for (unsigned int i{0}; i < ind; ++i, temp = temp->next)
      ;
    return temp->element;
  }
  
  
  
  template <typename Data> inline const Data &List<Data>::Back() const {
    if (size)
      return Tail->element;
    throw std::length_error("Empty List");
  }
  
  

  template <typename Data> void List<Data>::Clear() noexcept{
    delete Head;
    Head = Tail = nullptr;
    size = 0;
  }
  

  

  template <typename Data>
  void List<Data>::PreOrderTraverse(TraverseFun fun, Node *curr) const {
    if (!curr)
      return;
  
    fun(curr->element);
    PreOrderTraverse(fun, curr->next);
  }
  
  
  template <typename Data>
  void List<Data>::PostOrderTraverse(TraverseFun fun, Node *curr) const {
    if (!curr)
      return;
    PostOrderTraverse(fun, curr->next);
    fun(curr->element);
  }
  

  template <typename Data>
  void List<Data>::PreOrderMap(MapFun fun, Node *curr) const {
    if (!curr)
      return;
    fun(curr->element);
    PreOrderMap(fun, curr->next);
  }
  

  template <typename Data>
  void List<Data>::PostOrderMap(MapFun fun, Node *curr) const {
    if (!curr)
      return;
    PostOrderMap(fun, curr->next);
    fun(curr->element);
  }
  
  
  }
  
  