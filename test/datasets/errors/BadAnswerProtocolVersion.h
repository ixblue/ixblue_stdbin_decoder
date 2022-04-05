#ifndef TEST_DATASET_BAD_ANSWER_PROTOCOL_VERSION_H
#define TEST_DATASET_BAD_ANSWER_PROTOCOL_VERSION_H
#include <array>
// clang-format off
constexpr std::array<uint8_t,0x0d> BAD_ANSWER_PROTOCOL_VERSION {
    'A',  'N',  /* IX blue header   */
    0x00,       /* Protocol Version */
    0x00, 0x0d, /* Telegram size */
    0xde, 0xad, 0xbe, 0xef, /* payload */
    0x00, 0x00, 0x3, 0xd4, /* checksum */
};
// clang-format on
#endif //TEST_DATASET_BAD_ANSWER_PROTOCOL_VERSION_H
