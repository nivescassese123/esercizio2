
namespace lasd {

  template <typename Data, typename Accumulator>
  using FoldFun = typename TraversableContainer<Data>::template FoldFun<Accumulator>;
  

  template <typename Data>
  template <typename Accumulator>
  inline Accumulator TraversableContainer<Data>::Fold(FoldFun<Accumulator> fun, Accumulator accumulator) const noexcept {
      Traverse(
          [fun, &accumulator](const Data & data) { 
              accumulator = fun(data, accumulator);
          }
      );
      return accumulator;
  } 
  

  template <typename Data>
  inline bool TraversableContainer<Data>::Exists(const Data &value) const noexcept {
      bool res = false;
      Traverse(
          [value, &res](const Data & data) {
              res |= (data == value); 
          }
      );
      return res; 
  }
  

    template <typename Data>
  template <typename Accumulator>
  inline Accumulator PostOrderTraversableContainer<Data>::PostOrderFold(FoldFun<Accumulator> func, Accumulator accumulator) const
    {
      PostOrderTraverse([&accumulator, &func](const Data &currData)
                        { accumulator = func(currData, accumulator); });
      return accumulator;
    };

    

  template <typename Data>
    template <typename Accumulator>
    inline Accumulator PreOrderTraversableContainer<Data>::PreOrderFold(FoldFun<Accumulator> func, Accumulator accumulator) const
    {
      PreOrderTraverse([&accumulator, func](const Data &currData)
                       { accumulator = func(currData, accumulator); });
      return accumulator;
    };

  
  
  }
  
