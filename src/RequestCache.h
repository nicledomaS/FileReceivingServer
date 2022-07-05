#pragma once

#include "RequestHandler.h"

#include <set>
#include <map>

class RequestCache : public RequestHandler
{
public:
    RequestCache();
    std::shared_ptr<Response> handle(std::shared_ptr<Request> request) override;

private:
    std::map<int64_t, std::set<Request>> m_requests;
    std::map<int64_t, uint32_t> m_crcs;
};