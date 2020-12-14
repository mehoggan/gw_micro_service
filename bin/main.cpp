#include <cppmicroservices/Bundle.h>
#include <cppmicroservices/BundleContext.h>
#include <cppmicroservices/BundleImport.h>
#include <cppmicroservices/Framework.h>
#include <cppmicroservices/FrameworkFactory.h>

#include <cstdlib>

using namespace cppmicroservices;

int main(int argc, char* argv[])
{
  int status_code = EXIT_SUCCESS;

  Framework fw = FrameworkFactory().NewFramework();

  try {
    fw.Init();
  } catch (const std::exception& e) {
    std::cout << e.what() << std::endl;
    return EXIT_FAILURE;
  }

  auto ctx = fw.GetBundleContext();
  if (!ctx) {
    std::cerr << "Invalid framework context" << std::endl;
    status_code = EXIT_FAILURE;
  } else {
    for (int i = 1; i < argc; ++i) {
      try {
        ctx.InstallBundles(argv[i]);
      } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        status_code = EXIT_FAILURE;
      }
    }

    if (status_code != EXIT_FAILURE) {
      try {
        fw.Start();
        auto bundles = ctx.GetBundles();
        auto iter = std::find_if(bundles.begin(), bundles.end(),
          [](Bundle& b) {
            return b.GetSymbolicName() == "service_time_systemclock";
          });
        if (iter != bundles.end()) {
          iter->Start();
        }

        for (auto& bundle : bundles) {
          bundle.Start();
        }
      } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        status_code = EXIT_FAILURE;
      }
    }
  } 

  return status_code;
}

#if !defined(US_BUILD_SHARED_LIBS)
CPPMICROSERVICES_IMPORT_BUNDLE(service_time_systemclock)
CPPMICROSERVICES_IMPORT_BUNDLE(service_time_consumer)
#endif
