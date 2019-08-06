#pragma once
namespace StdBinDecoder
{
namespace Data
{

/*! Average temperature data */
struct Temperatures
{
    float mean_temp_fog;     /*! °Celsuis - Average of each fog temperature */
    float mean_temp_acc;     /*! °Celsuis - Average of each accelerometers temperature */
    float board_temperature; /*! °Celsuis */
};
} // namespace Data
} // namespace StdBinDecoder