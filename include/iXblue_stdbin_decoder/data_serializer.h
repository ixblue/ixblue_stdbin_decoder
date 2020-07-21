#pragma once

#include "iXblue_stdbin_decoder/data_models/stdbin.h"

#include <boost/asio/buffer.hpp>
#include <boost/core/noncopyable.hpp>
#include <memory>
#include <bitset>

namespace StdBinDecoder
{

boost::asio::mutable_buffer& operator<<(boost::asio::mutable_buffer& buf, double data);
boost::asio::mutable_buffer& operator<<(boost::asio::mutable_buffer& buf, float data);
boost::asio::mutable_buffer& operator<<(boost::asio::mutable_buffer& buf, int32_t data);
boost::asio::mutable_buffer& operator<<(boost::asio::mutable_buffer& buf, uint64_t data);
boost::asio::mutable_buffer& operator<<(boost::asio::mutable_buffer& buf, uint32_t data);
boost::asio::mutable_buffer& operator<<(boost::asio::mutable_buffer& buf, uint16_t data);
boost::asio::mutable_buffer& operator<<(boost::asio::mutable_buffer& buf, uint8_t data);

template<size_t N>
boost::asio::mutable_buffer& operator<<(boost::asio::mutable_buffer& buf,
                                        const std::array<uint8_t, N>& data)
{
    for (size_t bytes_index = 0; bytes_index < data.size(); bytes_index++)
    {
        buf << data[bytes_index];
    }
    return buf;
}

inline boost::asio::mutable_buffer& operator<<(boost::asio::mutable_buffer& buf,
                                               const std::vector<uint8_t>& data)
{
    for (size_t bytes_index = 0; bytes_index < data.size(); bytes_index++)
    {
        buf << data[bytes_index];
    }
    return buf;
}

class DataSerializer : public boost::noncopyable
{
private:
    DataSerializer() = delete; // ensure that offsetInMask will always be set.

public:
    typedef std::bitset<32> tBitMask;
    DataSerializer(size_t offsetInMask, size_t bytesCount)
        : bytesCount(bytesCount)
        , offsetInMask(offsetInMask) { }

    bool serialize(boost::asio::mutable_buffer& outBuffer, tBitMask& mask,
                   const Data::BinaryNav& binaryNav);

    virtual bool serialize(boost::asio::mutable_buffer& outBuffer,
                           const Data::BinaryNav& binaryNav) = 0;

    size_t getBytesCount(void) const { return bytesCount; }
    size_t getOffsetInMask(void) const { return offsetInMask; }

protected:
    const size_t bytesCount;
    const size_t offsetInMask;
};

typedef std::shared_ptr<DataSerializer> DataSerializerPtr;
} // namespace StdBinDecoder
