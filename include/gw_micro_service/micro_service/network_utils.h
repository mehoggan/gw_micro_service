#ifndef GW_MICRO_SERVICE_MICRO_SERVICE_NETWORK_UTILS_H_INCLUDED
#define GW_MICRO_SERVICE_MICRO_SERVICE_NETWORK_UTILS_H_INCLUDED

#include "gw_micro_service/micro_service/std_micro_service.h"

#include <string>

namespace gw_micro_service
{
  namespace micro_service
  {
    using HostInetInfo = boost::asio::ip::tcp::resolver::iterator;

    class NetworkUtils
    {
    private:
      static HostInetInfo query_host_inet_info();
      static std::string host_IP(unsigned short family);

    public:
      static std::string host_IP4();
      static std::string host_IP6();
      static std::string host_name();
    };
  }
}

#endif
