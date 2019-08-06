#pragma once

#include "iXblue_stdbin_decoder/data_models/navigation_data/course_speed_over_ground.h"
#include "iXblue_stdbin_decoder/memory_block_parser.h"

namespace StdBinDecoder
{
namespace Parser
{
class CourseSpeedoverGround : public MemoryBlockParser
{
public:
    CourseSpeedoverGround() : MemoryBlockParser(24, 8) {}
    void parse(boost::asio::mutable_buffer& buffer,
               Data::BinaryNav& outBinaryNav) override
    {
        Data::CourseSpeedoverGround res;
        buffer >> res.course_over_ground >> res.speed_over_ground;
        outBinaryNav.courseSpeedoverGround = res;
    }
};
} // namespace Parser
} // namespace StdBinDecoder