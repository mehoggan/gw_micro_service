#include "gw_micro_service/micro_service/interrupt_handler.h"
#include "gw_micro_service/micro_service/runtime_utils.h"
#include "gw_micro_service/micro_service/micro_service_controller.h"

#include <cstdlib>

int main(int argc, const char *argv[])
{
  (void) argc;
  (void) argv;

  gw_micro_service::micro_service::InterruptHandler::hook_SIGINT();

  gw_micro_service::micro_service::MicroServiceController server;
  server.set_endpoint("http://localhost:8081/v1/api");
  
  try {
    server.accept().wait();
    std::cout << "Modern C++ Micro Service now listening for requests at: "
      << server.endpoint() << '\n';
    gw_micro_service::micro_service::InterruptHandler
      ::wait_for_user_interrupt();
    server.shutdown().wait();
  } catch(std::exception & e) {
    std::cerr << "something wrong happened! :(" << '\n';
  } catch(...) {
    gw_micro_service::micro_service::RuntimeUtils::print_stack_trace();
  }

  return EXIT_SUCCESS;
}
