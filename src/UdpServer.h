#pragma once

#include "Server.h"

class UdpServer : public Server
{
public:
    UdpServer();
    std::shared_ptr<Request> receive() override;
    void send(std::shared_ptr<Response> responce) override;
};