#include "Shop.h"
#include <iostream>

Shop::Shop(std::string name) : m_name(name)
{}

void Shop::update(float price)
{
  m_price = price;
  std::cout<< "Price at "<<m_name<<" is now "<<m_price<<std::endl;
}
