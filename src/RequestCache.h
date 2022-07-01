#pragma once

#include "RequestHandler.h"

#include <vector>
#include <map>

class RequestCache : public RequestHandler
{
public:
    RequestCache();
    std::shared_ptr<Response> handle(std::shared_ptr<Request> request) override;

private:
    std::map<int, std::vector<std::shared_ptr<Request>>> m_requests;
};