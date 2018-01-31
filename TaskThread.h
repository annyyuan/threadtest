
#pragma once

#include <pthread.h>
#include <memory>
#include <string>
#include "Queue.h"


class ITask {
public:
  virtual ~ITask() {}
  virtual void Execute() = 0;
  virtual size_t GetExecuteCount() = 0;
  virtual void SetOutputStr(bool output) = 0;
};

class TaskThread {
public:
  TaskThread(ITask * task);
  virtual ~TaskThread();

  static void * ThreadFunc(void * arg);

  int Start();
  void Stop();

protected:
  virtual void Run();

private:
  ITask  * task_;
  bool     running_;
  pthread_t   thread_;
};


class SerialTask : public ITask {
public:
  SerialTask();
  virtual ~SerialTask();

  virtual void Execute() override;
  virtual size_t GetExecuteCount() override;
  virtual void SetOutputStr(bool output) override;

private:
  size_t  count_;
  Queue<std::string> queue_;
  bool outputstr_;
};

class PushTask : public ITask {
public:
  PushTask(std::shared_ptr<Queue<std::string>> & queue);
  virtual ~PushTask();

  virtual void Execute() override;
  virtual size_t GetExecuteCount() override;
  virtual void SetOutputStr(bool output)override;

private:
  size_t count_;
  std::shared_ptr<Queue<std::string>> queue_;
  bool outputstr_;
};

class PopTask : public ITask {
public:
  PopTask(std::shared_ptr<Queue<std::string>> & queue);
  virtual ~PopTask();

  virtual void Execute() override;
  virtual size_t GetExecuteCount() override;
  virtual void SetOutputStr(bool output) override;

private:
  size_t count_;
  std::shared_ptr<Queue<std::string>>  queue_;
  bool outputstr_;
};



