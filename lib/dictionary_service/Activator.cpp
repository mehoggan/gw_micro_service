#include "gw_micro_service/dictionary_service/IDictionaryService.h"

#include <cppmicroservices/BundleActivator.h>
#include <cppmicroservices/BundleContext.h>
#include <cppmicroservices/ServiceProperties.h>

#include <memory>
#include <set>


namespace
{
  class US_ABI_LOCAL Activator :
    public cppmicroservices::BundleActivator
  {

  private:
    class DictionaryImpl : public IDictionaryService
    {
    private:
      std::set<std::string> dictionary_;

    public:
      DictionaryImpl()
      {
        dictionary_.insert("welcome");
        dictionary_.insert("to");
        dictionary_.insert("the");
        dictionary_.insert("micro");
        dictionary_.insert("services");
        dictionary_.insert("tutorial");
      }

      bool CheckWord(const std::string& word)
      {
        std::string lword(word);
        std::transform(lword.begin(), lword.end(), lword.begin(), ::tolower);

        return dictionary_.find(lword) != dictionary_.end();
      }
    };

  public:
    void Start(cppmicroservices::BundleContext context)
    {
      std::shared_ptr<DictionaryImpl> dictionary_Service =
        std::make_shared<DictionaryImpl>();
      cppmicroservices::ServiceProperties props;
      props["Language"] = std::string("English");
      context.RegisterService<IDictionaryService>(dictionary_Service, props);
    }

    void Stop(cppmicroservices::BundleContext context)
    {
      (void) context;
    }
  };
}

CPPMICROSERVICES_EXPORT_BUNDLE_ACTIVATOR(Activator)
