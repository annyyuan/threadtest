
#pragma once

#include <list>
#include <mutex>
#include <thread>

template <typename T>
class Queue {
public:
  Queue(){}
  virtual ~Queue() {}

  void Push(T & obj) {
    std::lock_guard<std::mutex> lock(mutex_);
    list_.push_back(obj);
  }

  T Pop() {
    std::lock_guard<std::mutex> lock(mutex_);
    T obj = list_.front();
    list_.pop_front();
    return obj;
  }

  size_t Size() {
//    std::lock_guard<std::mutex> lock(mutex_);
    return list_.size();
  }

private:
  std::mutex  mutex_;
  std::list<T>   list_;
};

