#include "RequestCache.h"
#include "Request.h"

RequestCache::RequestCache()
{
}

std::shared_ptr<Response> RequestCache::handle(std::shared_ptr<Request> request)
{
    auto responce = std::make_shared<Response>(request);
    m_requests[0].push_back(std::move(request));
    return responce;
}