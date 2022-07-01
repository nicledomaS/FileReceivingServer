#include "UdpServer.h"
#include "../Request.h"

#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>

#include <stdexcept>
#include <iostream>

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
    memset(&serveraddr, 0, sizeof(serveraddr));
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
    serveraddr.sin_port = htons(port);

    if (bind(m_socketFd, (struct sockaddr *) &serveraddr, sizeof(serveraddr)) < 0)
    {
        throw std::runtime_error("ERROR on binding");
    }
}

std::shared_ptr<Request> UdpServer::receive()
{
    sockaddr_in clientAddr;
    socklen_t clientStructLength = sizeof(clientAddr);
    auto result = recvfrom(m_socketFd, m_buffer.data(), m_buffer.size(), 0, reinterpret_cast<sockaddr*>(&clientAddr), &clientStructLength);
    std::cout << "Receive: " << result << " butes" << std::endl;
  
    return std::make_shared<Request>(std::move(clientAddr), m_buffer.data(), result);
}

void UdpServer::send(std::shared_ptr<Response> responce)
{
    sockaddr_in* clientAddr = responce->getClientAddr();
    if(clientAddr)
    {
        socklen_t clientStructLength = sizeof(*clientAddr);
        auto result = sendto(m_socketFd, m_buffer.data(), m_buffer.size(), 0, reinterpret_cast<sockaddr*>(clientAddr), clientStructLength);
        std::cout << "Send: " << result << " butes" << std::endl;
    }
}