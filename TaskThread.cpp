
#include <unistd.h>
#include <algorithm>
#include <iostream>
#include "TaskThread.h"
#include "RandStr.h"


TaskThread::TaskThread(ITask * task) {
  task_ = task;
  running_ = false;
  thread_ = 0;
}

TaskThread::~TaskThread() {
  Stop();
}

void TaskThread::Run() {
  while( running_ ){
    task_->Execute();
  }
}

int TaskThread::Start() {
  running_ = true;
  if( 0 == pthread_create(&thread_, nullptr, TaskThread::ThreadFunc, this) ){
    return 0;
  }
  running_ = false;
  return -1;
}

void TaskThread::Stop() {
  if( running_ ){
    running_ = false;
    pthread_join(thread_, nullptr);
  }
}

void * TaskThread::ThreadFunc(void * arg) {
  TaskThread * pThis = (TaskThread*)arg;
  pThis->Run();
  return nullptr;
}



SerialTask::SerialTask() {
  count_ = 0;
  outputstr_ = false;
}

SerialTask::~SerialTask() {
}

void SerialTask::Execute() {
  std::string str = RandStr::GenerateRandomString();
//  queue_.Push(str);
//  str = queue_.Pop();
  std::sort(str.begin(), str.end());
  if(outputstr_){
    std::cout << str << std::endl;
  }
  count_ ++;
}

void SerialTask::SetOutputStr(bool output){
  outputstr_=output;
}

size_t SerialTask::GetExecuteCount() {
  return count_;
}


PushTask::PushTask(std::shared_ptr<Queue<std::string>> & queue){
  queue_ = queue;
  count_ = 0;
  outputstr_=false;
}

PushTask::~PushTask() {
}

void PushTask::Execute() {
  std::string str = RandStr::GenerateRandomString();
  queue_->Push(str);
  count_ ++;
}

void PushTask::SetOutputStr(bool output){
  outputstr_=output;
}

size_t PushTask::GetExecuteCount() {
  return count_;
}

PopTask::PopTask(std::shared_ptr<Queue<std::string>> & queue){
  queue_ = queue;
  count_ = 0;
  outputstr_=false;
}

PopTask::~PopTask() {
}

void PopTask::Execute() {
  if( queue_->Size() > 0 ){
    std::string str = queue_->Pop();
    std::sort(str.begin(), str.end());
    if(outputstr_){
      std::cout << str << std::endl;
    }
    count_ ++;
  }else
    sleep(0);
}

void PopTask::SetOutputStr(bool output){
  outputstr_=output;
}

size_t PopTask::GetExecuteCount() {
  return count_;
}

