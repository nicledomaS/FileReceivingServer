#pragma once

#include <arpa/inet.h>

#include <vector>
#include <memory>

class Request
{
public:
    Request(
        sockaddr_in clientAddr,
        const unsigned char* data,
        size_t size);

    sockaddr_in* getClientAddr();

private:
    sockaddr_in m_clientAddr;
    std::vector<unsigned char> m_buffer;
};

class Response
{
public:
    explicit Response(std::weak_ptr<Request> request);

    sockaddr_in* getClientAddr();

private:
    std::weak_ptr<Request> m_request;
    std::vector<unsigned char> m_buffer;
};