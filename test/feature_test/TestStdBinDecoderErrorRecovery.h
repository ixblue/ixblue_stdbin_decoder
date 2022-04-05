#ifndef TEST_STD_BIN_DECODER_ERROR_RECOVERY_FEATURE_H
#define TEST_STD_BIN_DECODER_ERROR_RECOVERY_FEATURE_H

#include <gtest/gtest.h>
#include <ixblue_stdbin_decoder/stdbin_decoder.h>

// add data for error recovery
#include "../datasets/errors/BadCheckSum.h"
#include "../datasets/errors/BadNavProtocolVersion.h"
#include "../datasets/errors/BadAnswerProtocolVersion.h"

#include "../datasets/MinimalV2NavFrame.h"
#include "../datasets/MinimalV3AnsFrame.h"

class TestStdBinDecoderErrorRecovery : public ixblue_stdbin_decoder::StdBinDecoder , public testing::Test {
    /**
     * @brief used to assert if error recovery was successfully applied
     */
    void testNavFrameErrorRecovery(){
        this->addNewDataFrame(MINIMAL_V2_NAV_FRAME);
        ASSERT_NO_THROW(parseNextFrame()) << "Error recovery don't work.";
        ASSERT_EQ(this->internalBuffer.size(),0L);
    }

    /**
     * @brief used to assert if error recovery was successfully applied
     */
    void testAnswerFrameErrorRecovery(){
        this->addNewDataFrame(MINIMAL_V3_ANS_FRAME);
        ASSERT_NO_THROW(parseNextFrame()) << "Error recovery don't work.";
        ASSERT_EQ(this->internalBuffer.size(),0L);
    }
public:
    /**
     * @brief Add data using dataset values
     * @tparam T dataset inferred type
     * @param frame passed to add new data function
     */
    template<typename T> void addNewDataFrame(const T & frame){
        this->addNewData(frame.data(),frame.size());
    }

    /**
     * @brief used to assert if is error is thrown
     */
    void testIsErrorIsThrown(ssize_t cleaned_buffer_size){
        ASSERT_THROW(parseNextFrame(),std::runtime_error) << "Exception must be thrown in miss formatted data frame.";
        EXPECT_EQ(this->internalBuffer.size(),cleaned_buffer_size) << "Buffer must be cleaned.";
    }

    /**
     * @brief use multiple frame to test error recovery.
     * Add Nav data frame and parse it.
     * Add Answer data frame and parse it.
     */
    void testFramesErrorRecovery(){
        this->testNavFrameErrorRecovery();
        this->testAnswerFrameErrorRecovery();
    }

};
#endif //TEST_STD_BIN_DECODER_ERROR_RECOVERY_FEATURE_H
