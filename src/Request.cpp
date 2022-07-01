#include "Request.h"

#include <string.h>

namespace
{

constexpr auto headerLen = sizeof(Header);

} // anonymous


bool operator<(const Request& lhs, const Request& rhs)
{
    auto lheader = lhs.getHeader();
    auto rheader = rhs.getHeader();
    return lheader.seq_number < rheader.seq_number;
}

Request::Request()
{
}

const Header& Request::getHeader() const
{
    return m_header;
}

std::vector<unsigned char> Request::getData() const
{
    return m_data;
}

sockaddr_in* Request::getClientAddr()
{
    return &m_clientAddr;
}

void Request::fromBytes(const std::vector<unsigned char>& buffer)
{
    if(buffer.empty())
    {
        //throw
    }

    memcpy(&m_header, buffer.data(), headerLen);
    m_data = std::vector<unsigned char>(buffer.begin() + headerLen, buffer.end());
}

Response::Response(Request& request)
    : m_clientAddr(request.getClientAddr()),
    m_header(request.getHeader()),
    m_crc(0)
{
    m_header.type = 0;
}

sockaddr_in* Response::getClientAddr()
{
    return m_clientAddr;
}

void Response::setNumPacket(uint32_t numPacket)
{
    m_header.seq_number = numPacket;
}

void Response::setCrc(uint32_t crc)
{
    m_crc = crc;
}

std::vector<unsigned char> Response::toBytes() const
{
    constexpr auto crcLen = sizeof(uint32_t);
    std::vector<unsigned char> buffer(headerLen + crcLen, 0);
    
    auto ptr = buffer.data();
    memcpy(ptr, &m_header, headerLen);
    ptr += headerLen;
    memcpy(ptr, &m_crc, crcLen);

    return buffer;
}