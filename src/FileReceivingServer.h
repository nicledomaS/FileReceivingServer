#pragma once

#include "Application.h"

#include <memory>

class Server;
class RequestHandler;

class FileReceivingServer : public Application
{
public:
    explicit FileReceivingServer(unsigned short port);
    ~FileReceivingServer() override;
    void run() override;

private:
    std::unique_ptr<Server> m_server;
    std::unique_ptr<RequestHandler> m_requestHandler;
};