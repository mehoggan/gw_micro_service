#ifndef GW_MICRO_SERVICE_DICTIONARY_SERVICE_ACTIVATOR_H_INCLUDED
#define GW_MICRO_SERVICE_DICTIONARY_SERVICE_ACTIVATOR_H_INCLUDED

#include <cppmicroservices/BundleActivator.h>
#include <cppmicroservices/BundleContext.h>
#include <cppmicroservices/ServiceProperties.h>

namespace gw_micro_service
{
  namespace dictionary_service
  {
    class US_ABI_LOCAL Activator : public cppmicroservices::BundleActivator
    {
    public:
      virtual void Start(cppmicroservices::BundleContext context) override;

      virtual void Stop(cppmicroservices::BundleContext context) override;
    };
  }
}

#endif
