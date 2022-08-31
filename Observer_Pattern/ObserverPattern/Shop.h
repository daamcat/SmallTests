#ifndef SHOP_H
#define SHOP_H

#include <string>

#include "Observer.h"

// Shop is concrete observer:
class Shop : public Observer
{
  // name of the shop:
  std::string m_name;
  float m_price;

public:
  Shop(std::string name);
  void update(float price) override;
};

#endif // SHOP_H
