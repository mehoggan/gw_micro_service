#include "gw_micro_service/micro_service/std_micro_service.h"
#include "gw_micro_service/micro_service/micro_service_controller.h"

#include <iterator>
#include <sstream>

namespace gw_micro_service
{
  namespace micro_service
  {
    MicroServiceController::MicroServiceController() :
      BasicController()
    {}

    MicroServiceController::~MicroServiceController()
    {}

    void MicroServiceController::init_rest_op_handlers()
    {
      listener_.support(web::http::methods::GET,
        std::bind(&MicroServiceController::handle_get,
        this,
        std::placeholders::_1));
      listener_.support(web::http::methods::PUT,
        std::bind(&MicroServiceController::handle_put,
        this,
        std::placeholders::_1));
      listener_.support(web::http::methods::POST,
        std::bind(&MicroServiceController::handle_post,
        this,
        std::placeholders::_1));
      listener_.support(web::http::methods::DEL,
        std::bind(&MicroServiceController::handle_delete,
        this,
        std::placeholders::_1));
      listener_.support(web::http::methods::PATCH,
        std::bind(&MicroServiceController::handle_patch,
        this,
        std::placeholders::_1));
    }

    void MicroServiceController::handle_get(web::http::http_request message)
    {
      std::vector<std::string> path = request_path(message);

      std::ostringstream oss;
      std::copy(path.begin(), path.end(),
        std::ostream_iterator<std::string>(oss, "/"));
      std::cout << "path = " << oss.str() << std::endl;

      auto response = web::json::value::object();
      response["version"] = web::json::value::string("0.1.1");
      response["status"] = web::json::value::string("ready!");
      message.reply(web::http::status_codes::OK, response);
    }

    void MicroServiceController::handle_patch(web::http::http_request message)
    {
      std::cout << __FUNCTION__ << " was called." << std::endl;
      message.reply(web::http::status_codes::NotImplemented,
        response_not_impl(web::http::methods::PATCH));
    }

    void MicroServiceController::handle_put(web::http::http_request message)
    {
      std::cout << __FUNCTION__ << " was called." << std::endl;
      message.reply(web::http::status_codes::NotImplemented,
        response_not_impl(web::http::methods::PUT));
    }

    void MicroServiceController::handle_post(web::http::http_request message)
    {
      std::cout << __FUNCTION__ << " was called." << std::endl;
      message.reply(web::http::status_codes::NotImplemented,
        response_not_impl(web::http::methods::POST));
    }

    void MicroServiceController::handle_delete(web::http::http_request message)
    {    
      std::cout << __FUNCTION__ << " was called." << std::endl;
      message.reply(web::http::status_codes::NotImplemented,
        response_not_impl(web::http::methods::DEL));
    }

    void MicroServiceController::handle_head(web::http::http_request message)
    {
      std::cout << __FUNCTION__ << " was called." << std::endl;
      message.reply(web::http::status_codes::NotImplemented,
        response_not_impl(web::http::methods::HEAD));
    }

    void MicroServiceController::handle_options(
      web::http::http_request message)
    {
      std::cout << __FUNCTION__ << " was called." << std::endl;
      message.reply(web::http::status_codes::NotImplemented,
        response_not_impl(web::http::methods::OPTIONS));
    }

    void MicroServiceController::handle_trace(web::http::http_request message)
    {
      std::cout << __FUNCTION__ << " was called." << std::endl;
      message.reply(web::http::status_codes::NotImplemented,
        response_not_impl(web::http::methods::TRCE));
    }

    void MicroServiceController::handle_connect(
      web::http::http_request message)
    {
      std::cout << __FUNCTION__ << " was called." << std::endl;
      message.reply(web::http::status_codes::NotImplemented,
        response_not_impl(web::http::methods::CONNECT));
    }

    void MicroServiceController::handle_merge(web::http::http_request message)
    {
      std::cout << __FUNCTION__ << " was called." << std::endl;
      message.reply(web::http::status_codes::NotImplemented,
        response_not_impl(web::http::methods::MERGE));
    }

    web::json::value MicroServiceController::response_not_impl(
      const web::http::method &method)
    {
      auto response = web::json::value::object();
      response["serviceName"] = web::json::value::string("MircroService");
      response["http_method"] = web::json::value::string(method);
      return response ;
    }
  }
}
