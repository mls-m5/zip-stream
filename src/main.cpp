//#include <boost/iostreams/filter/zlib.hpp>
#include <boost/iostreams/copy.hpp>
#include <boost/iostreams/device/file.hpp>
#include <boost/iostreams/filter/gzip.hpp>
#include <boost/iostreams/filtering_stream.hpp>
#include <fstream>
#include <iostream>
#include <sstream>

int main(int argc, char *argv[]) {
    using std::literals::operator""s;
    {
        auto out = boost::iostreams::filtering_ostream{};
        out.push(boost::iostreams::gzip_compressor());
        out.push(boost::iostreams::file_sink{"test.gz"});

        auto str = "hello hello there!\n"s;

        out << str;
    }

    {

        auto in = boost::iostreams::filtering_istream{};
        in.push(boost::iostreams::gzip_decompressor{});
        in.push(boost::iostreams::file_source{"test.gz"});
        if (!in) {
            std::cout << "could not open file\n";
            std::terminate();
        }

        boost::iostreams::copy(in, std::cout);
        std::cout.flush();
    }

    return 0;
}
