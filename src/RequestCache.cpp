#include "RequestCache.h"
#include "Request.h"

#include <iostream>
#include <string.h>

namespace
{

uint32_t crc32c(uint32_t crc, const unsigned char *buf, size_t len)
{
    int k;
    crc = ~crc;
    while (len--) {
        crc ^= *buf++;
        for (k = 0; k < 8; k++)
        crc = crc & 1 ? (crc >> 1) ^ 0x82f63b78 : crc >> 1;
    }
    return ~crc;
}


} // anonymous

RequestCache::RequestCache()
{
}

std::shared_ptr<Response> RequestCache::handle(std::shared_ptr<Request> request)
{
    auto responce = std::make_shared<Response>(*request);
    
    auto header = request->getHeader();
    int64_t id = *(reinterpret_cast<const int64_t*>(header.id));

    auto crcIt = m_crcs.find(id);
    if(crcIt != m_crcs.end())
    {
        responce->setNumPacket(header.seq_total);
        responce->setCrc(crcIt->second);
    }
    else
    {
        auto it = m_requests.find(id);
        if(it == m_requests.end())
        {
            auto res = m_requests.insert({ id, std::set<Request>() });
            it = res.first;
        }

        auto& requests = it->second;
        requests.insert(std::move(*request));
        responce->setNumPacket(requests.size());

        auto seq_total = header.seq_total;
        if(requests.size() == seq_total)
        {
            uint32_t crc = 0;

            for(const auto& request : requests)
            {
                auto data = request.getData();
                crc = crc32c(crc, data.data(), data.size());
            }

            std::cout << "crc: " << crc << std::endl;

            responce->setCrc(crc);
            m_crcs.insert({ id, crc });
            m_requests.erase(it); 
        }
    }

    return responce;
}