#ifndef GW_MICRO_SERVICE_MICRO_SERVICE_BASIC_CONTROLLER_H_INCLUDED
#define GW_MICRO_SERVICE_MICRO_SERVICE_BASIC_CONTROLLER_H_INCLUDED

#include "cpprest/http_listener.h"

#include "pplx/pplxtasks.h"

#include "gw_micro_service/micro_service/controller.h"

#include <string>

namespace gw_micro_service
{
  namespace micro_service
  {
    class BasicController
    {
    protected:
      web::http::experimental::listener::http_listener listener_;

    public:
      BasicController() = default;

      ~BasicController() = default;

      void set_endpoint(const std::string &value);
      std::string endpoint() const;
      pplx::task<void> accept();
      pplx::task<void> shutdown();
      std::vector<utility::string_t> request_path(
        const web::http::http_request &message);

    public:
      virtual void init_rest_op_handlers();
    };
  }
}

#endif
