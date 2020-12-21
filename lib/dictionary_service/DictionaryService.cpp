#include "gw_micro_service/dictionary_service/DictionaryService.h"

namespace gw_micro_service
{
  namespace dictionary_service
  {
    DictionaryService::DictionaryService()
    {
      dictionary_.insert("welcome");
      dictionary_.insert("to");
      dictionary_.insert("the");
      dictionary_.insert("micro");
      dictionary_.insert("services");
      dictionary_.insert("tutorial");
    }

    bool DictionaryService::CheckWord(const std::string& word)
    {
      std::string lword(word);
      std::transform(lword.begin(), lword.end(), lword.begin(), ::tolower);

      return dictionary_.find(lword) != dictionary_.end();
    }
  }
}
