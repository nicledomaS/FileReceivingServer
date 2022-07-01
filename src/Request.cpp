#include "Request.h"

Request::Request(
        sockaddr_in clientAddr,
        const unsigned char* data,
        size_t size)
    : m_clientAddr(std::move(clientAddr)),
    m_buffer(data, data + size)
{
}

sockaddr_in* Request::getClientAddr()
{
    return &m_clientAddr;
}

Response::Response(std::weak_ptr<Request> request)
    : m_request(std::move(request))
{
}

sockaddr_in* Response::getClientAddr()
{
    auto request = m_request.lock();
    return request ? request->getClientAddr() : nullptr;
}