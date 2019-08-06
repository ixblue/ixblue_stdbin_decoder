#pragma once

#include <boost/optional.hpp>

namespace StdBinDecoder
{
namespace Data
{
struct NavHeader
{
    uint8_t protocolVersion;
    uint32_t navigationBitMask;
    boost::optional<uint32_t> extendedNavigationBitMask;
    uint32_t externalSensorBitMask;
    uint16_t telegramSize;
    uint32_t navigationDataValidityTime_100us;
};
} // namespace Data
} // namespace StdBinDecoder
