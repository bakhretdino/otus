#ifndef __ISUBSCRIBER__
#define __ISUBSCRIBER__

#include <string>

class ISubscriber {
public:
  virtual void notify(const std::string &data) = 0;
};

#endif /* __ISUBSCRIBER__ */
