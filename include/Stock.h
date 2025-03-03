#ifndef STOCK_H_
#define STOCK_H_

#include "Depot.h"
#include "Card.h"
#include <vector>
#include <memory>
class Stock: public Depot{
protected:
private:
   std::vector<std::unique_ptr<Card>> _pile;
public:
   Stock();
   
};
#endif
