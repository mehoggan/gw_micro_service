#ifndef GW_MICRO_SERVICE_MICRO_SERVICE_RUNTIME_UTILS_H_INCLUDED
#define GW_MICRO_SERVICE_MICRO_SERVICE_RUNTIME_UTILS_H_INCLUDED

#include <execinfo.h>
#include <unistd.h>

namespace gw_micro_service
{
  namespace micro_service
  {
    class RuntimeUtils
    {
    public:
      static void print_stack_trace();
    };
  }
}

#endif
