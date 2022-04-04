#include <numeric>
#include <sstream>
#include <stdexcept>

#include <ixblue_stdbin_decoder/stdbin_decoder.h>

/* Navigation data blocs */
#include <ixblue_stdbin_decoder/memory_blocs_parsers/extended_navigation_data/rotation_acceleration_vessel_frame.h>
#include <ixblue_stdbin_decoder/memory_blocs_parsers/extended_navigation_data/rotation_acceleration_vessel_frame_deviation.h>
#include <ixblue_stdbin_decoder/memory_blocs_parsers/navigation_data/acceleration_geographic_frame.h>
#include <ixblue_stdbin_decoder/memory_blocs_parsers/navigation_data/acceleration_vessel_frame.h>
#include <ixblue_stdbin_decoder/memory_blocs_parsers/navigation_data/acceleration_vessel_frame_deviation.h>
#include <ixblue_stdbin_decoder/memory_blocs_parsers/navigation_data/ahrs_algorithm_status.h>
#include <ixblue_stdbin_decoder/memory_blocs_parsers/navigation_data/ahrs_system_status.h>
#include <ixblue_stdbin_decoder/memory_blocs_parsers/navigation_data/ahrs_user_status.h>
#include <ixblue_stdbin_decoder/memory_blocs_parsers/navigation_data/attitude_heading.h>
#include <ixblue_stdbin_decoder/memory_blocs_parsers/navigation_data/attitude_heading_deviation.h>
#include <ixblue_stdbin_decoder/memory_blocs_parsers/navigation_data/attitude_quaternion.h>
#include <ixblue_stdbin_decoder/memory_blocs_parsers/navigation_data/attitude_quaternion_deviation.h>
#include <ixblue_stdbin_decoder/memory_blocs_parsers/navigation_data/course_speed_over_ground.h>
#include <ixblue_stdbin_decoder/memory_blocs_parsers/navigation_data/current_geographic_frame.h>
#include <ixblue_stdbin_decoder/memory_blocs_parsers/navigation_data/current_geographic_frame_deviation.h>
#include <ixblue_stdbin_decoder/memory_blocs_parsers/navigation_data/heading_roll_pitch_rate.h>
#include <ixblue_stdbin_decoder/memory_blocs_parsers/navigation_data/heave_surge_sway_speed.h>
#include <ixblue_stdbin_decoder/memory_blocs_parsers/navigation_data/ins_algorithm_status.h>
#include <ixblue_stdbin_decoder/memory_blocs_parsers/navigation_data/ins_system_status.h>
#include <ixblue_stdbin_decoder/memory_blocs_parsers/navigation_data/ins_user_status.h>
#include <ixblue_stdbin_decoder/memory_blocs_parsers/navigation_data/position.h>
#include <ixblue_stdbin_decoder/memory_blocs_parsers/navigation_data/position_deviation.h>
#include <ixblue_stdbin_decoder/memory_blocs_parsers/navigation_data/raw_acceleration_vessel_frame.h>
#include <ixblue_stdbin_decoder/memory_blocs_parsers/navigation_data/realtime_heave_surge_sway.h>
#include <ixblue_stdbin_decoder/memory_blocs_parsers/navigation_data/rotation_rate_vessel_frame.h>
#include <ixblue_stdbin_decoder/memory_blocs_parsers/navigation_data/rotation_rate_vessel_frame_deviation.h>
#include <ixblue_stdbin_decoder/memory_blocs_parsers/navigation_data/sensor_status.h>
#include <ixblue_stdbin_decoder/memory_blocs_parsers/navigation_data/smart_heave.h>
#include <ixblue_stdbin_decoder/memory_blocs_parsers/navigation_data/speed_geographic_frame.h>
#include <ixblue_stdbin_decoder/memory_blocs_parsers/navigation_data/speed_geographic_frame_deviation.h>
#include <ixblue_stdbin_decoder/memory_blocs_parsers/navigation_data/speed_vessel_frame.h>
#include <ixblue_stdbin_decoder/memory_blocs_parsers/navigation_data/system_date.h>
#include <ixblue_stdbin_decoder/memory_blocs_parsers/navigation_data/temperatures.h>

/* Extended navigation data blocs */
#include <ixblue_stdbin_decoder/memory_blocs_parsers/extended_navigation_data/raw_rotation_rate_vessel_frame.h>
#include <ixblue_stdbin_decoder/memory_blocs_parsers/extended_navigation_data/rotation_acceleration_vessel_frame.h>
#include <ixblue_stdbin_decoder/memory_blocs_parsers/extended_navigation_data/rotation_acceleration_vessel_frame_deviation.h>
#include <ixblue_stdbin_decoder/memory_blocs_parsers/extended_navigation_data/vehicle_attitude_heading.h>
#include <ixblue_stdbin_decoder/memory_blocs_parsers/extended_navigation_data/vehicle_attitude_heading_deviation.h>
#include <ixblue_stdbin_decoder/memory_blocs_parsers/extended_navigation_data/vehicle_position.h>
#include <ixblue_stdbin_decoder/memory_blocs_parsers/extended_navigation_data/vehicle_position_deviation.h>

/* External data blocs */
#include <ixblue_stdbin_decoder/memory_blocs_parsers/external_data/depth.h>
#include <ixblue_stdbin_decoder/memory_blocs_parsers/external_data/dmi.h>
#include <ixblue_stdbin_decoder/memory_blocs_parsers/external_data/dvl_ground_speed.h>
#include <ixblue_stdbin_decoder/memory_blocs_parsers/external_data/dvl_water_speed.h>
#include <ixblue_stdbin_decoder/memory_blocs_parsers/external_data/emlog.h>
#include <ixblue_stdbin_decoder/memory_blocs_parsers/external_data/eventmarker.h>
#include <ixblue_stdbin_decoder/memory_blocs_parsers/external_data/gnss.h>
#include <ixblue_stdbin_decoder/memory_blocs_parsers/external_data/lbl.h>
#include <ixblue_stdbin_decoder/memory_blocs_parsers/external_data/logbook.h>
#include <ixblue_stdbin_decoder/memory_blocs_parsers/external_data/sound_velocity.h>
#include <ixblue_stdbin_decoder/memory_blocs_parsers/external_data/turret_angles.h>
#include <ixblue_stdbin_decoder/memory_blocs_parsers/external_data/usbl.h>
#include <ixblue_stdbin_decoder/memory_blocs_parsers/external_data/utc.h>
#include <ixblue_stdbin_decoder/memory_blocs_parsers/external_data/vtg.h>

using namespace boost::asio;

namespace ixblue_stdbin_decoder
{

StdBinDecoder::StdBinDecoder()
    : navigationParsers(
          {std::make_shared<Parser::AttitudeHeading>(),
           std::make_shared<Parser::AttitudeHeadingDeviation>(),
           std::make_shared<Parser::RealTimeHeaveSurgeSway>(),
           std::make_shared<Parser::SmartHeave>(),
           std::make_shared<Parser::HeadingRollPitchRate>(),
           std::make_shared<Parser::RotationRateVesselFrame>(),
           std::make_shared<Parser::AccelerationVesselFrame>(),
           std::make_shared<Parser::Position>(),
           std::make_shared<Parser::PositionDeviation>(),
           std::make_shared<Parser::SpeedGeographicFrame>(),
           std::make_shared<Parser::SpeedGeographicFrameDeviation>(),
           std::make_shared<Parser::CurrentGeographicFrame>(),
           std::make_shared<Parser::CurrentGeographicFrameDeviation>(),
           std::make_shared<Parser::SystemDate>(),
           std::make_shared<Parser::SensorStatus>(),
           std::make_shared<Parser::INSAlgorithmStatus>(),
           std::make_shared<Parser::INSSystemStatus>(),
           std::make_shared<Parser::INSUserStatus>(),
           std::make_shared<Parser::AHRSAlgorithmStatus>(),
           std::make_shared<Parser::AHRSSystemStatus>(),
           std::make_shared<Parser::AHRSUserStatus>(),
           std::make_shared<Parser::HeaveSurgeSwaySpeed>(),
           std::make_shared<Parser::SpeedVesselFrame>(),
           std::make_shared<Parser::AccelerationGeographicFrame>(),
           std::make_shared<Parser::CourseSpeedoverGround>(),
           std::make_shared<Parser::Temperatures>(),
           std::make_shared<Parser::AttitudeQuaternion>(),
           std::make_shared<Parser::AttitudeQuaternionDeviation>(),
           std::make_shared<Parser::RawAccelerationVesselFrame>(),
           std::make_shared<Parser::AccelerationVesselFrameDeviation>(),
           std::make_shared<Parser::RotationRateVesselFrameDeviation>()},
          [](const MemoryBlockParserPtr& lhs, const MemoryBlockParserPtr& rhs) -> bool {
              return lhs->getOffsetInMask() < rhs->getOffsetInMask();
          }),
      extendedNavigationParsers(
          {std::make_shared<Parser::RotationAccelerationVesselFrame>(),
           std::make_shared<Parser::RotationAccelerationVesselFrameDeviation>(),
           std::make_shared<Parser::RawRotationRateVesselFrame>(),
           std::make_shared<Parser::VehicleAttitudeHeading>(),
           std::make_shared<Parser::VehiclePosition>(),
           std::make_shared<Parser::VehiclePositionDeviation>()},
          [](const MemoryBlockParserPtr& lhs, const MemoryBlockParserPtr& rhs) -> bool {
              return lhs->getOffsetInMask() < rhs->getOffsetInMask();
          }),
      externalDataParsers(
          {std::make_shared<Parser::Utc>(),
           std::make_shared<Parser::Gnss1>(),
           std::make_shared<Parser::Gnss2>(),
           std::make_shared<Parser::GnssManual>(),
           std::make_shared<Parser::Emlog1>(),
           std::make_shared<Parser::Emlog2>(),
           std::make_shared<Parser::Depth>(),
           std::make_shared<Parser::Usbl1>(),
           std::make_shared<Parser::Usbl2>(),
           std::make_shared<Parser::Usbl3>(),
           std::make_shared<Parser::DvlGroundSpeed1>(),
           std::make_shared<Parser::DvlWaterSpeed1>(),
           std::make_shared<Parser::SoundVelocity>(),
           std::make_shared<Parser::Dmi>(),
           std::make_shared<Parser::Lbl1>(),
           std::make_shared<Parser::Lbl2>(),
           std::make_shared<Parser::Lbl3>(),
           std::make_shared<Parser::Lbl4>(),
           std::make_shared<Parser::EventMarkerA>(),
           std::make_shared<Parser::EventMarkerB>(),
           std::make_shared<Parser::EventMarkerC>(),
           std::make_shared<Parser::DvlGroundSpeed2>(),
           std::make_shared<Parser::DvlWaterSpeed2>(),
           std::make_shared<Parser::TurretAngles>(),
           std::make_shared<Parser::Vtg1>(),
           std::make_shared<Parser::Vtg2>(),
           std::make_shared<Parser::LogBook>()},
          [](const MemoryBlockParserPtr& lhs, const MemoryBlockParserPtr& rhs) -> bool {
              return lhs->getOffsetInMask() < rhs->getOffsetInMask();
          }),
      internalBuffer{128000}

{}

void StdBinDecoder::addNewData(const std::vector<uint8_t>& data)
{
    addNewData(data.data(), data.size());
}

void StdBinDecoder::addNewData(const uint8_t* data, std::size_t length)
{
    internalBuffer.insert(internalBuffer.end(), data, data + length);
}

bool StdBinDecoder::parseNextFrame()
{
    // Now, we will look for version of the received frame and wait to have receive enough
    // data to parse full header.
    if(!haveEnoughBytesToParseHeader())
    {
        return false;
    }

    // The call to linearize() can lead to a copy of the buffer content, but once in a
    // because the buffer is quite large
    boost::asio::const_buffer buffer(internalBuffer.linearize(), internalBuffer.size());
    lastHeader = parseHeader(buffer);
    // if we didn't receive the whole frame, we return false, and wait for the next
    // memory chunck.
    if(internalBuffer.size() < lastHeader.telegramSize)
    {
        return false;
    }

    // Compare checksum before going further (will throw if bad)
    compareChecksum();

    if(lastHeader.messageType == Data::NavHeader::MessageType::NavData)
    {
        for(const auto& parser : navigationParsers)
        {
            parser->parse(buffer, lastHeader.navigationBitMask, lastParsed);
        }

        if(lastHeader.extendedNavigationBitMask.is_initialized())
        {
            for(const auto& parser : extendedNavigationParsers)
            {
                parser->parse(buffer, lastHeader.extendedNavigationBitMask.get(),
                              lastParsed);
            }
        }

        for(const auto& parser : externalDataParsers)
        {
            parser->parse(buffer, lastHeader.externalSensorBitMask, lastParsed);
        }
    }
    else if(lastHeader.messageType == Data::NavHeader::MessageType::Answer)
    {
        lastAnswer.clear();
        const size_t answerSize =
            lastHeader.telegramSize - ANSWER_HEADER_SIZE - CHECKSUM_SIZE;
        lastAnswer.resize(answerSize);
        buffer_copy(boost::asio::buffer(lastAnswer), buffer, answerSize);
        buffer = buffer + answerSize;
    }

    // Remove the parsed telegram from the buffer
    internalBuffer.erase_begin(lastHeader.telegramSize);
    return true;
}

bool StdBinDecoder::haveEnoughBytesToParseHeader()
{
    while(internalBuffer.size() > 3)
    {
        const uint8_t protocol_version = internalBuffer[2];
        if(internalBuffer[0] == 'I' && internalBuffer[1] == 'X')
        {
            switch(protocol_version)
            {
            case 0x02: return internalBuffer.size() >= HEADER_SIZE_V2;
            case 0x03: return internalBuffer.size() >= HEADER_SIZE_V3;
            case 0x04: return internalBuffer.size() >= HEADER_SIZE_V4;
            case 0x05: return internalBuffer.size() >= HEADER_SIZE_V5;
            default:
                // Errors need to clean header, pop one byte at front associated to internal buffer and thrown exception
                internalBuffer.pop_front();
                throw std::runtime_error("Unhandled protocol version");
            }
        }
        else if(internalBuffer[0] == 'A' && internalBuffer[1] == 'N')
        {
            if(protocol_version >= 3 && protocol_version <= 5)
            {
                return internalBuffer.size() >= ANSWER_HEADER_SIZE;
            }
            else
            {
                // Errors need to clean header, pop one byte at front associated to internal buffer and thrown exception
                internalBuffer.pop_front();
                throw std::runtime_error("Unhandled protocol version for an answer");
            }
        }
        else
        {
            // No valid header found, pop one byte at the front of the buffer and try
            // again
            internalBuffer.pop_front();
        }
    }
    return false;
}

void StdBinDecoder::compareChecksum()
{
    // Create a new buffer to start from start of frame
    // This call to linearize() is free because the buffer as been linearized just before
    boost::asio::const_buffer buffer(internalBuffer.linearize(), internalBuffer.size());
    const std::size_t checksumPositionInFrame = lastHeader.telegramSize - CHECKSUM_SIZE;
    buffer = buffer + checksumPositionInFrame;
    uint32_t receivedChecksum = 0;
    buffer >> receivedChecksum;

    const uint32_t computedChecksum = std::accumulate(
        internalBuffer.begin(), internalBuffer.begin() + checksumPositionInFrame, 0);

    if(receivedChecksum != computedChecksum)
    {
        // Remove the parsed telegram from the buffer
        internalBuffer.erase_begin(lastHeader.telegramSize);

        std::ostringstream ss;
        ss << "Bad checksum. Received: 0x" << std::hex << receivedChecksum
           << ", computed: 0x" << computedChecksum;
        throw std::runtime_error(ss.str());
    }
}

Data::NavHeader StdBinDecoder::parseHeader(const_buffer& buffer) const
{
    // We know we have enough bytes to parse the whole header because it had been
    // checked before.
    static constexpr size_t HEADER_MINIMAL_SIZE = 3;

    Data::NavHeader res;
    if(buffer_size(buffer) < HEADER_MINIMAL_SIZE)
    {
        throw std::runtime_error("Not enough bytes in buffer to parse header");
    }

    res.messageType = getHeaderType(buffer);
    if(res.messageType == Data::NavHeader::MessageType::Unknown)
    {
        throw std::runtime_error("Incorrect frame header, expected 'I', 'X' or 'A', 'N'");
    }

    buffer >> res.protocolVersion;
    if(res.protocolVersion < 2 || res.protocolVersion > 5)
    {
        throw std::runtime_error(
            "Unknown protocol version. Supported protocol are version 2->5");
    }

    if(res.messageType == Data::NavHeader::MessageType::NavData)
    {
        buffer >> res.navigationBitMask;
        if(res.protocolVersion > 2)
        {
            uint32_t extendedNavigationMask;
            buffer >> extendedNavigationMask;
            res.extendedNavigationBitMask = extendedNavigationMask;
        }
        buffer >> res.externalSensorBitMask;
        uint16_t navigationSize = 0;
        if(res.protocolVersion > 3)
        {
            buffer >> navigationSize;
        }
        buffer >> res.telegramSize;
        buffer >> res.navigationDataValidityTime_100us;
        uint32_t counter;
        buffer >> counter;
    }
    else
    {
        buffer >> res.telegramSize;
    }
    return res;
}

Data::NavHeader::MessageType StdBinDecoder::getHeaderType(const_buffer& buffer) const
{
    // We already checked the buffer size before calling this method.
    uint8_t h1, h2;
    buffer >> h1;
    buffer >> h2;

    if(h1 == 'I' && h2 == 'X')
    {
        return Data::NavHeader::MessageType::NavData;
    }

    if(h1 == 'A' && h2 == 'N')
    {
        return Data::NavHeader::MessageType::Answer;
    }

    return Data::NavHeader::MessageType::Unknown;
}

} // namespace ixblue_stdbin_decoder
