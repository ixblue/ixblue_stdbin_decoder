#ifndef TEST_DATASET_MINIMAL_V3_ANS_FRAME_H
#define TEST_DATASET_MINIMAL_V3_ANS_FRAME_H
#include <array>
// clang-format off
constexpr std::array<uint8_t,0x0d> MINIMAL_V3_ANS_FRAME {
    'A',  'N',  /* IX blue header   */
    0x03,       /* Protocol Version */
    0x00, 0x0d, /* Telegram size */
    0xde, 0xad, 0xbe, 0xef, /* payload */
    0x00, 0x00, 0x03, 0xd7, /* checksum */
};
// clang-format on
#endif // TEST_DATASET_MINIMAL_V3_ANS_FRAME_H