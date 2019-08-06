#pragma once
namespace StdBinDecoder
{
namespace Data
{

/*! Course and speed over ground at primary lever arm */
struct CourseSpeedoverGround
{
    float course_over_ground; /*! deg - [0° - 360°[ */
    float speed_over_ground;  /*! m/s */
};
} // namespace Data
} // namespace StdBinDecoder