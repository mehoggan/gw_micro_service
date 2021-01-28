#ifndef GW_MICRO_SERVICE_MICRO_SERVICE_USR_INTERRUPT_HANDLER_H_INCLUDED
#define GW_MICRO_SERVICE_MICRO_SERVICE_USR_INTERRUPT_HANDLER_H_INCLUDED

#include <condition_variable>
#include <mutex>

namespace gw_micro_service
{
  namespace micro_service
  {
    class InterruptHandler
    {
    public:
      static void hook_SIGINT();

      static void handle_user_interrupt(int signal);

      static void wait_for_user_interrupt();

    private:
      static std::condition_variable condition_;

      static std::mutex mutex_;
    };
  }
}

#endif
