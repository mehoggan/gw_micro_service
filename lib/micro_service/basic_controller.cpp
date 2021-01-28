#include "gw_micro_service/micro_service/basic_controller.h"
#include "gw_micro_service/micro_service/network_utils.h"

namespace gw_micro_service
{
  namespace micro_service
  {
    void BasicController::set_endpoint(const std::string &value)
    {
      web::uri endpoint_URI(value);
      web::uri_builder endpoint_builder;

      endpoint_builder.set_scheme(endpoint_URI.scheme());
      // TODO (mehoggan@gmail.com): Use config to determine IPv4 or IPv6.
      endpoint_builder.set_host(NetworkUtils::host_IP4());        
      endpoint_builder.set_port(endpoint_URI.port());
      endpoint_builder.set_path(endpoint_URI.path());

      listener_ = web::http::experimental::listener::http_listener(
        endpoint_builder.to_uri());
    }

    std::string BasicController::endpoint() const
    {
      return listener_.uri().to_string();
    }

    pplx::task<void> BasicController::accept()
    {
      init_rest_op_handlers();
      return listener_.open();
    }

    pplx::task<void> BasicController::shutdown()
    {
      return listener_.close();
    }

    std::vector<utility::string_t> BasicController::request_path(
      const web::http::http_request &message)
    {
      auto relative_path = web::uri::decode(message.relative_uri().path());
      return web::uri::split_path(relative_path);        
    }

    void BasicController::init_rest_op_handlers()
    {}
  }
}
