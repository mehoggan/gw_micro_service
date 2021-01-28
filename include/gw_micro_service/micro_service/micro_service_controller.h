#ifndef GW_MICRO_SERVICE_MICRO_SERVICE_MICROSERVICE_CONTROLLER_H_INCLUDED
#define GW_MICRO_SERVICE_MICRO_SERVICE_MICROSERVICE_CONTROLLER_H_INCLUDED

#include "gw_micro_service/micro_service/basic_controller.h"

namespace gw_micro_service
{
  namespace micro_service
  {
    class MicroServiceController : public BasicController, Controller
    {
    public:
        MicroServiceController();
        ~MicroServiceController();
        void handle_get(web::http::http_request message) override;
        void handle_put(web::http::http_request message) override;
        void handle_post(web::http::http_request message) override;
        void handle_patch(web::http::http_request message) override;
        void handle_delete(web::http::http_request message) override;
        void handle_head(web::http::http_request message) override;
        void handle_options(web::http::http_request message) override;
        void handle_trace(web::http::http_request message) override;
        void handle_connect(web::http::http_request message) override;
        void handle_merge(web::http::http_request message) override;
        void init_rest_op_handlers() override;    

    private:
        static
        web::json::value response_not_impl(const web::http::method &method);
    };
  }
}

#endif
