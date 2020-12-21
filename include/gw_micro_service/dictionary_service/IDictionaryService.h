#include "cppmicroservices/ServiceInterface.h"

#include <string>

#ifdef US_BUILD_SHARED_LIBS
#  ifdef Tutorial_dictionaryservice_EXPORTS
#    define DICTIONARYSERVICE_EXPORT US_ABI_EXPORT
#  else
#    define DICTIONARYSERVICE_EXPORT US_ABI_IMPORT
#  endif
#else
#  define DICTIONARYSERVICE_EXPORT US_ABI_EXPORT
#endif

namespace gw_micro_service
{
  namespace dictionary_service
  {
    struct DICTIONARYSERVICE_EXPORT IDictionaryService
    {
      virtual ~IDictionaryService();

      virtual bool CheckWord(const std::string& word) = 0;
    };
  }
}
