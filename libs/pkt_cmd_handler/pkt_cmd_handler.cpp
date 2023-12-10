#include <esubscriber.hpp>
#include <pkt_cmd_handler.hpp>
#include <subscriber_factory.hpp>

#include <algorithm>
#include <chrono>
#include <iostream>
#include <numeric>

PktCmdHandler::PktCmdHandler(int pkt_size, std::string &&start_delim,
                             std::string &&stop_delim)
    : pkt_size(pkt_size), start_delim(std::move(start_delim)),
      stop_delim(std::move(stop_delim)) {}

void PktCmdHandler::add_subscriber(std::unique_ptr<ISubscriber> sub) {
  subs.push_back(std::move(sub));
}

void PktCmdHandler::remove_subscriber(std::unique_ptr<ISubscriber> sub) {
  auto it = std::remove_if(subs.begin(), subs.end(),
                           [sub_ptr = sub.get()](const auto &subscriber) {
                             return subscriber.get() == sub_ptr;
                           });

  subs.erase(it, subs.end());
}

void PktCmdHandler::print_block() {
  std::string line;
  std::string resp = "bulk: ";
  resp += std::accumulate(
      cmd_pkt.begin(), cmd_pkt.end(), std::string(),
      [](const std::string &a, const std::string &b) -> std::string {
        return a.empty() ? b : a + ", " + b;
      });

  for (auto it = subs.begin(); it != subs.end();) {
    auto &sub = *it;
    sub->notify(resp);
    it = subs.erase(it);
  }
  std::cout << resp << std::endl;
  cmd_pkt.clear();
}

void PktCmdHandler::entry() {
  std::string cmd;
  if (std::cin >> cmd) {
    if (cmd == start_delim) {
      recv_start_delim_cnt++;
    } else if (cmd != stop_delim) {
      /* Register a file subscriber */
      add_subscriber(SubscriberFactory::create(eSubscriber::File));
      cmd_pkt.push_back(cmd);
      recv_cmd_cnt++;

      if (recv_start_delim_cnt > 0) {
        state = State::DynamicBlock;
      } else if (recv_cmd_cnt == pkt_size) {
        print_block();
        recv_cmd_cnt = 0;
      } else {
        state = State::Ordinary;
      }
    }
  } else {
    state = State::Finish;
  }
}

void PktCmdHandler::ordinary_block() {
  std::string cmd;
  if (std::cin >> cmd) {
    if (cmd == start_delim) {
      recv_start_delim_cnt++;
      if (recv_start_delim_cnt == 1) {
        print_block();
        recv_cmd_cnt = 0;
      }
      state = State::Entry;
    } else if (cmd != stop_delim) {
      recv_cmd_cnt++;
      cmd_pkt.push_back(cmd);
      if (recv_cmd_cnt == pkt_size) {
        print_block();
        recv_cmd_cnt = 0;
        state = State::Entry;
      }
    }
  } else {
    state = State::Finish;
  }
}

void PktCmdHandler::dynamic_block() {
  std::string cmd;
  if (std::cin >> cmd) {
    if (cmd == start_delim) {
      recv_start_delim_cnt++;
    } else if (cmd == stop_delim) {
      recv_stop_delim_cnt++;
      if (recv_start_delim_cnt == recv_stop_delim_cnt) {
        recv_start_delim_cnt = 0;
        recv_stop_delim_cnt = 0;
        print_block();
        recv_cmd_cnt = 0;
        state = State::Entry;
      }
    } else {
      recv_cmd_cnt++;
      cmd_pkt.push_back(cmd);
    }
  } else {
    state = State::Finish;
  }
}

void PktCmdHandler::finish() {
  if (recv_start_delim_cnt == 0) {
    print_block();
    recv_cmd_cnt = 0;
  }
}

void PktCmdHandler::run() { loop(); }

void PktCmdHandler::loop() {
  while (1) {
    switch (state) {
    case State::Entry: {
      entry();
    } break;
    case State::Ordinary: {
      ordinary_block();
    } break;
    case State::DynamicBlock: {
      dynamic_block();
    } break;
    case State::Finish: {
      finish();
      return;
    } break;
    }
  }
}
