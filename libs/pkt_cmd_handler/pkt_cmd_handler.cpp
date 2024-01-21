#include <pkt_cmd_handler.hpp>

#include <chrono>
#include <iostream>

PktCmdHandler::PktCmdHandler(int pkt_size, std::string &&log_file_prefix,
                             std::string &&log_file_postfix,
                             std::string &&start_delim,
                             std::string &&stop_delim)
    : pkt_size(pkt_size), log_file_prefix(std::move(log_file_prefix)),
      log_file_postfix(std::move(log_file_postfix)),
      start_delim(std::move(start_delim)), stop_delim(std::move(stop_delim)) {}

PktCmdHandler::~PktCmdHandler() {
  if (cur_log_file.is_open()) {
    cur_log_file.close();
  }
}

std::string PktCmdHandler::get_cur_epoch_time_str() {
  using namespace std::chrono;
  auto cur_time = system_clock::now();
  auto cur_epoch = duration_cast<seconds>(cur_time.time_since_epoch());
  return std::to_string(cur_epoch.count());
}

void PktCmdHandler::print_block() {
  std::string line;
  std::string resp_prefix = "bulk: ";
  std::string resp;
  resp += resp_prefix;
  cur_log_file.seekg(0, std::ios::beg);
  while (std::getline(cur_log_file, line)) {
    resp += (resp.size() > resp_prefix.size() ? ", " : "") + line;
  }
  std::cout << resp << std::endl;
}

void PktCmdHandler::entry() {
  std::string cmd;
  if (std::cin >> cmd) {
    if (cmd == start_delim) {
      recv_start_delim_cnt++;
    } else if (cmd != stop_delim) {
      cur_log_file = std::fstream(
          log_file_prefix + get_cur_epoch_time_str() + log_file_postfix,
          std::ios::in | std::ios::out | std::ios::trunc);
      if (!cur_log_file.is_open()) {
        throw std::runtime_error("Can't open log file\n");
      }
      cur_log_file << cmd << std::endl;
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
      cur_log_file << cmd << std::endl;
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
      cur_log_file << cmd << std::endl;
    }
  } else {
    state = State::Finish;
  }
}

void PktCmdHandler::finish() {
  if (cur_log_file.is_open() && (recv_start_delim_cnt == 0)) {
    print_block();
    recv_cmd_cnt = 0;
  }
}

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
