#include <esubscriber.hpp>
#include <isubscriber.hpp>
#include <subscriber_factory.hpp>
#include <subscribers.hpp>

std::unique_ptr<ISubscriber> SubscriberFactory::create(eSubscriber type) {
  std::unique_ptr<ISubscriber> subscriber;

  switch (type) {
  case eSubscriber::File: {
    subscriber = std::make_unique<FileSubscriber>();
  } break;
  case eSubscriber::Cout: {
    subscriber = std::make_unique<CoutSubscriber>();
  } break;
  default:
    throw std::runtime_error("Unsupported subscriber type");
  }

  return subscriber;
}
