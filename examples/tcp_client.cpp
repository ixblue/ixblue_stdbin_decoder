#include <array>
#include <chrono>
#include <iomanip>
#include <iostream>
#include <limits>
#include <string>

#include <boost/asio.hpp>

#include <ixblue_stdbin_decoder/stdbin_decoder.h>

using boost::asio::ip::tcp;

int main(int argc, char** argv)
{
    if(argc < 2)
    {
        std::cerr << "USAGE: tcp_client <host> <port>\n";
        return 1;
    }

    boost::asio::io_service io;

    tcp::resolver resolver(io);
    tcp::resolver::query query(tcp::v4(), argv[1], argv[2]);
    tcp::resolver::iterator iterator = resolver.resolve(query);

    std::cout << "Connecting to TCP server " << argv[1] << " on port " << argv[2] << '\n';

    tcp::socket socket{io};

    try
    {
        boost::asio::connect(socket, iterator);
    }
    catch(const boost::system::system_error& e)
    {
        std::cerr << "Failed to connect to the socket: " << e.what();
        return 1;
    }

    std::array<uint8_t, 9000> recvBuffer;
    ixblue_stdbin_decoder::StdBinDecoder decoder;
    auto lastPrint = std::chrono::steady_clock::now();
    try
    {
        while(true)
        {
            const auto bytesRead = socket.read_some(boost::asio::buffer(recvBuffer));

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
                    else
                    {
                        std::cout
                            << "Last nav frame received does not contain position\n";
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
