#pragma once
#include <inttypes.h>

namespace ixblue_stdbin_decoder
{
namespace Data
{
// TODO : For all status data, we will need to allow user to query a textual
// representation of a status.
struct INSSystemStatus
{
    enum Status1
    {
        SERIAL_IN_R_ERR,
        INPUT_A_ERR,
        INPUT_B_ERR,
        INPUT_C_ERR,
        INPUT_D_ERR,
        INPUT_E_ERR,
        // 6-7 reserved
        INPUT_R_ACTIVITY = 8,
        INPUT_A_ACTIVITY,
        INPUT_B_ACTIVITY,
        INPUT_C_ACTIVITY,
        INPUT_D_ACTIVITY,
        INPUT_E_ACTIVITY,
        // 14-15 reserved
        OUTPUT_R_FULL = 16,
        OUTPUT_A_FULL,
        OUTPUT_B_FULL,
        OUTPUT_C_FULL,
        OUTPUT_D_FULL,
        OUTPUT_E_FULL,
        ETHERNET_PORT_FULL,
        // 23 reserved
        INTERNAL_TIME_USED = 24,
        // 25 reserved
        ETHERNET_PORT_ACTIVITY = 26,
        PULSE_IN_A_ACTIVITY,
        PULSE_IN_B_ACTIVITY,
        // 29-31 reserved
    };

    enum Status2
    {
        // 0-1 reserved
        GPS_DETECTED = 2,
        // 3-7 reserved
        DMI_DETECTED = 8,
        UTC_DETECTED,
        ALTITUDE_DETECTED,
        PPS_DETECTED,
        ZUPT_MODE_ACTIVATED,
        // 13 reserved
        MANUAL_GPS_DETECTED = 14,
        // 15-20 reserved
        WAIT_FOR_POSITION = 21,
        // 22-23 reserved
        INTERNAL_LOG = 24,
        // 25-26 reserved
        MPC_OVERLOAD = 27,
        POWER_SUPPLY_FAILURE,
        RD_MODE,
        CONFIGURATION_SAVED,
        // 31 reserved
    };

    enum Status3
    {
        // 0-12 reserved
        VTG1_DETECTED = 13,
        // 14 reserved
        MANUAL_ATT_DETECTED = 15,
        INPUT_CAN_ERR,
        INPUT_CAN_ACTIVITY,
        // 18-31 reserved
    };

    uint32_t status1 = 0;
    uint32_t status2 = 0;
    uint32_t status3 = 0;
};

} // namespace Data
} // namespace ixblue_stdbin_decoder
