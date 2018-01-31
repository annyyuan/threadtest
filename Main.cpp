#include <unistd.h>
#include <sys/select.h>
#include <sys/time.h>
#include <sys/types.h>
#include <string.h>
#include <iostream>
#include <string>
#include <algorithm>
#include <memory>
#include "RandStr.h"
#include "Queue.h"
#include "TaskThread.h"

static const std::string helpStr = "threadtest --parallel/--serial time(second) [--output]";

bool IsAllNum(char* str)
{
  for(unsigned int i=0;i<strlen(str);i++){
     char c = str[i];
     if(c>='0'&& c<='9')continue;
     else
        return false;
  }
  return true;
}

void SerialExecute(int seconds,bool output) {
  std::cout << "Serial Execute" << std::endl;
  ITask * task = new SerialTask();
  TaskThread * thread = new TaskThread(task);
  
  task->SetOutputStr(output);
  thread->Start();

  struct timeval tv;
  tv.tv_sec = seconds;
  tv.tv_usec = 0;
  select(0, NULL, NULL, NULL, &tv);
  thread->Stop();
  std::cout << "Serial Execute Count is " << task->GetExecuteCount() << std::endl;
  
  delete thread;
  delete task;
}

void ParallelExecute(int seconds,bool output) {
  std::cout << "Parallel Execute" << std::endl;
  std::shared_ptr<Queue<std::string>> queue; 
  queue.reset(new Queue<std::string>());
  ITask * push_task = new PushTask(queue);
  ITask * pop_task = new PopTask(queue);
  TaskThread * push_thread = new TaskThread(push_task);
  TaskThread * pop_thread = new TaskThread(pop_task);
  
  push_task->SetOutputStr(output);
  pop_task->SetOutputStr(output);
  push_thread->Start();
  pop_thread->Start();

  struct timeval tv;
  tv.tv_sec = seconds;
  tv.tv_usec = 0;
  select(0, NULL, NULL, NULL, &tv);

  push_thread->Stop();
  pop_thread->Stop();
  std::cout << "Parallel Execute Count is " << pop_task->GetExecuteCount() << std::endl;

  delete push_thread;
  delete pop_thread;
  delete push_task;
  delete pop_task;
}

int main(int argc, char ** argv) 
{
  if( argc < 3 && argc>4 ){
    std::cout << helpStr << std::endl;
    return -1;
  }
  bool output = false;
  if(!IsAllNum(argv[2])){
    std::cout<<"Invalid parameters"<<std::endl;
    return -1;
  }

  int seconds = atoi(argv[2]);
  if( seconds <= 0 ){
    std::cout << "Invalid parameters" << std::endl;
    return -1;
  }
  if(argc==4 && strcmp(argv[3],"--output")==0)
    output = true;

  if( strcmp(argv[1], "--serial") == 0 ){
    SerialExecute(seconds,output);   
  } else if( strcmp(argv[1], "--parallel") == 0 ){
    ParallelExecute(seconds,output);
  } else {
    std::cout << "Invalid parameters" << std::endl;
  }

  return 0;
}


