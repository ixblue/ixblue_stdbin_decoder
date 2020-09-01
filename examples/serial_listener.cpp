#include <chrono>
#include <iomanip>
#include <iostream>
#include <limits>
#include <vector>

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

    socket.open(argv[1]);
    using serial = boost::asio::serial_port_base;
    socket.set_option(serial::baud_rate{});
    socket.set_option(serial::character_size{8});
    socket.set_option(serial::parity{serial::parity::odd});
    socket.set_option(serial::stop_bits{serial::stop_bits::two});
    socket.set_option(serial::flow_control{serial::flow_control::none});

    std::vector<uint8_t> data(9000);
    ixblue_stdbin_decoder::StdBinDecoder decoder;
    auto lastPrint = std::chrono::steady_clock::now();

    std::cout << "Listening on serial port " << argv[1] << "...\n";

    while(true)
    {
        const auto bytesRead = boost::asio::read(socket, boost::asio::buffer(data),
                                                 boost::asio::transfer_at_least(200));
        std::cout << "Received " << bytesRead << " bytes\n";
        if(decoder.parse(data))
        {
            if((std::chrono::steady_clock::now() - lastPrint) > std::chrono::seconds{1})
            {
                const auto nav = decoder.getLastNavData();
                if(nav.position.is_initialized())
                {
                    std::cout << "Position: \n"
                              << std::fixed << std::setprecision(9)
                              << "  lat: " << nav.position->latitude_deg << " deg\n"
                              << "  lon: " << nav.position->longitude_deg << "deg\n"
                              << std::setprecision(2)
                              << "  alt: " << nav.position->altitude_m << " m\n";
                    lastPrint = std::chrono::steady_clock::now();
                }
            }
        }
        else
        {
            std::cout << "Failed to parse\n";
        }
    }
}
