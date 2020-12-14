#include "gw_micro_service/service_time/ServiceTime.h"

#include <cppmicroservices/BundleActivator.h>
#include <cppmicroservices/BundleContext.h>
#include <cppmicroservices/GetBundleContext.h>

#include <iostream>

class ServiceTimeConsumerActivator : public cppmicroservices::BundleActivator
{
  typedef cppmicroservices::ServiceReference<ServiceTime> ServiceTimeRef;

  void Start(cppmicroservices::BundleContext ctx)
  {
    auto ref = ctx.GetServiceReference<ServiceTime>();

    PrintTime(ref);
  }

  void Stop(cppmicroservices::BundleContext ctx)
  {
    (void) ctx;
  }

  void PrintTime(const ServiceTimeRef& ref) const
  {
    if (!ref) {
      std::cout << "ServiceTime reference invalid" << std::endl;
      return;
    }

    auto ctx = cppmicroservices::GetBundleContext();

    auto svc_time = ctx.GetService(ref);
    if (!svc_time) {
      std::cerr<< "ServiceTime not available" << std::endl;
    } else {
      std::cout << "Elapsed: " << svc_time->elapsed().count() << "ms"
        << std::endl;
    }
  }
};

CPPMICROSERVICES_EXPORT_BUNDLE_ACTIVATOR(ServiceTimeConsumerActivator)

// [no-cmake]
// The code below is required if the CMake
// helper functions are not used.
#ifdef NO_CMAKE
CPPMICROSERVICES_INITIALIZE_BUNDLE(service_time_consumer)
#endif
