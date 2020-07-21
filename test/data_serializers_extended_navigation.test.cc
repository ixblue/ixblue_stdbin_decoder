#include <gtest/gtest.h>

#include <iXblue_stdbin_decoder/data_serializers/extended_navigation_data/raw_rotation_rate_vessel_frame.h>
#include <iXblue_stdbin_decoder/data_serializers/extended_navigation_data/rotation_acceleration_vessel_frame.h>
#include <iXblue_stdbin_decoder/data_serializers/extended_navigation_data/rotation_acceleration_vessel_frame_deviation.h>
#include <iXblue_stdbin_decoder/data_serializers/extended_navigation_data/vehicle_attitude_heading.h>
#include <iXblue_stdbin_decoder/data_serializers/extended_navigation_data/vehicle_attitude_heading_deviation.h>
#include <iXblue_stdbin_decoder/data_serializers/extended_navigation_data/vehicle_position.h>
#include <iXblue_stdbin_decoder/data_serializers/extended_navigation_data/vehicle_position_deviation.h>

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

TEST(DataSerializers, SerializeRotationAccelerationVesselFrame)
{
    // xv1 : -1.5f (0xbfc00000), xv2 : 1.25f(0x3fa00000), xv3 : 12.55f
    // (0x4148cccd)
    // clang-format off
    std::vector<uint8_t> data{
        0xbf, 0xc0, 0x00, 0x00,
        0x3f, 0xa0, 0x00, 0x00,
        0x41, 0x48, 0xcc, 0xcd
    };
    // clang-format on
    Data::RotationAccelerationVesselFrame rotationAccelerationVesselFrame;
    rotationAccelerationVesselFrame.xv1_degsec2 = -1.5;
    rotationAccelerationVesselFrame.xv2_degsec2 = 1.25;
    rotationAccelerationVesselFrame.xv3_degsec2 = 12.55;

    ASSERT_SERIALIZATION(
        Serializer::RotationAccelerationVesselFrame,
        rotationAccelerationVesselFrame,
        rotationAccelerationVesselFrame,
        data
    )
}

TEST(DataSerializers, SerializeRotationAccelerationVesselFrameDeviation)
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
    Data::RotationAccelerationVesselFrameDeviation
        rotationAccelerationVesselFrameDeviation;

    rotationAccelerationVesselFrameDeviation.xv1_stddev_degsec2 = -1.5;
    rotationAccelerationVesselFrameDeviation.xv2_stddev_degsec2 = 1.25;
    rotationAccelerationVesselFrameDeviation.xv3_stddev_degsec2 = 12.55;

    ASSERT_SERIALIZATION(
        Serializer::RotationAccelerationVesselFrameDeviation,
        rotationAccelerationVesselFrameDeviation,
        rotationAccelerationVesselFrameDeviation,
        data
    )
}

TEST(DataSerializers, SerializeRawRotationRateVesselFrame)
{
    // xv1 : -1.5f (0xbfc00000), xv2 : 1.25f(0x3fa00000), xv3 : 12.55f
    // (0x4148cccd)
    // clang-format off
    std::vector<uint8_t> data{
        0xbf, 0xc0, 0x00, 0x00,
        0x3f, 0xa0, 0x00, 0x00,
        0x41, 0x48, 0xcc, 0xcd
    };
    // clang-format on
    Data::RawRotationRateVesselFrame rawRotationRateVesselFrame;
    rawRotationRateVesselFrame.xv1_degsec = -1.5;
    rawRotationRateVesselFrame.xv2_degsec = 1.25;
    rawRotationRateVesselFrame.xv3_degsec = 12.55;

    ASSERT_SERIALIZATION(
        Serializer::RawRotationRateVesselFrame,
        rawRotationRateVesselFrame,
        rawRotationRateVesselFrame,
        data
    )
}

TEST(DataSerializers, SerializeVehicleAttitudeHeading)
{
    // xv1 : -1.5f (0xbfc00000), xv2 : 1.25f(0x3fa00000), xv3 : 12.55f
    // (0x4148cccd)
    // clang-format off
    std::vector<uint8_t> data{
        0xbf, 0xc0, 0x00, 0x00,
        0x3f, 0xa0, 0x00, 0x00,
        0x41, 0x48, 0xcc, 0xcd
    };
    // clang-format on
    Data::VehicleAttitudeHeading vehicleAttitudeHeading;
    vehicleAttitudeHeading.heading_deg = -1.5;
    vehicleAttitudeHeading.pitch_deg = 12.55;
    vehicleAttitudeHeading.roll_deg = 1.25;

    ASSERT_SERIALIZATION(
        Serializer::VehicleAttitudeHeading,
        vehicleAttitudeHeading,
        vehicleAttitudeHeading,
        data
    )
}

TEST(DataSerializers, SerializeVehicleAttitudeHeadingDeviation)
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
    Data::VehicleAttitudeHeadingDeviation vehicleAttitudeHeadingDeviation;
    vehicleAttitudeHeadingDeviation.heading_stddev_deg = -1.5;
    vehicleAttitudeHeadingDeviation.pitch_stddev_deg = 12.55;
    vehicleAttitudeHeadingDeviation.roll_stddev_deg = 1.25;

    ASSERT_SERIALIZATION(
        Serializer::VehicleAttitudeHeadingDeviation,
        vehicleAttitudeHeadingDeviation,
        vehicleAttitudeHeadingDeviation,
        data
    )
}

TEST(DataSerializers, SerializeVehiclePosition)
{
    // latitude : 25.68d (0x4039ae147ae147ae), longitude : -4.75d (0xc013000000000000),
    // altitude ref : 1 (0x01), altitude : 154.21f (0x43 1a 35 c3)
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
    Data::VehiclePosition vehiclePosition;
    vehiclePosition.altitude_m = 154.21;
    vehiclePosition.altitude_ref = 1;
    vehiclePosition.latitude_deg = 25.68;
    vehiclePosition.longitude_deg = -4.75;

    ASSERT_SERIALIZATION(
        Serializer::VehiclePosition,
        vehiclePosition,
        vehiclePosition,
        data
    )
}

TEST(DataSerializers, SerializeVehiclePositionDeviation)
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
    Data::VehiclePositionDeviation vehiclePositionDeviation;
    vehiclePositionDeviation.altitude_stddev_m = -0.005;
    vehiclePositionDeviation.east_stddev_m = 12.55;
    vehiclePositionDeviation.north_east_corr = -1.5;
    vehiclePositionDeviation.north_stddev_m = 1.25;

    ASSERT_SERIALIZATION(
        Serializer::VehiclePositionDeviation,
        vehiclePositionDeviation,
        vehiclePositionDeviation,
        data
    )
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}