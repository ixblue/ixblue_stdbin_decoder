#pragma once

#include "data_models/nav_header.h"
#include "data_models/stdbin.h"
#include "memory_block_parser.h"

#include <boost/circular_buffer.hpp>
#include <boost/noncopyable.hpp>

#include <functional>
#include <set>

namespace ixblue_stdbin_decoder
{

/*!
 * \brief Parser of a STDBIN IXblue message.
 * This is the entry point of the library. Usage of this class is as follow :
 * \code
 * StdBinDecoder parser;
 * ///...
 * try{
 *   if(parser.parse(buffer)) {
 *     auto navDatas = parser.getLastMessage();
 *   }
 * }catch(std::runtime_error& e){
 *   // Parsing error are reported by throwing std::runtime_exception.
 * }
 * \endcode
 * parse method can be called with a partial buffer. Data will be agglomerated until the
 * full frame have been received.
 */
class StdBinDecoder : private boost::noncopyable
{
    // we sort the parsers list by offsetMask because this is a design constraint. We need
    // to process parser in the same order than data are filled in memory.
    typedef std::set<
        MemoryBlockParserPtr,
        std::function<bool(const MemoryBlockParserPtr&, const MemoryBlockParserPtr&)>>
        tParsersSet;

    static constexpr size_t HEADER_SIZE_V2 = 21;
    static constexpr size_t HEADER_SIZE_V3 = 25;
    static constexpr size_t HEADER_SIZE_V4 = 27;
    static constexpr size_t HEADER_SIZE_V5 = 27;
    static constexpr size_t ANSWER_HEADER_SIZE = 5;
    static constexpr size_t CHECKSUM_SIZE = 4;

public:
    StdBinDecoder();

    /*!
     * \brief Add new binary data to the parser internal buffer
     * The new data can only be a part of a frame, the parser will manage to assemble
     * the several parts in order to decode it
     * \param data a pointer to a contiguous memory buffer
     * \param length the amount of bytes to read from the buffer
     */
    void addNewData(const uint8_t* data, std::size_t length);

    /*!
     * \brief Add new binary data to the parser internal buffer
     * The new data can only be a part of a frame, the parser will manage to assemble
     * the several parts in order to decode it
     * \param data a std::vector containing data to copy into the internal buffer
     * \warning The vector must be full of received bytes because it will be entirely
     * copied to the internal buffer.
     * If the vector is only partially filled, use the other oveload:
     * \code{.cpp}
     * std::vector<uint8_t> buf(2000);
     * std::size_t byteRead = socket.read(buf);
     * // here, the buf only contains byteRead valid bytes
     * parser.addNewData(buf.data(), bytesRead);
     * \endcode
     */
    void addNewData(const std::vector<uint8_t>& data);

    /*!
     * \brief Try to parse a frame from the parser internal buffer.
     * Some binary data must have been added with the \c addNewData() method beforehand.
     * This method is able to handle buffer with header at the middle of the frame as
     * found on connection-less communication like serial port (RS-232).
     * \return true if the frame has been completly parsed, false otherwise.
     * If frame has been parsed, result is accessible via \c getLastNavData();
     * \exception runtime_error if a parse error occurs.
     */
    bool parseNextFrame();

    Data::BinaryNav getLastNavData(void) const { return lastParsed; }
    Data::NavHeader getLastHeaderData(void) const { return lastHeader; }
    const std::vector<uint8_t>& getLastAnswerData(void) const { return lastAnswer; }

protected:
    /*!
     * \exception runtime_error if a parse error occurs.
     */
    Data::NavHeader parseHeader(boost::asio::const_buffer& buffer) const;
    Data::NavHeader::MessageType getHeaderType(boost::asio::const_buffer& buffer) const;
    bool haveEnoughBytesToParseHeader();
    /*!
     * \brief Compute current frame checksum and compare with the frame checksum.
     * If mismatch, throw \c std::runtime_error exception.
     * \exception runtime_error if bad checksum
     */
    void compareChecksum();
    // We set the parsers set "constant" to be sure that the content of this set will be
    // the same during all the lifetime of this object. We can only add memory bloc parser
    // at construction.
    const tParsersSet navigationParsers;
    const tParsersSet extendedNavigationParsers;
    const tParsersSet externalDataParsers;

    Data::BinaryNav lastParsed;
    Data::NavHeader lastHeader;
    std::vector<uint8_t> lastAnswer;

    // We store in this buffer the current frame's data. This memory chunk is managed by
    // the parsing state machine. See function \c parse.
    boost::circular_buffer<uint8_t> internalBuffer;
};
} // namespace ixblue_stdbin_decoder
