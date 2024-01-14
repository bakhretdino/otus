#include <pkt_cmd_handler.hpp>

#include <algorithm>
#include <chrono>
#include <iostream>
#include <numeric>
#include <sstream>
#include <thread>

PktCmdHandler::PktCmdHandler(
    int pkt_size, TaskQueue<std::string> &log_queue,
    TaskQueue<std::pair<std::string, std::string>> &file_queue,
    std::string &&start_delim, std::string &&stop_delim)
    : pkt_size(pkt_size), log_queue(log_queue), file_queue(file_queue),
      start_delim(std::move(start_delim)), stop_delim(std::move(stop_delim)) {}

void PktCmdHandler::print_block() {
  std::string resp = "bulk: ";
  resp += std::accumulate(
      cmd_pkt.begin(), cmd_pkt.end(), std::string(),
      [](const std::string &a, const std::string &b) -> std::string {
        return a.empty() ? b : a + ", " + b;
      });
  file_queue.add(std::make_pair(file_timestamp, resp));
  log_queue.add(resp);
  cmd_pkt.clear();
}

std::string PktCmdHandler::get_cur_epoch_time_str() {
  using namespace std::chrono;
  auto cur_time = system_clock::now();
  auto cur_epoch = duration_cast<seconds>(cur_time.time_since_epoch());
  return std::to_string(cur_epoch.count());
}

void PktCmdHandler::entry(const std::string &cmd) {
  if (cmd == start_delim) {
    recv_start_delim_cnt++;
  } else if (cmd != stop_delim) {
    file_timestamp = get_cur_epoch_time_str();
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
}

void PktCmdHandler::ordinary_block(const std::string &cmd) {
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
}

void PktCmdHandler::dynamic_block(const std::string &cmd) {
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
}

void PktCmdHandler::finish() {
  if (recv_start_delim_cnt == 0) {
    print_block();
    recv_cmd_cnt = 0;
  }
}

void PktCmdHandler::run(std::string data) {
  std::string input_data(data);
  std::istringstream iss(input_data);
  std::string cmd;
  while (iss >> cmd) {
    switch (state) {
    case State::Entry: {
      entry(cmd);
      break;
    }
    case State::Ordinary: {
      ordinary_block(cmd);
      break;
    }
    case State::DynamicBlock: {
      dynamic_block(cmd);
      break;
    }
    case State::Finish: {
      finish();
      return;
    }
    }
  }
}
