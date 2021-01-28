#include "gw_micro_service/micro_service/runtime_utils.h"

namespace gw_micro_service
{
  namespace micro_service
  {
    void RuntimeUtils::print_stack_trace()
    {
      const int MAX_CALLSTACK = 100;
      void * callstack[MAX_CALLSTACK];
      int frames;
      frames = backtrace(callstack, MAX_CALLSTACK);
      backtrace_symbols_fd(callstack, frames, STDERR_FILENO);
    }
  }
}
