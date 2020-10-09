#pragma once
#include <inttypes.h>

namespace ixblue_stdbin_decoder
{
namespace Data
{

struct INSAlgorithmStatus
{
    enum Status1
    {
        NAVIGATION,
        ALIGNMENT,
        FINE_ALIGNMENT,
        DEAD_RECKONING,
        GPS_ALTITUDE,
        DEPTHSENSOR_ALTITUDE,
        ZERO_ALTITUDE,
        HYDRO_ALTITUDE,
        LOG_RECEIVED,
        LOG_VALID,
        LOG_WAITING,
        LOG_REJECTED,
        GPS_RECEIVED,
        GPS_VALID,
        GPS_WAITING,
        GPS_REJECTED,
        USBL_RECEIVED,
        USBL_VALID,
        USBL_REJECTED,
        DEPTH_RECEIVED,
        DEPTH_VALID,
        DEPTH_WAITING,
        DEPTH_REJECTED,
        LBL_RECEIVED,
        LBL_VALID,
        LBL_WAITING,
        LBL_REJECTED,
        ALTITUDE_SATURATION,
        SPEED_SATURATION,
        INTERPOLATION_MISSED,
        HEAVE_INITIALISATION
    };

    enum Status2
    {
        WATERTRACK_RECEIVED,
        WATERTRACK_VALID,
        WATERTRACK_WAITING,
        WATERTRACK_REJECTED,
        GPS2_RECEIVED,
        GPS2_VALID,
        GPS2_WAITING,
        GPS2_REJECTED,
        // 8-11 reserved
        ALTITUDE_RECEIVED = 12,
        ALTITUDE_VALID,
        ALTITUDE_WAITING,
        ALTITUDE_REJECTED,
        ZUPT_ACTIVATED,
        ZUPT_VALID,
        RO_ZUPT_ACTIVATED,
        RO_ZUPT_VALID,
        // 20-21 reserved
        FAST_ALIGNEMENT = 22,
        EMULATION_MODE,
        EMLOG_RECEIVED,
        EMLOG_VALID,
        EMLOG_WAITING,
        EMLOG_REJECTED,
        MANUALGPS_RECEIVED,
        MANUALGPS_VALID,
        MANUALGPS_WAITING,
        MANUALGPS_REJECTED
    };

    enum Status3
    {
        SVL_RECEIVED,
        SVL_VALID,
        SVL_WAITING,
        SVL_REJECTED,
        EMLOG2_RECEIVED,
        EMLOG2_VALID,
        EMLOG2_WAITING,
        EMLOG2_REJECTED,
        USBL2_RECEIVED,
        USBL2_VALID,
        USBL2_WAITING,
        USBL2_REJECTED,
        USBL3_RECEIVED,
        USBL3_VALID,
        USBL3_WAITING,
        USBL3_REJECTED,
        // 16 reserved
        CALCHK = 17,
        RESTORE_ATTITUDE_FAILED,
        REL_SPD_ZUPT_ACTIVATED,
        REL_SPD_ZUPT_VALID,
        EXT_SENSOR_OUTDATED,
        SENSOR_USED_BEFORE_CALIB,
        RESTORE_ATTITUDE_REJECTED,
        // 24-26 reserved
        POLAR_VALIDITY = 27,
        FIRM_INCOMPATIBLES,
        IMO_ALIGNMENT,
        OPTIMAL_ALIGNMENT,
        STRATEGIC_ALIGNMENT,
    };

    enum Status4
    {
        LOG2_RECEIVED,
        LOG2_VALID,
        LOG2_WAITING,
        LOG2_REJECTED,
        WATERTRACK2_RECEIVED,
        WATERTRACK2_VALID,
        WATERTRACK2_WAITING,
        WATERTRACK2_REJECTED,
        DVL_DIST_TRAVELLED_VALID,
        DVL_CALIBRATION_NONE,
        DVL_ROUGH_CALIBRATION,
        DVL_FINE_CALIBRATION,
        DVL_CHECK_CALIBRATION,
        MANUAL_ATT_RECEIVED,
        MANUAL_ATT_VALID,
        MANUAL_ATT_WAITING,
        MANUAL_ATT_REJECTED,
        FIXED_HEADING,
        DEGRADED_MODE,
        VTG_RECEIVED,
        VTG_VALID,
        VTG_WAITING,
        VTG_REJECTED,
        VTG2_RECEIVED,
        VTG2_VALID,
        VTG2_WAITING,
        VTG2_REJECTED,
        ALIX_SYST_SATURATION,
        CINT_FLASH_MEMORY_WRERR,
        CINT_FLASH_MEMORY_ERERR,
        ODO_CALIBRATION_DONE,
        INCONSISTENT_SENSOR_DATA
    };

    enum Status5
    {
        NAV_MODE_NONE,
        TRAVELING_MODE,
        FIRING_MODE,
        FIRING_ON_MOVE,
        AERO_TRANSPORTATION,
        // 5-15 reserved
        MANUAL_ALTITUD_VALID = 16,
        MANUAL_ALTITUDE_REJECTED,
        SHOCK_ACTIVATED,
        SHOCK_DETECTED,
        TR_ZUPT_ACTIVATED,
        TR_ZUPT_VALID,
        PO_ZUPT_ACTIVATED,
        PO_ZUPT_VALID,
        RELATIVE_ATTITUDE_DEGRADED,
        CDSP_FLASH_MEMORY_WRERR,
        CDSP_FLASH_MEMORY_ERERR,
        CINT_FLASH_MEMORY_VIRGIN,
        CDSP_FLASH_MEMORY_VIRGIN,
        CINT_FLASH_MEMORY_ERROR,
        CDSP_FLASH_MEMORY_ERROR
    };

    enum Status6
    {
        // 0-31 reserved
    };

    uint32_t status1 = 0;
    uint32_t status2 = 0;
    uint32_t status3 = 0;
    uint32_t status4 = 0;
    uint32_t status5 = 0;
    uint32_t status6 = 0;
};

} // namespace Data
} // namespace ixblue_stdbin_decoder
