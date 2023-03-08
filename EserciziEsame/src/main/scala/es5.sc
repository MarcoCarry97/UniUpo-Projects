val orderedInsert:(List[Int],Int)=>List[Int]=(list,value)=>
  {
    list.takeWhile(value>_) ::: (value::list.dropWhile(value>_))
  }

orderedInsert(List(1,2,4),3)
orderedInsert(List(1,2,4),0)
orderedInsert(List(1,2,4),5)
orderedInsert(orderedInsert(orderedInsert(List(),4),5),0)