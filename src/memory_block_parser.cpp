#include <iXblue_stdbin_decoder/memory_block_parser.h>
#include <boost/endian/conversion.hpp>

namespace ixblue_stdbin_decoder
{

void MemoryBlockParser::parse(boost::asio::mutable_buffer& buffer, const tBitMask& mask,
                              Data::BinaryNav& outBinaryNav)
{
    // If this memory block is present in the frame,
    if(mask.test(offsetInMask))
    {
        // And there is enough bytes in buffer we can parse it :
        if(boost::asio::buffer_size(buffer) >= bytesCount)
        {
            parse(buffer, outBinaryNav);
        }
        else
        {
            throw std::runtime_error(
                "Not enough byes in buffer to parse this memory block");
        }
    }
}

boost::asio::mutable_buffer& operator>>(boost::asio::mutable_buffer& buf, double& res)
{
    uint64_t bytes = *boost::asio::buffer_cast<uint64_t*>(buf);
    boost::endian::big_to_native_inplace(bytes);
    res = *reinterpret_cast<double*>(&bytes);
    buf = buf + sizeof(double);
    return buf;
}

boost::asio::mutable_buffer& operator>>(boost::asio::mutable_buffer& buf, float& res)
{
    uint32_t bytes = *boost::asio::buffer_cast<uint32_t*>(buf);
    boost::endian::big_to_native_inplace(bytes);
    res = *reinterpret_cast<float*>(&bytes);
    buf = buf + sizeof(float);
    return buf;
}

boost::asio::mutable_buffer& operator>>(boost::asio::mutable_buffer& buf, int32_t& res)
{
    res = *boost::asio::buffer_cast<int32_t*>(buf);
    boost::endian::big_to_native_inplace(res);
    buf = buf + sizeof(int32_t);
    return buf;
}

boost::asio::mutable_buffer& operator>>(boost::asio::mutable_buffer& buf, uint64_t& res)
{
    res = *boost::asio::buffer_cast<uint64_t*>(buf);
    boost::endian::big_to_native_inplace(res);
    buf = buf + sizeof(uint64_t);
    return buf;
}

boost::asio::mutable_buffer& operator>>(boost::asio::mutable_buffer& buf, uint32_t& res)
{
    res = *boost::asio::buffer_cast<uint32_t*>(buf);
    boost::endian::big_to_native_inplace(res);
    buf = buf + sizeof(uint32_t);
    return buf;
}

boost::asio::mutable_buffer& operator>>(boost::asio::mutable_buffer& buf, uint16_t& res)
{
    res = *boost::asio::buffer_cast<uint16_t*>(buf);
    boost::endian::big_to_native_inplace(res);
    buf = buf + sizeof(uint16_t);
    return buf;
}

boost::asio::mutable_buffer& operator>>(boost::asio::mutable_buffer& buf, uint8_t& res)
{
    res = *boost::asio::buffer_cast<uint8_t*>(buf);
    buf = buf + sizeof(uint8_t);
    return buf;
}

} // namespace ixblue_stdbin_decoder
