#pragma once

#include <memory>

class Request;
class Response;

class RequestHandler
{
public:
    virtual ~RequestHandler() = default;
    virtual std::shared_ptr<Response> handle(std::shared_ptr<Request> request) = 0;
};