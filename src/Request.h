#pragma once

#include <arpa/inet.h>

#include <vector>
#include <memory>

// #pragma pack(push, 1)

struct Header
{
    uint32_t seq_number;
    uint32_t seq_total;
    uint8_t type;
    char id[8];
};

// #pragma pack(pop)

class Request
{
public:
    Request();

    const Header& getHeader() const;
    std::vector<unsigned char> getData() const;

    sockaddr_in* getClientAddr();

    void fromBytes(const std::vector<unsigned char>& buffer);

private:
    sockaddr_in m_clientAddr;
    Header m_header;
    std::vector<unsigned char> m_data;
};

class Response
{
public:
    explicit Response(Request& request);

    sockaddr_in* getClientAddr();
    void setNumPacket(uint32_t numPacket);
    void setCrc(uint32_t crc);

    std::vector<unsigned char> toBytes() const;

private:
    sockaddr_in* m_clientAddr;
    Header m_header;
    uint32_t m_crc;
};

bool operator<(const Request& lhs, const Request& rhs);