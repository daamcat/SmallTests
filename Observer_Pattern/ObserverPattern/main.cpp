#include <QCoreApplication>

#include <iostream>

#include "Product.h"
#include "Shop.h"
#include "Supermarket.h"

// Ref: https://www.codeproject.com/Articles/328365/Understanding-and-Implementing-Observer-Pattern-2

int main(int argc, char *argv[])
{
  std::cout<<"Hi I am Damon"<<std::endl;

  // This is the product whose price changes:
  Product product;
  Supermarket super;

  // We have 2 shops. They want to keep updated with price changes by product owner:
  Shop shop1("Shop 1");
  Shop shop2("Shop 2");


  product.attach(&shop1);
  product.attach(&shop2);
  product.attach(&super);

  // Change the price of product:
  product.changePrice(23.0f);

  // Shop2 is not interested anymore in new prices. We unsubscribe it:
  product.detach(&shop2);

  // Change the price of product:
  product.changePrice(26.0f);

  return 0;
}
