#include <array>
#include <gtest/gtest.h>

#include <iXblue_stdbin_decoder/data_serializers/external_data/depth.h>
#include <iXblue_stdbin_decoder/data_serializers/external_data/dmi.h>
#include <iXblue_stdbin_decoder/data_serializers/external_data/dvl_ground_speed.h>
#include <iXblue_stdbin_decoder/data_serializers/external_data/dvl_water_speed.h>
#include <iXblue_stdbin_decoder/data_serializers/external_data/emlog.h>
#include <iXblue_stdbin_decoder/data_serializers/external_data/eventmarker.h>
#include <iXblue_stdbin_decoder/data_serializers/external_data/gnss.h>
#include <iXblue_stdbin_decoder/data_serializers/external_data/lbl.h>
#include <iXblue_stdbin_decoder/data_serializers/external_data/logbook.h>
#include <iXblue_stdbin_decoder/data_serializers/external_data/sound_velocity.h>
#include <iXblue_stdbin_decoder/data_serializers/external_data/turret_angles.h>
#include <iXblue_stdbin_decoder/data_serializers/external_data/usbl.h>
#include <iXblue_stdbin_decoder/data_serializers/external_data/utc.h>
#include <iXblue_stdbin_decoder/data_serializers/external_data/vtg.h>

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

TEST(DataSerializers, SerializeUtc)
{
    // Validity Time : 254 (0x000000fe), source : 24 (0x18)
    // clang-format off
    std::vector<uint8_t> data{
        0x00, 0x00, 0x00, 0xfe,
        0x18
    };
    // clang-format on
    Data::Utc utc;
    utc.source = 24;
    utc.validityTime_100us = 254;

    ASSERT_SERIALIZATION(
        Serializer::Utc,
        utc,
        utc,
        data
    )
}

TEST(DataSerializers, SerializeGnss1)
{
    // Validity Time : 254 (0x000000fe), GNSS Id : 24 (0x18), GNSS Quality : 28
    // (0x1c), latitude : 25.68d (0x4039ae147ae147ae), longitude : -4.75d
    // (0xc013000000000000), altitude : 154.21f (0x431a35c3), latitudeSD : 1.25f(
    // 0x3fa00000 ), longitudeSD : 12.55f (0x4148cccd), altSD : -1.5f (0xbfc00000),
    // latlonCOR : -0.005f (0xbba3d70a), geoidalSep : 8.562 (0x4108fdf4)
    // clang-format off
    std::vector<uint8_t> data{
        0x00, 0x00, 0x00, 0xfe,
        0x18,
        0x1c,
        0x40, 0x39, 0xae, 0x14,
        0x7a, 0xe1, 0x47, 0xae,
        0xc0, 0x13, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00,
        0x43, 0x1a, 0x35, 0xc3,
        0x3f, 0xa0, 0x00, 0x00,
        0x41, 0x48, 0xcc, 0xcd,
        0xbf, 0xc0, 0x00, 0x00,
        0xbb, 0xa3, 0xd7, 0x0a,
        0x41, 0x08, 0xfd, 0xf4
    };
    // clang-format on
    Data::Gnss gnss1;
    gnss1.altitude_m = 154.21;
    gnss1.altitude_stddev_m = -1.5;
    gnss1.geoidal_separation_m = 8.562;
    gnss1.gnss_id = 24;
    gnss1.gnss_quality = 28;
    gnss1.lat_lon_stddev_m2 = -0.005;
    gnss1.latitude_deg = 25.68;
    gnss1.latitude_stddev_m = 1.25;
    gnss1.longitude_deg = -4.75;
    gnss1.longitude_stddev_m = 12.55;
    gnss1.validityTime_100us = 254;

    ASSERT_SERIALIZATION(
        Serializer::Gnss1,
        gnss1,
        gnss1,
        data
    )
}

TEST(DataSerializers, SerializeGnss2)
{
    // Validity Time : 254 (0x000000fe), GNSS Id : 24 (0x18), GNSS Quality : 28
    // (0x1c), latitude : -4.75d (0xc013000000000000), longitude : 25.68d
    // (0x4039ae147ae147ae), altitude : 154.21f (0x431a35c3), latitudeSD : -1.5f
    // (0xbfc00000), longitudeSD : 12.55f (0x4148cccd), altSD : 1.25f(0x3fa00000),
    // latlonCOR : -0.005f (0xbba3d70a), geoidalSep : 8.562 (0x4108fdf4)
    // clang-format off
    std::vector<uint8_t> data{
        0x00, 0x00, 0x00, 0xfe,
        0x18,
        0x1c,
        0xc0, 0x13, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00,
        0x40, 0x39, 0xae, 0x14,
        0x7a, 0xe1, 0x47, 0xae,
        0x43, 0x1a, 0x35, 0xc3,
        0xbf, 0xc0, 0x00, 0x00,
        0x41, 0x48, 0xcc, 0xcd,
        0x3f, 0xa0, 0x00, 0x00,
        0xbb, 0xa3, 0xd7, 0x0a,
        0x41, 0x08, 0xfd, 0xf4
    };
    // clang-format on
    Data::Gnss gnss2;
    gnss2.altitude_m = 154.21;
    gnss2.altitude_stddev_m = 1.25;
    gnss2.geoidal_separation_m = 8.562;
    gnss2.gnss_id = 24;
    gnss2.gnss_quality = 28;
    gnss2.lat_lon_stddev_m2 = -0.005;
    gnss2.latitude_deg = -4.75;
    gnss2.latitude_stddev_m = -1.5;
    gnss2.longitude_deg = 25.68;
    gnss2.longitude_stddev_m = 12.55;
    gnss2.validityTime_100us = 254;

    ASSERT_SERIALIZATION(
        Serializer::Gnss2,
        gnss2,
        gnss2,
        data
    )
}

TEST(DataSerializers, SerializeGnssManual)
{
    // Validity Time : 58 (0x0000003a), GNSS Id : 4 (0x04), GNSS Quality : 28
    // (0x1c), latitude : 25.68d (0x4039ae147ae147ae), longitude : -4.75d
    // (0xc013000000000000), altitude : 154.21f (0x431a35c3), latitudeSD : 1.25f(
    // 0x3fa00000 ), longitudeSD : 12.55f (0x4148cccd), altSD : -1.5f (0xbfc00000),
    // latlonCOR : -0.005f (0xbba3d70a), geoidalSep : 8.562 (0x4108fdf4)
    // clang-format off
    std::vector<uint8_t> data{
        0x00, 0x00, 0x00, 0x3a,
        0x04,
        0x1c,
        0x40, 0x39, 0xae, 0x14,
        0x7a, 0xe1, 0x47, 0xae,
        0xc0, 0x13, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00,
        0x43, 0x1a, 0x35, 0xc3,
        0x3f, 0xa0, 0x00, 0x00,
        0x41, 0x48, 0xcc, 0xcd,
        0xbf, 0xc0, 0x00, 0x00,
        0xbb, 0xa3, 0xd7, 0x0a,
        0x41, 0x08, 0xfd, 0xf4
    };
    // clang-format on
    Data::Gnss gnssManual;
    gnssManual.altitude_m = 154.21;
    gnssManual.altitude_stddev_m = -1.5;
    gnssManual.geoidal_separation_m = 8.562;
    gnssManual.gnss_id = 4;
    gnssManual.gnss_quality = 28;
    gnssManual.lat_lon_stddev_m2 = -0.005;
    gnssManual.latitude_deg = 25.68;
    gnssManual.latitude_stddev_m = 1.25;
    gnssManual.longitude_deg = -4.75;
    gnssManual.longitude_stddev_m = 12.55;
    gnssManual.validityTime_100us = 58;

    ASSERT_SERIALIZATION(
        Serializer::GnssManual,
        gnssManual,
        gnssManual,
        data
    )
}

TEST(DataSerializers, SerializeEmlog1)
{
    // Validity Time : 254 (0x000000fe), EMLOG Id : 24 (0x18),
    // Waterspeed : 154.21f (0x431a35c3), WaterspeedSD : 1.25f(0x3fa00000)
    // clang-format off
    std::vector<uint8_t> data{
        0x00, 0x00, 0x00, 0xfe,
        0x18,
        0x43, 0x1a, 0x35, 0xc3,
        0x3f, 0xa0, 0x00, 0x00
    };
    Data::Emlog emlog1;
    emlog1.emlog_id = 24;
    emlog1.validityTime_100us = 254;
    emlog1.xv1_speed_stddev_ms = 1.25;
    emlog1.xv1_waterSpeed_ms = 154.21;

    ASSERT_SERIALIZATION(
        Serializer::Emlog1,
        emlog1,
        emlog1,
        data
    )
}

TEST(DataSerializers, SerializeEmlog2)
{
    // Validity Time : 58 (0x0000003a), EMLOG Id : 4 (0x04),
    // Waterspeed : 1.25f(0x3fa00000), WaterspeedSD : 12.55f (0x4148cccd)
    // clang-format off
    std::vector<uint8_t> data{
        0x00, 0x00, 0x00, 0x3a,
        0x04,
        0x3f, 0xa0, 0x00, 0x00,
        0x41, 0x48, 0xcc, 0xcd
    };
    Data::Emlog emlog2;
    emlog2.emlog_id = 4;
    emlog2.validityTime_100us = 58;
    emlog2.xv1_speed_stddev_ms = 12.55;
    emlog2.xv1_waterSpeed_ms = 1.25;

    ASSERT_SERIALIZATION(
        Serializer::Emlog2,
        emlog2,
        emlog2,
        data
    )
}

TEST(DataSerializers, SerializeUsbl1)
{
    // Validity Time : 254 (0x000000fe), USBL Id : 24 (0x18), Beacon id : abcdefgh
    // (0x6162636465666768), latitude : 25.68d (0x4039ae147ae147ae), longitude : -4.75d
    // (0xc013000000000000), altitude : 154.21f (0x431a35c3), latitudeSD : 1.25f(
    // 0x3fa00000 ), longitudeSD : 12.55f (0x4148cccd), latlonCOR : -0.005f (0xbba3d70a),
    // altSD : -1.5f (0xbfc00000)
    // clang-format off
    std::vector<uint8_t> data{
        0x00, 0x00, 0x00, 0xfe,
        0x18,
        0x61, 0x62, 0x63, 0x64,
        0x65, 0x66, 0x67, 0x68,
        0x40, 0x39, 0xae, 0x14,
        0x7a, 0xe1, 0x47, 0xae,
        0xc0, 0x13, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00,
        0x43, 0x1a, 0x35, 0xc3,
        0x3f, 0xa0, 0x00, 0x00,
        0x41, 0x48, 0xcc, 0xcd,
        0xbb, 0xa3, 0xd7, 0x0a,
        0xbf, 0xc0, 0x00, 0x00
    };
    Data::Usbl usbl1;
    usbl1.altitude_m = 154.21;
    usbl1.altitude_stddev_m = -1.5;
    usbl1.beacon_id = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h' };
    usbl1.east_stddev_m = 12.55;
    usbl1.lat_lon_cov_m2 = -0.005;
    usbl1.latitude_deg = 25.68;
    usbl1.longitude_deg = -4.75;
    usbl1.north_stddev_m = 1.25;
    usbl1.usbl_id = 24;
    usbl1.validityTime_100us = 254;

    ASSERT_SERIALIZATION(
        Serializer::Usbl1,
        usbl1,
        usbl1,
        data
    )
}

TEST(DataSerializers, SerializeUsbl2)
{
    // Validity Time : 58 (0x0000003a), USBL Id : 4 (0x04), Beacon id : abcdefgh
    // (0x6162636465666768), latitude : 25.68d (0x4039ae147ae147ae), longitude : -4.75d
    // (0xc013000000000000), altitude : 154.21f (0x431a35c3), latitudeSD : 1.25f(
    // 0x3fa00000 ), longitudeSD : 12.55f (0x4148cccd), latlonCOR : -0.005f (0xbba3d70a),
    // altSD : -1.5f (0xbfc00000)
    // clang-format off
    std::vector<uint8_t> data{
        0x00, 0x00, 0x00, 0x3a,
        0x04,
        0x61, 0x62, 0x63, 0x64,
        0x65, 0x66, 0x67, 0x68,
        0x40, 0x39, 0xae, 0x14,
        0x7a, 0xe1, 0x47, 0xae,
        0xc0, 0x13, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00,
        0x43, 0x1a, 0x35, 0xc3,
        0x3f, 0xa0, 0x00, 0x00,
        0x41, 0x48, 0xcc, 0xcd,
        0xbb, 0xa3, 0xd7, 0x0a,
        0xbf, 0xc0, 0x00, 0x00
    };
    Data::Usbl usbl2;
    usbl2.altitude_m = 154.21;
    usbl2.altitude_stddev_m = -1.5;
    usbl2.beacon_id = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h' };
    usbl2.east_stddev_m = 12.55;
    usbl2.lat_lon_cov_m2 = -0.005;
    usbl2.latitude_deg = 25.68;
    usbl2.longitude_deg = -4.75;
    usbl2.north_stddev_m = 1.25;
    usbl2.usbl_id = 4;
    usbl2.validityTime_100us = 58;

    ASSERT_SERIALIZATION(
        Serializer::Usbl2,
        usbl2,
        usbl2,
        data
    )
}

TEST(DataSerializers, SerializeUsbl3)
{
    // Validity Time : 254 (0x000000fe), USBL Id : 24 (0x18), Beacon id : abcdefgh
    // (0x6162636465666768), latitude : 25.68d (0x4039ae147ae147ae), longitude : -4.75d
    // (0xc013000000000000), altitude : 12.55f (0x4148cccd), latitudeSD : 1.25f(
    // 0x3fa00000 ), longitudeSD : 154.21f (0x431a35c3), latlonCOR : -0.005f (0xbba3d70a),
    // altSD : -1.5f (0xbfc00000)
    // clang-format off
    std::vector<uint8_t> data{
        0x00, 0x00, 0x00, 0xfe,
        0x18,
        0x61, 0x62, 0x63, 0x64,
        0x65, 0x66, 0x67, 0x68,
        0x40, 0x39, 0xae, 0x14,
        0x7a, 0xe1, 0x47, 0xae,
        0xc0, 0x13, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00,
        0x41, 0x48, 0xcc, 0xcd,
        0x3f, 0xa0, 0x00, 0x00,
        0x43, 0x1a, 0x35, 0xc3,
        0xbb, 0xa3, 0xd7, 0x0a,
        0xbf, 0xc0, 0x00, 0x00
    };
    Data::Usbl usbl3;
    usbl3.altitude_m = 12.55;
    usbl3.altitude_stddev_m = -1.5;
    usbl3.beacon_id = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h' };
    usbl3.east_stddev_m = 154.21;
    usbl3.lat_lon_cov_m2 = -0.005;
    usbl3.latitude_deg = 25.68;
    usbl3.longitude_deg = -4.75;
    usbl3.north_stddev_m = 1.25;
    usbl3.usbl_id = 24;
    usbl3.validityTime_100us = 254;

    ASSERT_SERIALIZATION(
        Serializer::Usbl3,
        usbl3,
        usbl3,
        data
    )
}

TEST(DataSerializers, SerializeDepth)
{
    // Validity Time : 254 (0x000000fe)
    // Depth : 154.21f (0x431a35c3), DepthSD : 1.25f(0x3fa00000)

    // clang-format off
    std::vector<uint8_t> data{
        0x00, 0x00, 0x00, 0xfe,
        0x43, 0x1a, 0x35, 0xc3,
        0x3f, 0xa0, 0x00, 0x00
    };
    // clang-format on
    Data::Depth depth;
    depth.depth_m = 154.21;
    depth.depth_stddev_m = 1.25;
    depth.validityTime_100us = 254;

    ASSERT_SERIALIZATION(
        Serializer::Depth,
        depth,
        depth,
        data
    )
}

TEST(DataSerializers, SerializeDvlGroundSpeed1)
{
    // Validity Time : 254 (0x000000fe), DVL Id : 24 (0x18),
    // xv1 : 154.21f (0x431a35c3), xv2 : 1.25f (0x3fa00000), xv3 : 12.55f (0x4148cccd),
    // Speed of Sound : -0.005f (0xbba3d70a), altitude : -1.5f (0xbfc00000),
    // xv1SD : 8.56f (0x4108f5c3), xv2SD : -2.4f (0xc019999a), xv3SD : 42.12f (0x42287ae1)
    // clang-format off
    std::vector<uint8_t> data{
        0x00, 0x00, 0x00, 0xfe,
        0x18,
        0x43, 0x1a, 0x35, 0xc3,
        0x3f, 0xa0, 0x00, 0x00,
        0x41, 0x48, 0xcc, 0xcd,
        0xbb, 0xa3, 0xd7, 0x0a,
        0xbf, 0xc0, 0x00, 0x00,
        0x41, 0x08, 0xf5, 0xc3,
        0xc0, 0x19, 0x99, 0x9a,
        0x42, 0x28, 0x7a, 0xe1
    };
    // clang-format on
    Data::DvlGroundSpeed dvlGroundSpeed1;
    dvlGroundSpeed1.dvl_altitude_m = -1.5;
    dvlGroundSpeed1.dvl_id = 24;
    dvlGroundSpeed1.dvl_speedofsound_ms = -0.005;
    dvlGroundSpeed1.validityTime_100us = 254;
    dvlGroundSpeed1.xv1_groundspeed_ms = 154.21;
    dvlGroundSpeed1.xv1_stddev_ms = 8.56;
    dvlGroundSpeed1.xv2_groundspeed_ms = 1.25;
    dvlGroundSpeed1.xv2_stddev_ms = -2.4;
    dvlGroundSpeed1.xv3_groundspeed_ms = 12.55;
    dvlGroundSpeed1.xv3_stddev_ms = 42.12;

    ASSERT_SERIALIZATION(
        Serializer::DvlGroundSpeed1,
        dvlGroundSpeed1,
        dvlGroundSpeed1,
        data
    )
}

TEST(DataSerializers, SerializeDvlGroundSpeed2)
{
    // Validity Time : 58 (0x0000003a), DVL Id : 4 (0x04),
    // xv1 : 154.21f (0x431a35c3), xv2 : 1.25f (0x3fa00000), xv3 : 12.55f (0x4148cccd),
    // Speed of Sound : -0.005f (0xbba3d70a), altitude : -1.5f (0xbfc00000),
    // xv1SD : 8.56f (0x4108f5c3), xv2SD : -2.4f (0xc019999a), xv3SD : 42.12f (0x42287ae1)
    // clang-format off
    std::vector<uint8_t> data{
        0x00, 0x00, 0x00, 0x3a,
        0x04,
        0x43, 0x1a, 0x35, 0xc3,
        0x3f, 0xa0, 0x00, 0x00,
        0x41, 0x48, 0xcc, 0xcd,
        0xbb, 0xa3, 0xd7, 0x0a,
        0xbf, 0xc0, 0x00, 0x00,
        0x41, 0x08, 0xf5, 0xc3,
        0xc0, 0x19, 0x99, 0x9a,
        0x42, 0x28, 0x7a, 0xe1
    };
    // clang-format on
    Data::DvlGroundSpeed dvlGroundSpeed2;
    dvlGroundSpeed2.dvl_altitude_m = -1.5;
    dvlGroundSpeed2.dvl_id = 4;
    dvlGroundSpeed2.dvl_speedofsound_ms = -0.005;
    dvlGroundSpeed2.validityTime_100us = 58;
    dvlGroundSpeed2.xv1_groundspeed_ms = 154.21;
    dvlGroundSpeed2.xv1_stddev_ms = 8.56;
    dvlGroundSpeed2.xv2_groundspeed_ms = 1.25;
    dvlGroundSpeed2.xv2_stddev_ms = -2.4;
    dvlGroundSpeed2.xv3_groundspeed_ms = 12.55;
    dvlGroundSpeed2.xv3_stddev_ms = 42.12;

    ASSERT_SERIALIZATION(
        Serializer::DvlGroundSpeed2,
        dvlGroundSpeed2,
        dvlGroundSpeed2,
        data
    )
}

TEST(DataSerializers, SerializeDvlWaterSpeed1)
{
    // Validity Time : 254 (0x000000fe), DVL Id : 24 (0x18),
    // xv1 : 154.21f (0x431a35c3), xv2 : 1.25f (0x3fa00000), xv3 : 12.55f (0x4148cccd),
    // Speed of Sound : -0.005f (0xbba3d70a)
    // xv1SD : 8.56f (0x4108f5c3), xv2SD : -2.4f (0xc019999a), xv3SD : 42.12f (0x42287ae1)
    // clang-format off
    std::vector<uint8_t> data{
        0x00, 0x00, 0x00, 0xfe,
        0x18,
        0x43, 0x1a, 0x35, 0xc3,
        0x3f, 0xa0, 0x00, 0x00,
        0x41, 0x48, 0xcc, 0xcd,
        0xbb, 0xa3, 0xd7, 0x0a,
        0x41, 0x08, 0xf5, 0xc3,
        0xc0, 0x19, 0x99, 0x9a,
        0x42, 0x28, 0x7a, 0xe1
    };
    // clang-format on

    Data::DvlWaterSpeed dvlWaterSpeed1;
    dvlWaterSpeed1.dvl_id = 24;
    dvlWaterSpeed1.dvl_speedofsound_ms = -0.005;
    dvlWaterSpeed1.validityTime_100us = 254;
    dvlWaterSpeed1.xv1_stddev_ms = 8.56;
    dvlWaterSpeed1.xv1_waterspeed_ms = 154.21;
    dvlWaterSpeed1.xv2_stddev_ms = -2.4;
    dvlWaterSpeed1.xv2_waterspeed_ms = 1.25;
    dvlWaterSpeed1.xv3_stddev_ms = 42.12;
    dvlWaterSpeed1.xv3_waterspeed_ms = 12.55;

    ASSERT_SERIALIZATION(
        Serializer::DvlWaterSpeed1,
        dvlWaterSpeed1,
        dvlWaterSpeed1,
        data
    )
}

TEST(DataSerializers, SerializeDvlWaterSpeed2)
{
    // Validity Time : 58 (0x0000003a), DVL Id : 4 (0x04),
    // xv1 : 154.21f (0x431a35c3), xv2 : 1.25f (0x3fa00000), xv3 : 12.55f (0x4148cccd),
    // Speed of Sound : -0.005f (0xbba3d70a)
    // xv1SD : 8.56f (0x4108f5c3), xv2SD : -2.4f (0xc019999a), xv3SD : 42.12f (0x42287ae1)

    // clang-format off
    std::vector<uint8_t> data{
        0x00, 0x00, 0x00, 0x3a,
        0x04,
        0x43, 0x1a, 0x35, 0xc3,
        0x3f, 0xa0, 0x00, 0x00,
        0x41, 0x48, 0xcc, 0xcd,
        0xbb, 0xa3, 0xd7, 0x0a,
        0x41, 0x08, 0xf5, 0xc3,
        0xc0, 0x19, 0x99, 0x9a,
        0x42, 0x28, 0x7a, 0xe1
    };
    // clang-format on
    Data::DvlWaterSpeed dvlWaterSpeed2;
    dvlWaterSpeed2.dvl_id = 4;
    dvlWaterSpeed2.dvl_speedofsound_ms = -0.005;
    dvlWaterSpeed2.validityTime_100us = 58;
    dvlWaterSpeed2.xv1_stddev_ms = 8.56;
    dvlWaterSpeed2.xv1_waterspeed_ms = 154.21;
    dvlWaterSpeed2.xv2_stddev_ms = -2.4;
    dvlWaterSpeed2.xv2_waterspeed_ms = 1.25;
    dvlWaterSpeed2.xv3_stddev_ms = 42.12;
    dvlWaterSpeed2.xv3_waterspeed_ms = 12.55;

    ASSERT_SERIALIZATION(
        Serializer::DvlWaterSpeed2,
        dvlWaterSpeed2,
        dvlWaterSpeed2,
        data
    )
}

TEST(DataSerializers, SerializeSoundVelocity)
{
    // Validity Time : 254 (0x000000fe), Speed of sound : 154.21f (0x431a35c3)
    // clang-format off
    std::vector<uint8_t> data{
        0x00, 0x00, 0x00, 0xfe,
        0x43, 0x1a, 0x35, 0xc3
    };
    // clang-format on
    Data::SoundVelocity soundVelocity;
    soundVelocity.ext_speedofsound_ms = 154.21;
    soundVelocity.validityTime_100us = 254;

    ASSERT_SERIALIZATION(
        Serializer::SoundVelocity,
        soundVelocity,
        soundVelocity,
        data
    )
}

TEST(DataSerializers, SerializeDmi)
{
    // Validity Time : 254 (0x000000fe), Pulse count : 154 (0x0000009a)
    // clang-format off
    std::vector<uint8_t> data{
        0x00, 0x00, 0x00, 0xfe,
        0x00, 0x00, 0x00, 0x9a
    };
    // clang-format on
    Data::Dmi dmi;
    dmi.pulse_count = 154;
    dmi.validityTime_100us = 254;

    ASSERT_SERIALIZATION(
        Serializer::Dmi,
        dmi,
        dmi,
        data
    )
}

TEST(DataSerializers, SerializeLbl1)
{
    // Validity Time : 254 (0x000000fe),  RFU : 0 (0x00), Beacon id : abcdefgh
    // (0x6162636465666768), latitude : 25.68d (0x4039ae147ae147ae), longitude : -4.75d
    // (0xc013000000000000), altitude : 154.21f (0x431a35c3), range : 1.25f(
    // 0x3fa00000), rangeSD : 12.55f (0x4148cccd)
    // clang-format off
    std::vector<uint8_t> data{
        0x00, 0x00, 0x00, 0xfe,
        0x00,
        0x61, 0x62, 0x63, 0x64,
        0x65, 0x66, 0x67, 0x68,
        0x40, 0x39, 0xae, 0x14,
        0x7a, 0xe1, 0x47, 0xae,
        0xc0, 0x13, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00,
        0x43, 0x1a, 0x35, 0xc3,
        0x3f, 0xa0, 0x00, 0x00,
        0x41, 0x48, 0xcc, 0xcd
    };
    // clang-format on
    Data::Lbl lbl1;
    lbl1.beacon_altitude_m = 154.21;
    lbl1.beacon_id = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h' };
    lbl1.beacon_latitude_deg = 25.68;
    lbl1.beacon_longitude_deg = -4.75;
    lbl1.range_m = 1.25;
    lbl1.range_stddev_m = 12.55;
    lbl1.rfu = 0;
    lbl1.validityTime_100us = 254;

    ASSERT_SERIALIZATION(
        Serializer::Lbl1,
        lbl1,
        lbl1,
        data
    )
}

TEST(DataSerializers, SerializeLbl2)
{
    // Validity Time : 58 (0x0000003a),  RFU : 0 (0x00), Beacon id : abcdefgh
    // (0x6162636465666768), latitude : 25.68d (0x4039ae147ae147ae), longitude : -4.75d
    // (0xc013000000000000), altitude : 154.21f (0x431a35c3), range : 1.25f(
    // 0x3fa00000), rangeSD : 12.55f (0x4148cccd)
    // clang-format off
    std::vector<uint8_t> data{
        0x00, 0x00, 0x00, 0x3a,
        0x00,
        0x61, 0x62, 0x63, 0x64,
        0x65, 0x66, 0x67, 0x68,
        0x40, 0x39, 0xae, 0x14,
        0x7a, 0xe1, 0x47, 0xae,
        0xc0, 0x13, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00,
        0x43, 0x1a, 0x35, 0xc3,
        0x3f, 0xa0, 0x00, 0x00,
        0x41, 0x48, 0xcc, 0xcd
    };
    // clang-format on
    Data::Lbl lbl2;
    lbl2.beacon_altitude_m = 154.21;
    lbl2.beacon_id = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h' };
    lbl2.beacon_latitude_deg = 25.68;
    lbl2.beacon_longitude_deg = -4.75;
    lbl2.range_m = 1.25;
    lbl2.range_stddev_m = 12.55;
    lbl2.rfu = 0;
    lbl2.validityTime_100us = 58;

    ASSERT_SERIALIZATION(
        Serializer::Lbl2,
        lbl2,
        lbl2,
        data
    )
}

TEST(DataSerializers, SerializeLbl3)
{
    // Validity Time : 254 (0x000000fe),  RFU : 0 (0x00), Beacon id : abcdefgh
    // (0x6162636465666768), latitude : -4.75d(0xc013000000000000), longitude : 25.68d
    // (0x4039ae147ae147ae), altitude : 154.21f (0x431a35c3), range : 1.25f(0x3fa00000),
    // rangeSD : 12.55f (0x4148cccd)
    // clang-format off
    std::vector<uint8_t> data{
        0x00, 0x00, 0x00, 0xfe,
        0x00,
        0x61, 0x62, 0x63, 0x64,
        0x65, 0x66, 0x67, 0x68,
        0xc0, 0x13, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00,
        0x40, 0x39, 0xae, 0x14,
        0x7a, 0xe1, 0x47, 0xae,
        0x43, 0x1a, 0x35, 0xc3,
        0x3f, 0xa0, 0x00, 0x00,
        0x41, 0x48, 0xcc, 0xcd
    };
    // clang-format on
    Data::Lbl lbl3;
    lbl3.beacon_altitude_m = 154.21;
    lbl3.beacon_id = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h' };
    lbl3.beacon_latitude_deg = -4.75;
    lbl3.beacon_longitude_deg = 25.68;
    lbl3.range_m = 1.25;
    lbl3.range_stddev_m = 12.55;
    lbl3.rfu = 0;
    lbl3.validityTime_100us = 254;

    ASSERT_SERIALIZATION(
        Serializer::Lbl3,
        lbl3,
        lbl3,
        data
    )
}

TEST(DataSerializers, SerializeLbl4)
{
    // Validity Time : 58 (0x0000003a),  RFU : 0 (0x00), Beacon id : abcdefgh
    // (0x6162636465666768), latitude : -4.75d(0xc013000000000000), longitude : 25.68d
    // (0x4039ae147ae147ae), altitude : 154.21f (0x431a35c3), range : 1.25f(
    // 0x3fa00000), rangeSD : 12.55f (0x4148cccd)
    // clang-format off
    std::vector<uint8_t> data{
        0x00, 0x00, 0x00, 0x3a,
        0x00,
        0x61, 0x62, 0x63, 0x64,
        0x65, 0x66, 0x67, 0x68,
        0xc0, 0x13, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00,
        0x40, 0x39, 0xae, 0x14,
        0x7a, 0xe1, 0x47, 0xae,
        0x43, 0x1a, 0x35, 0xc3,
        0x3f, 0xa0, 0x00, 0x00,
        0x41, 0x48, 0xcc, 0xcd
    };
    // clang-format on
    Data::Lbl lbl4;
    lbl4.beacon_altitude_m = 154.21;
    lbl4.beacon_id = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h' };
    lbl4.beacon_latitude_deg = -4.75;
    lbl4.beacon_longitude_deg = 25.68;
    lbl4.range_m = 1.25;
    lbl4.range_stddev_m = 12.55;
    lbl4.rfu = 0;
    lbl4.validityTime_100us = 58;

    ASSERT_SERIALIZATION(
        Serializer::Lbl4,
        lbl4,
        lbl4,
        data
    )
}

TEST(DataSerializers, SerializeEventMarkerA)
{
    // Validity Time : 254 (0x000000fe), event id : 24 (0x18)
    // Pulse count : 154 (0x0000009a)
    // clang-format off
    std::vector<uint8_t> data{
        0x00, 0x00, 0x00, 0xfe,
        0x18,
        0x00, 0x00, 0x00, 0x9a
    };
    // clang-format on
    Data::EventMarker eventMarkerA;
    eventMarkerA.event_count = 154;
    eventMarkerA.event_id = 24;
    eventMarkerA.validityTime_100us = 254;

    ASSERT_SERIALIZATION(
        Serializer::EventMarkerA,
        eventMarkerA,
        eventMarkerA,
        data
    )
}

TEST(DataSerializers, SerializeEventMarkerB)
{
    // Validity Time : 58 (0x0000003a), event id : 24 (0x18)
    // Pulse count : 254 (0x000000fe)
    // clang-format off
    std::vector<uint8_t> data{
        0x00, 0x00, 0x00, 0x3a,
        0x18,
        0x00, 0x00, 0x00, 0xfe
    };
    // clang-format on
    Data::EventMarker eventMarkerB;
    eventMarkerB.event_count = 254;
    eventMarkerB.event_id = 24;
    eventMarkerB.validityTime_100us = 58;

    ASSERT_SERIALIZATION(
        Serializer::EventMarkerB,
        eventMarkerB,
        eventMarkerB,
        data
    )
}

TEST(DataSerializers, SerializeEventMarkerC)
{
    // Validity Time : 254 (0x000000fe), event id : 4 (0x04)
    // Pulse count : 58 (0x0000003a)
    // clang-format off
    std::vector<uint8_t> data{
        0x00, 0x00, 0x00, 0xfe,
        0x04,
        0x00, 0x00, 0x00, 0x3a
    };
    // clang-format on
    Data::EventMarker eventMarkerC;
    eventMarkerC.event_count = 58;
    eventMarkerC.event_id = 4;
    eventMarkerC.validityTime_100us = 254;

    ASSERT_SERIALIZATION(
        Serializer::EventMarkerC,
        eventMarkerC,
        eventMarkerC,
        data
    )
}

TEST(DataSerializers, SerializeTurretAngles)
{
    // Validity Time : 254 (0x000000fe),
    // Angle : 1.25f (0x3fa00000), Roll : 12.55f (0x4148cccd),
    // Elevation putch : -0.005f (0xbba3d70a)

    // clang-format off
    std::vector<uint8_t> data{
        0x00, 0x00, 0x00, 0xfe,
        0x3f, 0xa0, 0x00, 0x00,
        0x41, 0x48, 0xcc, 0xcd,
        0xbb, 0xa3, 0xd7, 0x0a
    };
    // clang-format on
    Data::TurretAngles turretAngles;
    turretAngles.elevationpitch_deg = -0.005;
    turretAngles.headingbearingdrift_angle_deg = 1.25;
    turretAngles.roll_deg = 12.55;
    turretAngles.validityTime_100us = 254;

    ASSERT_SERIALIZATION(
        Serializer::TurretAngles,
        turretAngles,
        turretAngles,
        data
    )
}

TEST(DataSerializers, SerializeVtg1)
{
    // Validity Time : 254 (0x000000fe), VTG Id : 24 (0x18),
    // Angle : 1.25f (0x3fa00000), Roll : 12.55f (0x4148cccd),
    // Elevation putch : -0.005f (0xbba3d70a)
    // clang-format off
    std::vector<uint8_t> data{
        0x00, 0x00, 0x00, 0xfe,
        0x18,
        0x3f, 0xa0, 0x00, 0x00,
        0x41, 0x48, 0xcc, 0xcd,
        0xbb, 0xa3, 0xd7, 0x0a
    };
    // clang-format
    Data::Vtg vtg1;
    vtg1.magnetic_course_deg = 12.55;
    vtg1.speed_over_ground_ms = -0.005;
    vtg1.true_course_deg = 1.25;
    vtg1.validityTime_100us = 254;
    vtg1.vtg_id = 24;

    ASSERT_SERIALIZATION(
        Serializer::Vtg1,
        vtg1,
        vtg1,
        data
    )
}

TEST(DataSerializers, SerializeVtg2)
{
    // Validity Time : 58 (0x0000003a), VTG Id : 4 (0x04),
    // Angle : 1.25f (0x3fa00000), Roll : 12.55f (0x4148cccd),
    // Elevation putch : -0.005f (0xbba3d70a)
    // clang-format off
    std::vector<uint8_t> data{
        0x00, 0x00, 0x00, 0x3a,
        0x04,
        0x3f, 0xa0, 0x00, 0x00,
        0x41, 0x48, 0xcc, 0xcd,
        0xbb, 0xa3, 0xd7, 0x0a
    };
    // clang-format on
    Data::Vtg vtg2;
    vtg2.magnetic_course_deg = 12.55;
    vtg2.speed_over_ground_ms = -0.005;
    vtg2.true_course_deg = 1.25;
    vtg2.validityTime_100us = 58;
    vtg2.vtg_id = 4;

    ASSERT_SERIALIZATION(
        Serializer::Vtg2,
        vtg2,
        vtg2,
        data
    )
}

TEST(DataSerializers, SerializeLogBook)
{
    // Validity Time : 254 (0x000000fe), event id : 785 (0x00000311)
    // Pulse count : abcd (0x61626364)

    // clang-format off
    std::vector<uint8_t> data{
        0x00, 0x00, 0x00, 0xfe,
        0x00, 0x00, 0x03, 0x11,
        0x61, 0x62, 0x63, 0x64,
        0x65, 0x66, 0x67, 0x68,
        0x61, 0x62, 0x63, 0x64,
        0x65, 0x66, 0x67, 0x68,
        0x61, 0x62, 0x63, 0x64,
        0x65, 0x66, 0x67, 0x68,
        0x61, 0x62, 0x63, 0x64,
        0x65, 0x66, 0x67, 0x68
    };
    // clang-format on
    Data::LogBook logBook;
    logBook.custom_text = {
        'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h',
        'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h',
        'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h',
        'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h'
    };
    logBook.log_id = 785;
    logBook.validityTime_100us = 254;

    ASSERT_SERIALIZATION(
        Serializer::LogBook,
        logBook,
        logBook,
        data
    )
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
