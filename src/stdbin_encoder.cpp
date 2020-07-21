#include <iXblue_stdbin_decoder/stdbin_encoder.h>

/* Navigation data blocs */
#include <iXblue_stdbin_decoder/data_serializers/extended_navigation_data/rotation_acceleration_vessel_frame.h>
#include <iXblue_stdbin_decoder/data_serializers/extended_navigation_data/rotation_acceleration_vessel_frame_deviation.h>
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

/* Extended navigation data blocs */
#include <iXblue_stdbin_decoder/data_serializers/extended_navigation_data/raw_rotation_rate_vessel_frame.h>
#include <iXblue_stdbin_decoder/data_serializers/extended_navigation_data/rotation_acceleration_vessel_frame.h>
#include <iXblue_stdbin_decoder/data_serializers/extended_navigation_data/rotation_acceleration_vessel_frame_deviation.h>
#include <iXblue_stdbin_decoder/data_serializers/extended_navigation_data/vehicle_attitude_heading.h>
#include <iXblue_stdbin_decoder/data_serializers/extended_navigation_data/vehicle_attitude_heading_deviation.h>
#include <iXblue_stdbin_decoder/data_serializers/extended_navigation_data/vehicle_position.h>
#include <iXblue_stdbin_decoder/data_serializers/extended_navigation_data/vehicle_position_deviation.h>

/* External data blocs */
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

#include <numeric>

using namespace StdBinDecoder;
using namespace boost::asio;

StdBinEncoder::StdBinEncoder::StdBinEncoder(ProtocolVersion version, DataMode mode)
    : dataMode(mode)
    , protocolVersion(version)
    , externalDataSerializers(
          { std::make_shared<Serializer::Utc>(),
            std::make_shared<Serializer::Gnss1>(),
            std::make_shared<Serializer::Gnss2>(),
            std::make_shared<Serializer::GnssManual>(),
            std::make_shared<Serializer::Emlog1>(),
            std::make_shared<Serializer::Emlog2>(),
            std::make_shared<Serializer::Depth>(),
            std::make_shared<Serializer::Usbl1>(),
            std::make_shared<Serializer::Usbl2>(),
            std::make_shared<Serializer::Usbl3>(),
            std::make_shared<Serializer::DvlGroundSpeed1>(),
            std::make_shared<Serializer::DvlWaterSpeed1>(),
            std::make_shared<Serializer::SoundVelocity>(),
            std::make_shared<Serializer::Dmi>(),
            std::make_shared<Serializer::Lbl1>(),
            std::make_shared<Serializer::Lbl2>(),
            std::make_shared<Serializer::Lbl3>(),
            std::make_shared<Serializer::Lbl4>(),
            std::make_shared<Serializer::EventMarkerA>(),
            std::make_shared<Serializer::EventMarkerB>(),
            std::make_shared<Serializer::EventMarkerC>(),
            std::make_shared<Serializer::DvlGroundSpeed2>(),
            std::make_shared<Serializer::DvlWaterSpeed2>(),
            std::make_shared<Serializer::TurretAngles>(),
            std::make_shared<Serializer::Vtg1>(),
            std::make_shared<Serializer::Vtg2>(),
            std::make_shared<Serializer::LogBook>() },
          [](const DataSerializerPtr& lhs, const DataSerializerPtr& rhs) -> bool {
              return lhs->getOffsetInMask() < rhs->getOffsetInMask();
          })
{
    if (dataMode != INPUT) {
        throw std::runtime_error(
            "This library can only serialize data in input mode"
        );
    }
}

std::pair<uint32_t, std::vector<uint8_t>> StdBinEncoder::processExternalData(
    const Data::BinaryNav binaryNav
) const
{
    std::vector<uint8_t> externalData;
    std::bitset<32> externalDataBitMask;

    for (const auto& serializer : externalDataSerializers)
    {
        std::vector<uint8_t> memory(serializer->getBytesCount());
        boost::asio::mutable_buffer buffer(memory.data(), memory.size());

        if (serializer->serialize(buffer, externalDataBitMask, binaryNav)) {
            externalData.insert(externalData.end(), memory.begin(), memory.end());
        }
    }

   return { externalDataBitMask.to_ulong(), externalData };
}

size_t StdBinEncoder::getHeaderSize(const Data::BinaryNav& binaryNav) const
{
    switch (protocolVersion)
    {
    case V2: return 21;
    case V3: return 25;
    case V4: return 27;
    case V5: return 27;
    default: throw std::runtime_error("Unknown protocol version");
    }
}

std::vector<uint8_t> StdBinEncoder::serialize(const Data::BinaryNav& binaryNav) const
{
    uint32_t externalDataBitMask;
    std::vector<uint8_t> externalData;

    std::tie(externalDataBitMask, externalData) = processExternalData(binaryNav);

    uint16_t telegramSize =  getHeaderSize(binaryNav) + // the header size +
                             externalData.size() + 4;   // external sensor data size
                                                        // + 4 bytes checksum

    std::vector<uint8_t> memory(telegramSize);
    boost::asio::mutable_buffer buffer(memory.data(), memory.size());

    buffer << (uint8_t)'I';
    buffer << (uint8_t)'X';
    buffer << (uint8_t)protocolVersion;
    buffer << (uint32_t)0; // navigation bit mask (unused in input mode)

    if (protocolVersion > 2)
    {
        buffer << (uint32_t)0; // extended navigation bit mask
                               // (unused in input mode)
    }
    buffer << externalDataBitMask;

    if (protocolVersion > 3)
    {
        buffer << (uint16_t)0; // navigation size
                               // (unused in input mode)
    }

    buffer << telegramSize;

    buffer << (uint8_t)0x00; // UTC time reference
    buffer << std::array<uint8_t, 7>{ 0, 0, 0, 0, 0, 0, 0 }; // rfu (should be 0x00
                                                             // in input mode)

    buffer << externalData;

    uint32_t checksum = std::accumulate(memory.begin(), memory.end() - 4, 0);
    buffer << checksum;

    return memory;
}
