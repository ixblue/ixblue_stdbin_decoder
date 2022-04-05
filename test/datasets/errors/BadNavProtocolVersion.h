#ifndef TEST_DATASET_BAD_NAV_PROTOCOL_VERSION_H
#define TEST_DATASET_BAD_NAV_PROTOCOL_VERSION_H
#include <array>
// clang-format off
constexpr std::array<uint8_t,0x25> BAD_NAV_PROTOCOL_VERSION {
    'I',  'X',  /*IX blue header   */
    0x00,       /*Protocol Version */
    0x00, 0x00, 0x00, 0x01, /* navigation bitmask (0x00000001 means only AttitudeAndHeading) */
    0x00, 0x00, 0x00, 0x00, /* external data bitmask */
    0x00, 0x25,             /* Telegram size */
    0x00, 0x00, 0x00, 0x05, /* navigation validity time (500 us) */
    0x00, 0x00, 0x01, 0x23, /* counter (0x123) */
    0x00, 0x00, 0xa0, 0x3f, /* Heading : 1.25f */
    0x00, 0x00, 0xc0, 0xbf, /* roll : -1.5f   */
    0xcd, 0xcc, 0x48, 0x41, /* Pitch : 12.55f */
    0x00, 0x00, 0x05, 0x70  /* Checksum */
};
// clang-format on
#endif //TEST_DATASET_BAD_NAV_PROTOCOL_VERSION_H
