#include <array>
#include <chrono>
#include <iomanip>
#include <iostream>
#include <limits>

#include <boost/asio.hpp>

#include <ixblue_stdbin_decoder/stdbin_decoder.h>

using boost::asio::ip::udp;

int main(int argc, char** argv)
{
    if(argc < 2)
    {
        std::cerr << "USAGE: udp_listener <port>\n";
        return 1;
    }

    const int port = std::atoi(argv[1]);
    if(port <= 0 || port > std::numeric_limits<uint16_t>::max())
    {
        std::cerr << "Port (=" << port << ") must be between 1 and "
                  << std::numeric_limits<uint16_t>::max() << '\n';
        return 1;
    }

    boost::asio::io_service io;
    udp::socket socket{io, udp::endpoint(udp::v4(), port)};

    std::array<uint8_t, 9000> recvBuffer;
    udp::endpoint senderEndpoint;
    ixblue_stdbin_decoder::StdBinDecoder decoder;
    auto lastPrint = std::chrono::steady_clock::now();

    std::cout << "Listening on UDP port " << port << "...\n";

    try
    {
        while(true)
        {
            const auto bytesRead =
                socket.receive_from(boost::asio::buffer(recvBuffer), senderEndpoint);
            decoder.addNewData(recvBuffer.data(), bytesRead);
            while(decoder.parseNextFrame())
            {
                if((std::chrono::steady_clock::now() - lastPrint) >
                   std::chrono::seconds{1})
                {
                    const auto nav = decoder.getLastNavData();
                    if(nav.position.is_initialized())
                    {
                        std::cout << "Position: \n"
                                  << std::fixed << std::setprecision(9)
                                  << "  lat: " << nav.position->latitude_deg << " deg\n"
                                  << "  lon: " << nav.position->longitude_deg << " deg\n"
                                  << std::setprecision(2)
                                  << "  alt: " << nav.position->altitude_m << " m\n";
                        lastPrint = std::chrono::steady_clock::now();
                    }
                }
            }
        }
    }
    catch(const std::runtime_error& e)
    {
        std::cerr << "Parser error: " << e.what() << '\n';
        return 1;
    }
}
