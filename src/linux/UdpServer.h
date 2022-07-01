#pragma once

#include "../Server.h"

#include <array>

class UdpServer : public Server
{
public:
    explicit UdpServer(unsigned short port);
    std::shared_ptr<Request> receive() override;
    void send(std::shared_ptr<Response> responce) override;

private:
    int m_socketFd;
    std::array<unsigned char, MaxPacketSize> m_buffer;
};