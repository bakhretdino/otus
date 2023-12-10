#ifndef __SUBSCRIBER_FACTORY__
#define __SUBSCRIBER_FACTORY__

#include <memory>

enum class eSubscriber;
class ISubscriber;

class SubscriberFactory {
public:
  static std::unique_ptr<ISubscriber> create(eSubscriber type);
};

#endif /* __SUBSCRIBER_FACTORY__ */
