#include "gw_micro_service/micro_service/network_utils.h"

namespace gw_micro_service
{
  namespace micro_service
  {
    HostInetInfo NetworkUtils::query_host_inet_info()
    {
      boost::asio::io_service ios;
      boost::asio::ip::tcp::resolver resolver(ios);
      boost::asio::ip::tcp::resolver::query query(host_name(), "");
      return resolver.resolve(query);
    }

    std::string NetworkUtils::host_IP(unsigned short family) {
      std::cout << "Getting host info..." << std::endl;
      auto host_inet_info = query_host_inet_info();
      boost::asio::ip::tcp::resolver::iterator end;
      std::string ret = "";
      while(host_inet_info != end) {
        boost::asio::ip::tcp::endpoint ep = *host_inet_info++;
        sockaddr sa = *ep.data();
        if (sa.sa_family == family) {
          ret = ep.address().to_string();
        }
      }
      return ret;
    }

    std::string NetworkUtils::host_IP4()
    {
     return host_IP(AF_INET);
    }

    std::string NetworkUtils::host_IP6()
    {
     return host_IP(AF_INET6);
    }

    std::string NetworkUtils::host_name()
    {
     return boost::asio::ip::host_name();
    }
  }
}
