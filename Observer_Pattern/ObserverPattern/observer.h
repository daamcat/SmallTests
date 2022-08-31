#ifndef OBSERVER_H
#define OBSERVER_H

class Observer
{
public:
  virtual void update(float price) = 0;
};


#endif // OBSERVER_H
