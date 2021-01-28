#include "gw_micro_service/micro_service/interrupt_handler.h"

#include <iostream>

#include <signal.h>

namespace gw_micro_service
{
  namespace micro_service
  {
    std::mutex InterruptHandler::mutex_;
    std::condition_variable InterruptHandler::condition_;

    void InterruptHandler::hook_SIGINT()
    {
      signal(SIGINT, InterruptHandler::handle_user_interrupt);        
    }

    void InterruptHandler::handle_user_interrupt(int signal)
    {
      if (signal == SIGINT) {
        std::cout << "SIGINT trapped ..." << '\n';
        condition_.notify_one();
      }
    }

    void InterruptHandler::wait_for_user_interrupt()
    {
      std::unique_lock<std::mutex> lock { mutex_ };
      condition_.wait(lock);
      std::cout << "user has signaled to interrup program..." << '\n';
      lock.unlock();
    }
  }
}
