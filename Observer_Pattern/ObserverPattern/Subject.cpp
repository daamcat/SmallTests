#include "Subject.h"

#include <algorithm>

void Subject::attach(Observer* observer)
{
  m_list.push_back(observer);
}
void Subject::detach(Observer* observer)
{
  m_list.erase(std::remove(m_list.begin(),m_list.end(),observer),m_list.end());
}
void Subject::notify(float price)
{
  for (auto observer : m_list)
  {
    observer->update(price);
  }
}
