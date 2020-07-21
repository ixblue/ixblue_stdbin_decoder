#pragma once

#include "iXblue_stdbin_decoder/data_models/external_data/eventmarker.h"
#include "iXblue_stdbin_decoder/data_serializer.h"

namespace StdBinDecoder
{
namespace Serializer
{
class EventMarker : public DataSerializer
{
public:
    EventMarker(int bit_pose) : DataSerializer(bit_pose, 9) { }
    bool serialize(boost::asio::mutable_buffer& outBuffer,
                   const Data::BinaryNav& binaryNav) override
    {
        if (!getData(binaryNav).is_initialized()) {
            return false;
        }
        outBuffer << getData(binaryNav)->validityTime_100us
                  << getData(binaryNav)->event_id
                  << getData(binaryNav)->event_count;
        return true;
    }
    virtual const boost::optional<Data::EventMarker>& getData(const Data::BinaryNav& binaryNav) const = 0;
};

class EventMarkerA : public EventMarker
{
public:
    EventMarkerA() : EventMarker(18) { }

protected:
    const boost::optional<Data::EventMarker>& getData(const Data::BinaryNav& binaryNav) const
    {
        return binaryNav.eventMarkerA;
    }
};

class EventMarkerB : public EventMarker
{
public:
    EventMarkerB() : EventMarker(19) { }

protected:
    const boost::optional<Data::EventMarker>& getData(const Data::BinaryNav& binaryNav) const
    {
        return binaryNav.eventMarkerB;
    }
};

class EventMarkerC : public EventMarker
{
public:
    EventMarkerC() : EventMarker(20) { }

protected:
    const boost::optional<Data::EventMarker>& getData(const Data::BinaryNav& binaryNav) const
    {
        return binaryNav.eventMarkerC;
    }
};

} // namespace Serializer
} // namespace StdBinDecoder
