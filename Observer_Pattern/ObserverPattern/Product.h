#ifndef PRODUCT_H
#define PRODUCT_H

#include "Subject.h"

// Product is concrete subject:
// We are interested in changes in this class. The observers want to know about the changes in this class:
class Product : public Subject
{
public:
  void changePrice(float price);
};

#endif // PRODUCT_H
