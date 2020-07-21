#pragma once

#include "data_models/stdbin.h"
#include "data_serializer.h"

#include <boost/noncopyable.hpp>
#include <functional>
#include <set>

namespace StdBinDecoder
{

/*!
 * \brief Serializer of a STDBIN IXblue message.
 * This is the entry point of the library. Usage of this class is as follow :
 * \code
 * StdBinEncoder serializer;
 * ///...
 * try {
 *   std::vector<uint8_t> data;
 *   data = serializer.serialize(binaryNav);
 * } catch(std::runtime_error& e){
 *   // Serialization errors are reported by throwing std::runtime_exception.
 * }
 * \endcode
 */
class StdBinEncoder : private boost::noncopyable
{
    // we sort the serializers list by offsetMask because this is a design constraint.
    // We need to process serializes in the same ordrer than data are filled in memory.
    typedef std::set<
        DataSerializerPtr,
        std::function<bool(const DataSerializerPtr&, const DataSerializerPtr&)>>
        tSerializersSet;

public:
    enum ProtocolVersion {
        V2 = 0x02,
        V3 = 0x03,
        V4 = 0x04,
        V5 = 0x05
    };

    enum DataMode {
        COMMAND,
        ANSWER,
        OUTPUT,
        INPUT
    };

    StdBinEncoder(ProtocolVersion version = V5, DataMode mode = INPUT);

    /*!
     * \arg binaryNav: The navigation data we want to serialize
     * \return a vector with the serialized data
     * \exception runtime_error if a parse error occurs.
     */
    std::vector<uint8_t> serialize(const Data::BinaryNav& binaryNav) const;

protected:
    const DataMode dataMode;
    const ProtocolVersion protocolVersion;
    const tSerializersSet externalDataSerializers;

    std::pair<uint32_t, std::vector<uint8_t>> processExternalData(
        const Data::BinaryNav binaryNav
    ) const;

    size_t getHeaderSize(const Data::BinaryNav& binaryNav) const;
};
} // namespace StdBinDecoder
