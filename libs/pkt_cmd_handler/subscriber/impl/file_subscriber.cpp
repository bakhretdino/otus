#include <file_subscriber.hpp>

#include <chrono>

FileSubscriber::FileSubscriber(std::string &&log_file_prefix,
                               std::string &&log_file_postfix)
    : log_file_prefix(std::move(log_file_prefix)),
      log_file_postfix(std::move(log_file_postfix)) {
  /* TODO generate rng and add before postfix */
  log_file.open(this->log_file_prefix + get_cur_epoch_time_str() +
                    this->log_file_postfix,
                std::ios::in | std::ios::out | std::ios::trunc);
  if (!log_file.is_open()) {
    throw std::runtime_error("Can't open log file\n");
  }
}

FileSubscriber::~FileSubscriber() {
  if (log_file.is_open()) {
    log_file.close();
  }
}

std::string FileSubscriber::get_cur_epoch_time_str() {
  using namespace std::chrono;
  auto cur_time = system_clock::now();
  auto cur_epoch = duration_cast<seconds>(cur_time.time_since_epoch());
  return std::to_string(cur_epoch.count());
}

void FileSubscriber::notify(const std::string &data) {
  log_file << data << std::endl;
}
