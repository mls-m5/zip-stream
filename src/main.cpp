//#include <boost/iostreams/filter/zlib.hpp>
#include <boost/iostreams/copy.hpp>
#include <boost/iostreams/filter/gzip.hpp>
#include <boost/iostreams/filtering_streambuf.hpp>
#include <fstream>
#include <iostream>
#include <sstream>

int main(int argc, char *argv[]) {
    using std::literals::operator""s;
    {
        auto file = std::ofstream{"test.gz"};
        auto out =
            boost::iostreams::filtering_streambuf<boost::iostreams::output>{};

        out.push(boost::iostreams::gzip_compressor{});
        out.push(file);

        auto str = "hello there\n"s;

        auto ss = std::stringstream{};
        ss << str;
        boost::iostreams::copy(ss, out);
    }

    {
        auto file = std::ifstream{"test.gz"};

        if (!file) {
            std::cout << "could not open file\n";
            std::terminate();
        }
        auto in =
            boost::iostreams::filtering_streambuf<boost::iostreams::input>{};
        in.push(boost::iostreams::gzip_decompressor{});
        in.push(file);

        boost::iostreams::copy(in, std::cout);
        std::cout.flush();
    }

    return 0;
}
