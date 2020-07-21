#include <gtest/gtest.h>
#include <iXblue_stdbin_decoder/data_models/stdbin.h>
#include <iXblue_stdbin_decoder/stdbin_encoder.h>
#include <numeric>

using namespace StdBinDecoder;

TEST(StdBinEncoder, SerializesABinaryPacket)
{
    // Given a frame with only attitude :
    // clang-format off
    std::vector<uint8_t> memory{
        'I',  'X',              /* IX blue header */
        0x05,                   /* Protocol Version */
        0x00, 0x00, 0x00, 0x00, /* navigation bitmask */
        0x00, 0x00, 0x00, 0x00, /* extended navigation bitmask */
        0x00, 0x00, 0x12, 0x01, /* external data bitmask (Utc, Depth and SoundVelocity) */
        0x00, 0x00,             /* navigation size */
        0x00, 0x38,             /* Telegram size */
        0x00,                   /* UTC time reference */
        0x00, 0x00, 0x00, 0x00, /* RFU */
        0x00, 0x00, 0x00,       /* RFU */
        0xDE, 0xAD, 0xBE, 0xEF,
        0xFF,
        0xC0, 0xCA, 0xF0, 0x0D,
        0xBA, 0xDC, 0x0C, 0x0A,
        0xDE, 0xAD, 0xFE, 0xED,
        0xDE, 0xAD, 0xC0, 0xDE,
        0xC0, 0xFE, 0xEF, 0xEE
    };
    // clang-format on

    uint32_t checksum = std::accumulate(memory.begin(), memory.end(), 0);
    memory.push_back((checksum & 0xFF000000) >> 24);
    memory.push_back((checksum & 0x00FF0000) >> 16);
    memory.push_back((checksum & 0x0000FF00) >> 8);
    memory.push_back((checksum & 0x000000FF) >> 0);

    StdBinEncoder serializer;
    Data::BinaryNav binaryNav;
    binaryNav.utc = Data::Utc();
    binaryNav.utc->validityTime_100us = 0xDEADBEEF;
    binaryNav.utc->source = 0xFF;
    binaryNav.depth = Data::Depth();
    binaryNav.depth->validityTime_100us = 0xC0CAF00D;
    *reinterpret_cast<uint32_t *>(&binaryNav.depth->depth_m) = 0xBADC0C0A;
    *reinterpret_cast<uint32_t *>(&binaryNav.depth->depth_stddev_m) = 0xDEADFEED;
    binaryNav.soundVelocity = Data::SoundVelocity();
    *reinterpret_cast<uint32_t *>(&binaryNav.soundVelocity->ext_speedofsound_ms)
        = 0xC0FEEFEE;
    binaryNav.soundVelocity->validityTime_100us = 0xDEADC0DE;

    std::vector<uint8_t> packet = serializer.serialize(binaryNav);
    ASSERT_EQ(memory, packet);
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
