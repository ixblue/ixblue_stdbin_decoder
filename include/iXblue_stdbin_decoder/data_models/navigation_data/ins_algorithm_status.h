#pragma once
#include <inttypes.h>

namespace StdBinDecoder
{
namespace Data
{

struct INSAlgorithmStatus
{
    uint32_t status1;
    uint32_t status2;
    uint32_t status3;
    uint32_t status4;
};
} // namespace Data
} // namespace StdBinDecoder