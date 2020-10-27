#include <array>
#include <chrono>
#include <iomanip>
#include <iostream>
#include <limits>

#include <boost/asio.hpp>

#include <ixblue_stdbin_decoder/stdbin_decoder.h>

int main(int argc, char** argv)
{
    if(argc < 3)
    {
        std::cerr << "USAGE: serial_listener <port> <baudrate>\n\n"
                  << " Note: The serial setting should be Odd Parity and 2 stop bits.\n";
        return 1;
    }

    const int baudrate = std::atoi(argv[2]);
    if(baudrate <= 0)
    {
        std::cerr << "Bad baudrate (=" << baudrate << "\n";
        return 1;
    }

    boost::asio::io_service io;
    boost::asio::serial_port socket{io};

    try
    {
        socket.open(argv[1]);
    }
    catch(const boost::system::system_error& e)
    {
        std::cerr << "Failed to open the serial port: " << e.what();
        return 1;
    }

    using serial = boost::asio::serial_port_base;
    socket.set_option(serial::baud_rate(baudrate));
    socket.set_option(serial::character_size{8});
    socket.set_option(serial::parity{serial::parity::odd});
    socket.set_option(serial::stop_bits{serial::stop_bits::two});
    socket.set_option(serial::flow_control{serial::flow_control::none});

    std::array<uint8_t, 8192> recvBuffer;
    ixblue_stdbin_decoder::StdBinDecoder decoder;

    std::cout << "Listening on serial port " << argv[1] << "...\n";

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
