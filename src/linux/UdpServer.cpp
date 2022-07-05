#include "UdpServer.h"
#include "../Request.h"

#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>

#include <stdexcept>
#include <iostream>
#include <vector>

namespace
{

socklen_t SockAddrStructLength = sizeof(sockaddr_in);

} // anonymous

UdpServer::UdpServer(unsigned short port)
    : m_socketFd(socket(AF_INET, SOCK_DGRAM, 0))
{
    if(m_socketFd < 0)
    {
        throw std::runtime_error("ERROR opening socket");
    }

    auto optval = 1;
    setsockopt(m_socketFd, SOL_SOCKET, SO_REUSEADDR, &optval , sizeof(int));

    sockaddr_in serveraddr;
    memset(&serveraddr, 0, SockAddrStructLength);
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
    serveraddr.sin_port = htons(port);

    if (bind(m_socketFd, (struct sockaddr *) &serveraddr, SockAddrStructLength) < 0)
    {
        throw std::runtime_error("ERROR on binding");
    }
}

std::shared_ptr<Request> UdpServer::receive()
{
    auto request = std::make_shared<Request>();
    auto clientAddr = request->getClientAddr();
    std::vector<unsigned char> buffer(MaxPacketSize, 0);
    auto result = recvfrom(m_socketFd, buffer.data(), buffer.size(), 0, reinterpret_cast<sockaddr*>(clientAddr), &SockAddrStructLength);
    
    std::cout << "Received: " << result << " bytes" << std::endl;
   
    if(result < 0)
    {
        //throw
    }

    request->fromBytes(std::vector<unsigned char>(buffer.data(), buffer.data() + result));
  
    return request;
}

void UdpServer::send(std::shared_ptr<Response> responce)
{
    auto* clientAddr = responce->getClientAddr();
    if(clientAddr)
    {
        auto data = responce->toBytes();
        auto result = sendto(m_socketFd, data.data(), data.size(), 0, reinterpret_cast<sockaddr*>(clientAddr), SockAddrStructLength);
        if(result < 0)
        {
            //throw
        }

        std::cout << "Sent: " << result << " bytes" << std::endl;
    }
}