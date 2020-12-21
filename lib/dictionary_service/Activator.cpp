#include "gw_micro_service/dictionary_service/Activator.h"

#include "gw_micro_service/dictionary_service/DictionaryService.h"

#include <iostream>
#include <memory>
namespace gw_micro_service
{
  namespace dictionary_service
  {
    void Activator::Start(cppmicroservices::BundleContext context)
    {
      std::shared_ptr<DictionaryService> dictionary_service =
        std::make_shared<DictionaryService>();
      cppmicroservices::ServiceProperties props;
      props["Language"] = std::string("English");
      context.RegisterService<IDictionaryService>(dictionary_service, props);
      std::cout << "Starting service in " << __FILE__ << std::endl;
    }

    void Activator::Stop(cppmicroservices::BundleContext context)
    {
      (void) context;
    }
  }
}

CPPMICROSERVICES_EXPORT_BUNDLE_ACTIVATOR(
  gw_micro_service::dictionary_service::Activator)
