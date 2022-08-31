#ifndef SUBJECT_H
#define SUBJECT_H

#include <vector>
#include <list>

#include "Observer.h"

// Keeps track of all observers and provides the facility to add or remove observers.
// Moreover, this class updates the observers with the last changes.
class Subject
{
  // Keep track of all shops we are observing:
  std::vector<Observer*> m_list;

public:
  void attach(Observer* observer);
  void detach(Observer* observer);
  void notify(float price);
};

#endif // SUBJECT_H
