
#ifndef GW_MICRO_SERVICE_DICTIONARY_SERVICE_DICTIONARY_SERVICE_H_INCLUDED
#define GW_MICRO_SERVICE_DICTIONARY_SERVICE_DICTIONARY_SERVICE_H_INCLUDED

#include "gw_micro_service/dictionary_service/IDictionaryService.h"

#include <algorithm>
#include <set>

namespace gw_micro_service
{
  namespace dictionary_service
  {
    class DictionaryService : public IDictionaryService
    {
    public:
      DictionaryService();

      bool CheckWord(const std::string &word);

    private:
      std::set<std::string> dictionary_;
    };
  }
}
#endif
