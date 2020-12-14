#include "gw_micro_service/service_time/ServiceTime.h"

#include <cppmicroservices/BundleActivator.h>

class ServiceTimeSystemClock : public ServiceTime
{
  std::chrono::milliseconds elapsed() const
  {
    auto now = std::chrono::system_clock::now();

    return std::chrono::duration_cast<std::chrono::milliseconds>(
      now.time_since_epoch());
  }
};

class ServiceTimeActivator : public cppmicroservices::BundleActivator
{
  void Start(cppmicroservices::BundleContext ctx)
  {
    auto service = std::make_shared<ServiceTimeSystemClock>();
    ctx.RegisterService<ServiceTime>(service);
  }

  void Stop(cppmicroservices::BundleContext ctx)
  {
    (void) ctx;
  }
};

CPPMICROSERVICES_EXPORT_BUNDLE_ACTIVATOR(ServiceTimeActivator)

// [no-cmake]
// The code below is required if the CMake
// helper functions are not used.
#ifdef NO_CMAKE
CPPMICROSERVICES_INITIALIZE_BUNDLE(service_time_systemclock)
#endif
