#pragma once

#include <memory>

constexpr auto MaxPacketSize = 1472;

class Request;
class Response;

class Server
{
public:
    virtual ~Server() = default;
    virtual std::shared_ptr<Request> receive() = 0;
    virtual void send(std::shared_ptr<Response> responce) = 0;
};