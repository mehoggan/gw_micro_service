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

struct DICTIONARYSERVICE_EXPORT IDictionaryService
{
  virtual ~IDictionaryService();

  /**
   * Check for the existence of a word.
   * @param word the word to be checked.
   * @return true if the word is in the dictionary,
   *         false otherwise.
   **/
  virtual bool CheckWord(const std::string& word) = 0;
};
