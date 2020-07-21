#include <gtest/gtest.h>

#include <iXblue_stdbin_decoder/data_serializers/navigation_data/acceleration_geographic_frame.h>
#include <iXblue_stdbin_decoder/data_serializers/navigation_data/acceleration_vessel_frame.h>
#include <iXblue_stdbin_decoder/data_serializers/navigation_data/acceleration_vessel_frame_deviation.h>
#include <iXblue_stdbin_decoder/data_serializers/navigation_data/ahrs_algorithm_status.h>
#include <iXblue_stdbin_decoder/data_serializers/navigation_data/ahrs_system_status.h>
#include <iXblue_stdbin_decoder/data_serializers/navigation_data/ahrs_user_status.h>
#include <iXblue_stdbin_decoder/data_serializers/navigation_data/attitude_heading.h>
#include <iXblue_stdbin_decoder/data_serializers/navigation_data/attitude_heading_deviation.h>
#include <iXblue_stdbin_decoder/data_serializers/navigation_data/attitude_quaternion.h>
#include <iXblue_stdbin_decoder/data_serializers/navigation_data/attitude_quaternion_deviation.h>
#include <iXblue_stdbin_decoder/data_serializers/navigation_data/course_speed_over_ground.h>
#include <iXblue_stdbin_decoder/data_serializers/navigation_data/current_geographic_frame.h>
#include <iXblue_stdbin_decoder/data_serializers/navigation_data/current_geographic_frame_deviation.h>
#include <iXblue_stdbin_decoder/data_serializers/navigation_data/heading_roll_pitch_rate.h>
#include <iXblue_stdbin_decoder/data_serializers/navigation_data/heave_surge_sway_speed.h>
#include <iXblue_stdbin_decoder/data_serializers/navigation_data/ins_algorithm_status.h>
#include <iXblue_stdbin_decoder/data_serializers/navigation_data/ins_system_status.h>
#include <iXblue_stdbin_decoder/data_serializers/navigation_data/ins_user_status.h>
#include <iXblue_stdbin_decoder/data_serializers/navigation_data/position.h>
#include <iXblue_stdbin_decoder/data_serializers/navigation_data/position_deviation.h>
#include <iXblue_stdbin_decoder/data_serializers/navigation_data/raw_acceleration_vessel_frame.h>
#include <iXblue_stdbin_decoder/data_serializers/navigation_data/realtime_heave_surge_sway.h>
#include <iXblue_stdbin_decoder/data_serializers/navigation_data/rotation_rate_vessel_frame.h>
#include <iXblue_stdbin_decoder/data_serializers/navigation_data/rotation_rate_vessel_frame_deviation.h>
#include <iXblue_stdbin_decoder/data_serializers/navigation_data/sensor_status.h>
#include <iXblue_stdbin_decoder/data_serializers/navigation_data/smart_heave.h>
#include <iXblue_stdbin_decoder/data_serializers/navigation_data/speed_geographic_frame.h>
#include <iXblue_stdbin_decoder/data_serializers/navigation_data/speed_geographic_frame_deviation.h>
#include <iXblue_stdbin_decoder/data_serializers/navigation_data/speed_vessel_frame.h>
#include <iXblue_stdbin_decoder/data_serializers/navigation_data/system_date.h>
#include <iXblue_stdbin_decoder/data_serializers/navigation_data/temperatures.h>

using namespace StdBinDecoder;

#define ASSERT_SERIALIZATION(serializer, member, model, expected)    \
    std::vector<uint8_t> memory(expected.size());                    \
    auto buffer = boost::asio::buffer(memory.data(), memory.size()); \
    Data::BinaryNav binaryNav;                                       \
    binaryNav.member = model;                                        \
    serializer subject;                                              \
    subject.serialize(buffer, binaryNav);                            \
    ASSERT_EQ(expected, memory);                                     \
    ASSERT_EQ(0, boost::asio::buffer_size(buffer));

TEST(DataSerializers, SerializeAttitudeAndHeading)
{
    // Heading : 1.25f(0x3fa00000), Roll : 12.55f (0x4148cccd), Pitch : -1.5f
    // (0xbfc00000)
    // clang-format off
    std::vector<uint8_t> data{
        0x3f, 0xa0, 0x00, 0x00,
        0x41, 0x48, 0xcc, 0xcd,
        0xbf, 0xc0, 0x00, 0x00
    };
    // clang-format on
    Data::AttitudeHeading attitudeHeading;
    attitudeHeading.heading_deg = 1.25;
    attitudeHeading.roll_deg = 12.55;
    attitudeHeading.pitch_deg = -1.5;

    ASSERT_SERIALIZATION(
        Serializer::AttitudeHeading,
        attitudeHeading,
        attitudeHeading,
        data
    )
}

TEST(DataSerializers, SerializeAttitudeAndHeadingDeviation)
{
    // HeadingSD : 1.25f(0x3fa00000), RollSD : 12.55f (0x4148cccd), PitchSD : -1.5f
    // (0xbfc00000)
    // clang-format off
    std::vector<uint8_t> data{
        0x3f, 0xa0, 0x00, 0x00,
        0x41, 0x48, 0xcc, 0xcd,
        0xbf, 0xc0, 0x00, 0x00
    };
    // clang-format on
    Data::AttitudeHeadingDeviation attitudeHeadingDeviation;
    attitudeHeadingDeviation.heading_stdDev_deg = 1.25;
    attitudeHeadingDeviation.roll_stdDev_deg = 12.55;
    attitudeHeadingDeviation.pitch_stdDev_deg = -1.5;

    ASSERT_SERIALIZATION(
        Serializer::AttitudeHeadingDeviation,
        attitudeHeadingDeviation,
        attitudeHeadingDeviation,
        data
    )
}

TEST(DataSerializers, SerializeRealTimeHeaveSurgeSway)
{
    // Heave without BdL : 1.25f(0x3fa00000), Heave : 12.55f (0x4148cccd), Surge : -1.5f
    // (0xbfc00000), Sway : -0.005f(0xbba3d70a)
    // clang-format off
    std::vector<uint8_t> data{
        0x3f, 0xa0, 0x00, 0x00,
        0x41, 0x48, 0xcc, 0xcd,
        0xbf, 0xc0, 0x00, 0x00,
        0xbb, 0xa3, 0xd7, 0x0a
    };
    // clang-format on
    Data::RealTimeHeaveSurgeSway rtHeaveSurgeSway;
    rtHeaveSurgeSway.rt_heave_atBdL = 12.55;
    rtHeaveSurgeSway.rt_heave_withoutBdL = 1.25;
    rtHeaveSurgeSway.rt_surge_atBdL = -1.5;
    rtHeaveSurgeSway.rt_sway_atBdL = -0.005;

    ASSERT_SERIALIZATION(
        Serializer::RealTimeHeaveSurgeSway,
        rtHeaveSurgeSway,
        rtHeaveSurgeSway,
        data
    )
}

TEST(DataSerializers, SerializeSmartHeave)
{
    // Time : 125 = 0x0000007D (in big endian)
    // Heave : 1.25f(0x3fa00000)
    // clang-format off
    std::vector<uint8_t> data{
        0x00, 0x00, 0x00, 0x7D,
        0x3f, 0xa0, 0x00, 0x00,
    };
    // clang-format on
    Data::SmartHeave smartHeave;
    smartHeave.smartHeave_m = 1.25;
    smartHeave.validityTime_100us = 125;

    ASSERT_SERIALIZATION(
        Serializer::SmartHeave,
        smartHeave,
        smartHeave,
        data
    )
}

TEST(DataSerializers, SerializeHeadingRollPitchRate)
{
    // Heading rate : -1.5f (0xbfc00000), Roll rate : 1.25f(0x3fa00000),
    // Pitch rate : 12.55f (0x4148cccd)
    // clang-format off
    std::vector<uint8_t> data{
        0xbf, 0xc0, 0x00, 0x00,
        0x3f, 0xa0, 0x00, 0x00,
        0x41, 0x48, 0xcc, 0xcd
    };
    // clang-format on
    Data::HeadingRollPitchRate headingRollPitchRate;
    headingRollPitchRate.heading_rate = -1.5;
    headingRollPitchRate.roll_rate = 1.25;
    headingRollPitchRate.pitch_rate = 12.55;

    ASSERT_SERIALIZATION(
        Serializer::HeadingRollPitchRate,
        headingRollPitchRate,
        headingRollPitchRate,
        data
    )
}

TEST(DataSerializers, SerializeRotationRateVesselFrame)
{
    // XV1 : -1.5f (0xbfc00000), XV2 : 1.25f(0x3fa00000),
    // XV3 : 12.55f (0x4148cccd)
    // clang-format off
    std::vector<uint8_t> data{
        0xbf, 0xc0, 0x00, 0x00,
        0x3f, 0xa0, 0x00, 0x00,
        0x41, 0x48, 0xcc, 0xcd
    };
    // clang-format on
    Data::RotationRateVesselFrame rotationRateVesselFrame;
    rotationRateVesselFrame.xv1_degsec = -1.5;
    rotationRateVesselFrame.xv2_degsec = 1.25;
    rotationRateVesselFrame.xv3_degsec = 12.55;

    ASSERT_SERIALIZATION(
        Serializer::RotationRateVesselFrame,
        rotationRateVesselFrame,
        rotationRateVesselFrame,
        data
    )
}

TEST(DataSerializers, SerializeAccelerationVesselFrame)
{
    // XV1 : -1.5f (0xbfc00000), XV2 : 1.25f(0x3fa00000),
    // XV3 : 12.55 (0x4148cccd)
    // clang-format off
    std::vector<uint8_t> data{
        0xbf, 0xc0, 0x00, 0x00,
        0x3f, 0xa0, 0x00, 0x00,
        0x41, 0x48, 0xcc, 0xcd
    };
    // clang-format on
    Data::AccelerationVesselFrame accelerationVesselFrame;
    accelerationVesselFrame.xv1_msec2 = -1.5;
    accelerationVesselFrame.xv2_msec2 = 1.25;
    accelerationVesselFrame.xv3_msec2 = 12.55;

    ASSERT_SERIALIZATION(
        Serializer::AccelerationVesselFrame,
        accelerationVesselFrame,
        accelerationVesselFrame,
        data
    )
}

TEST(DataSerializers, SerializePosition)
{
    // latitude : 25.68d (0x4039ae147ae147ae), longitude : -4.75d (0xc013000000000000),
    // altitude ref : 1 (0x01), altitude : 154.21f (0x431a35c3)
    // clang-format off
    std::vector<uint8_t> data{
        0x40, 0x39, 0xae, 0x14,
        0x7a, 0xe1, 0x47, 0xae,
        0xc0, 0x13, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00,
        0x01,
        0x43, 0x1a, 0x35, 0xc3
    };
    // clang-format on
    Data::Position position;
    position.latitude_deg = 25.68;
    position.longitude_deg = -4.75;
    position.altitude_ref = 1;
    position.altitude_m = 154.21;

    ASSERT_SERIALIZATION(
        Serializer::Position,
        position,
        position,
        data
    )
}

TEST(DataSerializers, SerializePositionDeviation)
{
    // NorthSD : 1.25f(0x3fa00000), EastSD : 12.55f (0x4148cccd), NEcorr : -1.5f
    // (0xbfc00000), altSD : -0.005f(0xbba3d70a)
    // clang-format off
    std::vector<uint8_t> data{
        0x3f, 0xa0, 0x00, 0x00,
        0x41, 0x48, 0xcc, 0xcd,
        0xbf, 0xc0, 0x00, 0x00,
        0xbb, 0xa3, 0xd7, 0x0a
    };
    // clang-format on
    Data::PositionDeviation positionDeviation;
    positionDeviation.altitude_stddev_m = -0.005;
    positionDeviation.east_stddev_m = 12.55;
    positionDeviation.north_east_corr = -1.5;
    positionDeviation.north_stddev_m = 1.25;

    ASSERT_SERIALIZATION(
        Serializer::PositionDeviation,
        positionDeviation,
        positionDeviation,
        data
    )
}

TEST(DataSerializers, SerializeSpeedGeographicFrame)
{
    // North : -1.5f (0xbfc00000), East : 1.25f(0x3fa00000),
    // Up : 12.55f (0x4148cccd)
    // clang-format off
    std::vector<uint8_t> data{
        0xbf, 0xc0, 0x00, 0x00,
        0x3f, 0xa0, 0x00, 0x00,
        0x41, 0x48, 0xcc, 0xcd
    };
    // clang-format on
    Data::SpeedGeographicFrame speedGeographicFrame;
    speedGeographicFrame.east_msec = 1.25;
    speedGeographicFrame.north_msec = -1.5;
    speedGeographicFrame.up_msec = 12.55;

    ASSERT_SERIALIZATION(
        Serializer::SpeedGeographicFrame,
        speedGeographicFrame,
        speedGeographicFrame,
        data
    )
}

TEST(DataSerializers, SerializeSpeedGeographicFrameDeviation)
{
    // NorthSD : -1.5f (0xbfc00000), EastSD : 1.25f(0x3fa00000),
    // UpSD : 12.55f (0x4148cccd)
    // clang-format off
    std::vector<uint8_t> data{
        0xbf, 0xc0, 0x00, 0x00,
        0x3f, 0xa0, 0x00, 0x00,
        0x41, 0x48, 0xcc, 0xcd
    };
    // clang-format on
    Data::SpeedGeographicFrameDeviation speedGeographicFrameDeviation;
    speedGeographicFrameDeviation.east_stddev_msec = 1.25;
    speedGeographicFrameDeviation.north_stddev_msec = -1.5;
    speedGeographicFrameDeviation.up_stddev_msec = 12.55;

    ASSERT_SERIALIZATION(
        Serializer::SpeedGeographicFrameDeviation,
        speedGeographicFrameDeviation,
        speedGeographicFrameDeviation,
        data
    )
}

TEST(DataSerializers, SerializeCurrentGeographicFrameDeviation)
{
    // NorthSD : -1.5f (0xbfc00000), EastSD : 1.25f(0x3fa00000)
    // clang-format off
    std::vector<uint8_t> data{
        0xbf, 0xc0, 0x00, 0x00,
        0x3f, 0xa0, 0x00, 0x00
    };
    // clang-format on
    Data::CurrentGeographicFrameDeviation currentGeographicFrameDeviation;
    currentGeographicFrameDeviation.east_stddev_msec = 1.25;
    currentGeographicFrameDeviation.north_stddev_msec = -1.5;

    ASSERT_SERIALIZATION(
        Serializer::CurrentGeographicFrameDeviation,
        currentGeographicFrameDeviation,
        currentGeographicFrameDeviation,
        data
    )
}

TEST(DataSerializers, SerializeSystemDate)
{
    // Day : 28 (0x1c), Month : 8 (0x08), Year : 2020 (0x07e4)
    // clang-format off
    std::vector<uint8_t> data{
        0x1c,
        0x08,
        0x07, 0xe4
    };
    // clang-format on
    Data::SystemDate systemDate;
    systemDate.day = 28;
    systemDate.month = 8;
    systemDate.year = 2020;

    ASSERT_SERIALIZATION(
        Serializer::SystemDate,
        systemDate,
        systemDate,
        data
    )
}

TEST(DataSerializers, SerializeSensorStatus)
{
    // Status 1 : 532 (0x00000214), Status 2 : 17 (0x00000011)
    // clang-format off
    std::vector<uint8_t> data{
        0x00, 0x00, 0x02, 0x14,
        0x00, 0x00, 0x00, 0x11
    };
    // clang-format on
    Data::SensorStatus sensorStatus;
    sensorStatus.status1 = 532;
    sensorStatus.status2 = 17;

    ASSERT_SERIALIZATION(
        Serializer::SensorStatus,
        sensorStatus,
        sensorStatus,
        data
    )
}

TEST(DataSerializers, SerializeINSAlgorithmStatus)
{
    // Status 1 : 532 (0x00000214), Status 2 : 42 (0x0000002a)
    // Status 3 : 47826 (0x0000bad2), Status 4 : 17 (0x00000011)
    // clang-format off
    std::vector<uint8_t> data{
        0x00, 0x00, 0x02, 0x14,
        0x00, 0x00, 0x00, 0x2a,
        0x00, 0x00, 0xba, 0xd2,
        0x00, 0x00, 0x00, 0x11
    };
    // clang-format on
    Data::INSAlgorithmStatus insAlgorithmStatus;
    insAlgorithmStatus.status1 = 532;
    insAlgorithmStatus.status2 = 42;
    insAlgorithmStatus.status3 = 47826;
    insAlgorithmStatus.status4 = 17;

    ASSERT_SERIALIZATION(
        Serializer::INSAlgorithmStatus,
        insAlgorithmStatus,
        insAlgorithmStatus,
        data
    )
}

TEST(DataSerializers, SerializeINSSystemStatus)
{
    // Status 1 : 532 (0x00000214), Status 2 : 42 (0x0000002a)
    // Status 3 : 47826 (0x0000bad2)
    // clang-format off
    std::vector<uint8_t> data{
        0x00, 0x00, 0x02, 0x14,
        0x00, 0x00, 0x00, 0x2a,
        0x00, 0x00, 0xba, 0xd2
    };
    // clang-format on
    Data::INSSystemStatus insSystemStatus;
    insSystemStatus.status1 = 532;
    insSystemStatus.status2 = 42;
    insSystemStatus.status3 = 47826;

    ASSERT_SERIALIZATION(
        Serializer::INSSystemStatus,
        insSystemStatus,
        insSystemStatus,
        data
    )
}

TEST(DataSerializers, SerializeINSUserStatus)
{
    // Status : 532 (0x00000214)
    // clang-format off
    std::vector<uint8_t> data{
        0x00, 0x00, 0x02, 0x14,
    };
    // clang-format on
    Data::INSUserStatus insUserStatus;
    insUserStatus.status = 532;
    
    ASSERT_SERIALIZATION(
        Serializer::INSUserStatus,
        insUserStatus,
        insUserStatus,
        data
    )
}

TEST(DataSerializers, SerializeAHRSAlgorithmStatus)
{
    // Status : 532 (0x00000214)
    // clang-format off
    std::vector<uint8_t> data{
        0x00, 0x00, 0x02, 0x14
    };
    // clang-format on
    Data::AHRSAlgorithmStatus ahrsAlgorithmStatus;
    ahrsAlgorithmStatus.status = 532;

    ASSERT_SERIALIZATION(
        Serializer::AHRSAlgorithmStatus,
        ahrsAlgorithmStatus,
        ahrsAlgorithmStatus,
        data
    )
}

TEST(DataSerializers, SerializeAHRSSystemStatus)
{
    // Status 1 : 532 (0x00000214), Status 2 : 42 (0x0000002a)
    // Status 3 : 47826 (0x0000bad2)
    // clang-format off
    std::vector<uint8_t> data{
        0x00, 0x00, 0x02, 0x14,
        0x00, 0x00, 0x00, 0x2a,
        0x00, 0x00, 0xba, 0xd2
    };
    // clang-format on
    Data::AHRSSystemStatus ahrsSystemStatus;
    ahrsSystemStatus.status1 = 532;
    ahrsSystemStatus.status2 = 42;
    ahrsSystemStatus.status3 = 47826;

    ASSERT_SERIALIZATION(
        Serializer::AHRSSystemStatus,
        ahrsSystemStatus,
        ahrsSystemStatus,
        data
    )
}

TEST(DataSerializers, SerializeAHRSUserStatus)
{
    // Status : 532 (0x00000214)
    // clang-format off
    std::vector<uint8_t> data{
        0x00, 0x00, 0x02, 0x14
    };
    // clang-format on
    Data::AHRSUserStatus ahrsUserStatus;
    ahrsUserStatus.status = 532;

    ASSERT_SERIALIZATION(
        Serializer::AHRSUserStatus,
        ahrsUserStatus,
        ahrsUserStatus,
        data
    )
}

TEST(DataSerializers, SerializeHeaveSurgeSwaySpeed)
{
    // rtHeaveSpeed : -1.5f (0xbfc00000), SurgeSpeed : 1.25f(0x3fa00000),
    // SwaySpeed : 12.55f (0x4148cccd)
    // clang-format off
    std::vector<uint8_t> data{
        0xbf, 0xc0, 0x00, 0x00,
        0x3f, 0xa0, 0x00, 0x00,
        0x41, 0x48, 0xcc, 0xcd
    };
    // clang-format on
    Data::HeaveSurgeSwaySpeed heaveSurgeSwaySpeed;
    heaveSurgeSwaySpeed.realtime_heave_speed = -1.5;
    heaveSurgeSwaySpeed.surge_speed = 1.25;
    heaveSurgeSwaySpeed.sway_speed = 12.55;

    ASSERT_SERIALIZATION(
        Serializer::HeaveSurgeSwaySpeed,
        heaveSurgeSwaySpeed,
        heaveSurgeSwaySpeed,
        data
    )
}

TEST(DataSerializers, SerializeSpeedVesselFrame)
{
    // xv1 : -1.5f (0xbfc00000), xv2 : 1.25f(0x3fa00000), xv3 : 12.55f (0x4148cccd)
    // clang-format off
    std::vector<uint8_t> data{
        0xbf, 0xc0, 0x00, 0x00,
        0x3f, 0xa0, 0x00, 0x00,
        0x41, 0x48, 0xcc, 0xcd
    };
    // clang-format on
    Data::SpeedVesselFrame speedVesselFrame;
    speedVesselFrame.xv1_msec = -1.5;
    speedVesselFrame.xv2_msec = 1.25;
    speedVesselFrame.xv3_msec = 12.55;

    ASSERT_SERIALIZATION(
        Serializer::SpeedVesselFrame,
        speedVesselFrame,
        speedVesselFrame,
        data
    )
}

TEST(DataSerializers, SerializeAccelerationGeographicFrame)
{
    // north : -1.5f (0xbfc00000), east : 1.25f(0x3fa00000), up : 12.55f (0x4148cccd)
    // clang-format off
    std::vector<uint8_t> data{
        0xbf, 0xc0, 0x00, 0x00,
        0x3f, 0xa0, 0x00, 0x00,
        0x41, 0x48, 0xcc, 0xcd
    };
    // clang-format on
    Data::AccelerationGeographicFrame accelerationGeographicFrame;
    accelerationGeographicFrame.east_msec2 = 1.25;
    accelerationGeographicFrame.north_msec2 = -1.5;
    accelerationGeographicFrame.up_msec2 = 12.55;

    ASSERT_SERIALIZATION(
        Serializer::AccelerationGeographicFrame,
        accelerationGeographicFrame,
        accelerationGeographicFrame,
        data
    )
}

TEST(DataSerializers, SerializeCourseSpeedoverGrounde)
{
    // course : -1.5f (0xbfc00000), speed : 1.25f(0x3fa00000)
    // clang-format off
    std::vector<uint8_t> data{
        0xbf, 0xc0, 0x00, 0x00,
        0x3f, 0xa0, 0x00, 0x00
    };
    // clang-format on
    Data::CourseSpeedoverGround courseSpeedoverGround;
    courseSpeedoverGround.course_over_ground = -1.5;
    courseSpeedoverGround.speed_over_ground = 1.25;

    ASSERT_SERIALIZATION(
        Serializer::CourseSpeedoverGround,
        courseSpeedoverGround,
        courseSpeedoverGround,
        data
    )
}

TEST(DataSerializers, SerializeTemperatures)
{
    // FOG : -1.5f (0xbfc00000), Acc : 1.25f(0x3fa00000), Board : 12.55f (0x4148cccd)
    // clang-format off
    std::vector<uint8_t> data{
        0xbf, 0xc0, 0x00, 0x00,
        0x3f, 0xa0, 0x00, 0x00,
        0x41, 0x48, 0xcc, 0xcd
    };
    // clang-format on
    Data::Temperatures temperatures;
    temperatures.board_temperature = 12.55;
    temperatures.mean_temp_acc = 1.25;
    temperatures.mean_temp_fog = -1.5;

    ASSERT_SERIALIZATION(
        Serializer::Temperatures,
        temperatures,
        temperatures,
        data
    )
}

TEST(DataSerializers, SerializeAttitudeQuaternion)
{
    // Q0 : 1.25f (0x3fa00000), Q1 : 12.55f (0x4148cccd), Q2 : -1.5f (0xbfc00000), Q3 :
    // -0.005f (0xbba3d70a)
    // clang-format off
    std::vector<uint8_t> data{
        0x3f, 0xa0, 0x00, 0x00,
        0x41, 0x48, 0xcc, 0xcd,
        0xbf, 0xc0, 0x00, 0x00,
        0xbb, 0xa3, 0xd7, 0x0a
    };
    Data::AttitudeQuaternion attitudeQuaternion;
    attitudeQuaternion.q0 = 1.25;
    attitudeQuaternion.q1 = 12.55;
    attitudeQuaternion.q2 = -1.5;
    attitudeQuaternion.q3 = -0.005;

    // clang-format on
    ASSERT_SERIALIZATION(
        Serializer::AttitudeQuaternion,
        attitudeQuaternion,
        attitudeQuaternion,
        data
    )
}

TEST(DataSerializers, SerializeAttitudeQuaternionDeviation)
{
    // xi1 : -1.5f (0xbfc00000), xi2 : 1.25f(0x3fa00000), xi3 : 12.55f (0x4148cccd)
    // clang-format off
    std::vector<uint8_t> data{
        0xbf, 0xc0, 0x00, 0x00,
        0x3f, 0xa0, 0x00, 0x00,
        0x41, 0x48, 0xcc, 0xcd
    };
    // clang-format on
    Data::AttitudeQuaternionDeviation attitudeQuaternionDeviation;
    attitudeQuaternionDeviation.quat_stddev_xi1 = -1.5;
    attitudeQuaternionDeviation.quat_stddev_xi2 = 1.25;
    attitudeQuaternionDeviation.quat_stddev_xi3 = 12.55;

    ASSERT_SERIALIZATION(
        Serializer::AttitudeQuaternionDeviation,
        attitudeQuaternionDeviation,
        attitudeQuaternionDeviation,
        data
    )
}

TEST(DataSerializers, SerializeRawAccelerationVesselFrame)
{
    // xv1 : -1.5f (0xbfc00000), xv2 : 1.25f(0x3fa00000), xv3 : 12.55f (0x4148cccd)
    // clang-format off
    std::vector<uint8_t> data{
        0xbf, 0xc0, 0x00, 0x00,
        0x3f, 0xa0, 0x00, 0x00,
        0x41, 0x48, 0xcc, 0xcd
    };
    // clang-format on
    Data::RawAccelerationVesselFrame rawAccelerationVesselFrame;
    rawAccelerationVesselFrame.xv1_msec2 = -1.5;
    rawAccelerationVesselFrame.xv2_msec2 = 1.25;
    rawAccelerationVesselFrame.xv3_msec2 = 12.55;

    ASSERT_SERIALIZATION(
        Serializer::RawAccelerationVesselFrame,
        rawAccelerationVesselFrame,
        rawAccelerationVesselFrame,
        data
    )
}

TEST(DataSerializers, SerializeAccelerationVesselFrameDeviation)
{
    // xv1SD : -1.5f (0xbfc00000), xv2SD : 1.25f(0x3fa00000), xv3SD : 12.55f
    // (0x4148cccd)
    // clang-format off
    std::vector<uint8_t> data{
        0xbf, 0xc0, 0x00, 0x00,
        0x3f, 0xa0, 0x00, 0x00,
        0x41, 0x48, 0xcc, 0xcd
    };
    // clang-format on
    Data::AccelerationVesselFrameDeviation accelerationVesselFrameDeviation;
    accelerationVesselFrameDeviation.xv1_stddev_msec2 = -1.5;
    accelerationVesselFrameDeviation.xv2_stddev_msec2 = 1.25;
    accelerationVesselFrameDeviation.xv3_stddev_msec2 = 12.55;

    ASSERT_SERIALIZATION(
        Serializer::AccelerationVesselFrameDeviation,
        accelerationVesselFrameDeviation,
        accelerationVesselFrameDeviation,
        data
    )
}

TEST(DataSerializers, SerializeRotationRateVesselFrameDeviation)
{
    // xv1SD : -1.5f (0xbfc00000), xv2SD : 1.25f(0x3fa00000), xv3SD : 12.55f
    // (0x4148cccd)
    // clang-format off
    std::vector<uint8_t> data{
        0xbf, 0xc0, 0x00, 0x00,
        0x3f, 0xa0, 0x00, 0x00,
        0x41, 0x48, 0xcc, 0xcd
    };
    // clang-format on
    Data::RotationRateVesselFrameDeviation rotationRateVesselFrameDeviation;
    rotationRateVesselFrameDeviation.xv1_stddev_degsec = -1.5;
    rotationRateVesselFrameDeviation.xv2_stddev_degsec = 1.25;
    rotationRateVesselFrameDeviation.xv3_stddev_degsec = 12.55;

    ASSERT_SERIALIZATION(
        Serializer::RotationRateVesselFrameDeviation,
        rotationRateVesselFrameDeviation,
        rotationRateVesselFrameDeviation,
        data
    )
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
