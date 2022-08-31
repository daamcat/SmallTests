#ifndef SUPERMARKET_H
#define SUPERMARKET_H

#include "Observer.h"

class Supermarket : public Observer
{
public:
  Supermarket();


  void update(float price) override;
};

#endif // SUPERMARKET_H
