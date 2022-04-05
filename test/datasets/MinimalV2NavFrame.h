#ifndef TEST_DATASET_MINIMAL_V2_NAV_FRAME_H
#define TEST_DATASET_MINIMAL_V2_NAV_FRAME_H
#include <array>
// clang-format off
constexpr std::array<uint8_t,0x25> MINIMAL_V2_NAV_FRAME {
    'I',  'X',  /*IX blue header   */
    0x02,       /*Protocol Version */
    0x00, 0x00, 0x00, 0x01, /* navigation bitmask (0x00000001 means only AttitudeAndHeading) */
    0x00, 0x00, 0x00, 0x00, /* external data bitmask */
    0x00, 0x25,             /* Telegram size */
    0x00, 0x00, 0x00, 0x05, /* navigation validity time (500 us) */
    0x00, 0x00, 0x01, 0x23, /* counter (0x123) */
    0x00, 0x00, 0xa0, 0x3f, /* Heading : 1.25f */
    0x00, 0x00, 0xc0, 0xbf, /* roll : -1.5f   */
    0xcd, 0xcc, 0x48, 0x41, /* Pitch : 12.55f */
    0x00, 0x00, 0x5, 0x72  /* Checksum */
};
// clang-format on
#endif // TEST_DATASET_MINIMAL_V2_NAV_FRAME_H
