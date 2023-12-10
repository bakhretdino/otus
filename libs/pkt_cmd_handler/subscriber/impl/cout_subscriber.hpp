#ifndef __COUT_SUBSCRIBER__
#define __COUT_SUBSCRIBER__

#include <isubscriber.hpp>

class CoutSubscriber : public ISubscriber {
public:
  void notify(const std::string &data) override;
};

#endif /* __COUT_SUBSCRIBER__ */
