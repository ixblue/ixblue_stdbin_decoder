#include <iXblue_stdbin_decoder/data_serializer.h>
#include <boost/endian/conversion.hpp>

using namespace StdBinDecoder;

template <typename T, typename M>
static boost::asio::mutable_buffer& serializeInPlace(boost::asio::mutable_buffer& buf,
                                                     M data)
{
    T bytes = *reinterpret_cast<T*>(&data);
    boost::endian::native_to_big_inplace(bytes);
    std::memcpy(boost::asio::buffer_cast<void*>(buf), &bytes, sizeof(M));
    buf = buf + sizeof(M);
    return buf;
}

boost::asio::mutable_buffer& StdBinDecoder::operator<<(boost::asio::mutable_buffer& buf,
                                                       double data)
{
    return serializeInPlace<int64_t, double>(buf, data);
}

boost::asio::mutable_buffer& StdBinDecoder::operator<<(boost::asio::mutable_buffer& buf,
                                                       float data)
{
    return serializeInPlace<int32_t, float>(buf, data);
}

boost::asio::mutable_buffer& StdBinDecoder::operator<<(boost::asio::mutable_buffer& buf,
                                                       int32_t data)
{
    return serializeInPlace<int32_t, uint32_t>(buf, data);
}

boost::asio::mutable_buffer& StdBinDecoder::operator<<(boost::asio::mutable_buffer& buf,
                                                       uint64_t data)
{
    return serializeInPlace<int64_t, uint64_t>(buf, data);
}

boost::asio::mutable_buffer& StdBinDecoder::operator<<(boost::asio::mutable_buffer& buf,
                                                       uint32_t data)
{
    return serializeInPlace<int32_t, uint32_t>(buf, data);
}

boost::asio::mutable_buffer& StdBinDecoder::operator<<(boost::asio::mutable_buffer& buf,
                                                       uint16_t data)
{
    return serializeInPlace<int16_t, uint16_t>(buf, data);
}

boost::asio::mutable_buffer& StdBinDecoder::operator<<(boost::asio::mutable_buffer& buf,
                                                       uint8_t data)
{
    return serializeInPlace<int8_t, uint8_t>(buf, data);
}

bool DataSerializer::serialize(boost::asio::mutable_buffer& outBuffer, tBitMask& mask,
                               const Data::BinaryNav& binaryNav)
{
    // Make sure the buffer can fit all the data
    if (boost::asio::buffer_size(outBuffer) >= bytesCount)
    {
        if (serialize(outBuffer, binaryNav)) {
            // Set this memory block as present in frame
            mask.set(offsetInMask);
            return true;
        }
    }
    else
    {
        throw std::runtime_error("Buffer is too small to fit this memory block");
    }
    return false;
}
