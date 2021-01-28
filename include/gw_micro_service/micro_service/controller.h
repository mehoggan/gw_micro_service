#ifndef GW_MICRO_SERVICE_MICRO_SERVICE_CONTROLLER_H_INCLUDED
#define GW_MICRO_SERVICE_MICRO_SERVICE_CONTROLLER_H_INCLUDED

#include "cpprest/http_msg.h"

namespace gw_micro_service
{
  namespace micro_service
  {
    class Controller
    {
    public: 
      virtual void handle_get(web::http::http_request message) = 0;
      virtual void handle_put(web::http::http_request message) = 0;
      virtual void handle_post(web::http::http_request message) = 0;
      virtual void handle_delete(web::http::http_request message) = 0;
      virtual void handle_patch(web::http::http_request messge) = 0;
      virtual void handle_head(web::http::http_request message) = 0;
      virtual void handle_options(web::http::http_request message) = 0;
      virtual void handle_trace(web::http::http_request message) = 0;
      virtual void handle_connect(web::http::http_request message) = 0;
      virtual void handle_merge(web::http::http_request message) = 0;
    };
  }
}

#endif
