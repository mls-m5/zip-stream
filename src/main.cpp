//#include <boost/iostreams/filter/zlib.hpp>
#include <boost/iostreams/copy.hpp>
#include <boost/iostreams/filter/gzip.hpp>
#include <boost/iostreams/filtering_stream.hpp>
#include <fstream>
#include <iostream>
#include <sstream>

int main(int argc, char *argv[]) {
    using std::literals::operator""s;
    {
        auto file = std::ofstream{"test.gz"};
        auto out = boost::iostreams::filtering_ostream{};

        out.push(file);
        out.push(boost::iostreams::gzip_compressor{});

        auto str = "hello hello there\n"s;

        out << str;
    }

    {
        auto file = std::ifstream{"test.gz"};

        if (!file) {
            std::cout << "could not open file\n";
            std::terminate();
        }
        auto in = boost::iostreams::filtering_istream{};
        in.push(boost::iostreams::gzip_decompressor{});
        in.push(file);

        boost::iostreams::copy(in, std::cout);
        std::cout.flush();
    }

    return 0;
}
