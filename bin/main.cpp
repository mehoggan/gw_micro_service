#include "gw_micro_service/dictionary_service/IDictionaryService.h"

#include <cppmicroservices/Bundle.h>
#include <cppmicroservices/BundleContext.h>
#include <cppmicroservices/BundleImport.h>
#include <cppmicroservices/Framework.h>
#include <cppmicroservices/FrameworkEvent.h>
#include <cppmicroservices/FrameworkFactory.h>
#include <cppmicroservices/GetBundleContext.h>
#include <cppmicroservices/ServiceReference.h>

#include <algorithm>
#include <cstdint>
#include <iostream>
#include <iomanip>
#include <map>
#include <set>
#include <sstream>
#include <stdexcept>


int main(int /*argc*/, char** /*argv*/)
{
  char cmd[256];

  std::unordered_map<std::string, long> symbolicNameToId;

  cppmicroservices::FrameworkFactory factory;
  auto framework = factory.NewFramework();

  try {
    framework.Start();
    framework.GetBundleContext().InstallBundles("/home/mehoggan/Devel/build/"
      "github/mehoggan/gw_micro_service/lib/dictionary_service/"
      "libDictionaryServiced.so");
    framework.GetBundleContext().GetBundles()[0].Start();
  } catch (const std::exception &e) {
    std::cerr << e.what() << std::endl;
    return EXIT_FAILURE;
  }

  namespace gw =  gw_micro_service::dictionary_service;
  cppmicroservices::ServiceReference<gw::IDictionaryService> service_ref =
    framework.GetBundleContext().GetServiceReference<gw::IDictionaryService>();

  std::cout << "> ";
  while (std::cin.getline(cmd, sizeof(cmd))) {
    if (framework.GetState() != cppmicroservices::Bundle::STATE_ACTIVE) {
      break;
    }

    std::string str_cmd(cmd);
    if (str_cmd == "shutdown") {
      break;
    } else if (str_cmd == "h" || str_cmd == "help") {
      std::cout << std::left << std::setw(20) << "h"
        << " This help text\n"
        << std::setw(20) << "status"
        << " Print status information\n"
        << std::setw(20) << "shutdown"
        << " Shut down the framework\n"
        << std::flush;
    } else if (str_cmd == "status") {
      std::cout << std::left;
      std::cout << "Symbolic Name" << " | " << std::setw(9) << "State"
        << std::endl;
      std::cout << "-----------------------------------\n";
      auto bundle = framework.GetBundleContext().GetBundles()[0];

      std::cout << std::setw(20) << bundle.GetSymbolicName() << " | ";
      std::cout << std::setw(9) << (bundle.GetState());
      std::cout << std::endl;

      auto service = service_ref
        .GetBundle()
        .GetBundleContext()
        .GetService<gw::IDictionaryService>(service_ref);
      std::cout << std::setw(20)
        << (service->CheckWord("Tutorial") ? "true" : "false")
        << std::endl;
    } else if (str_cmd == "shutdown") {
      break;
    } else {
      std::cout << "Unknown command: " << str_cmd << " (type 'h' for help)"
        << std::endl;
    }
    
    std::cout << "> "; 
  }

  framework.Stop();
  framework.WaitForStop(std::chrono::seconds(2));

  return 0;
}

#ifndef US_BUILD_SHARED_LIBS
CPPMICROSERVICES_INITIALIZE_STATIC_BUNDLE(system_bundle)
CPPMICROSERVICES_IMPORT_BUNDLE(dictionaryservice)
#endif
