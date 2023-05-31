#include <vector>

#pragma once



class Rmq_answerer {
  public:
    void init(std::vector<int> vec);
    Index rmq(Index start, Index end);



};