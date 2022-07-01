#include "FileReceivingServer.h"
#include "UdpServer.h"
#include "RequestCache.h"

FileReceivingServer::FileReceivingServer()
    : m_server(std::make_unique<UdpServer>()),
    m_requestHandler(std::make_unique<RequestCache>())
{
}

FileReceivingServer::~FileReceivingServer()
{
}
    
void FileReceivingServer::run()
{
    while(true)
    {
        auto request = m_server->receive();
        auto response = m_requestHandler->handle(std::move(request));
        m_server->send(std::move(response));
    }
}