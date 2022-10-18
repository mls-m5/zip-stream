//#include <boost/iostreams/filter/zlib.hpp>
#include <boost/iostreams/copy.hpp>
#include <boost/iostreams/device/file.hpp>
#include <boost/iostreams/filter/gzip.hpp>
#include <boost/iostreams/filtering_stream.hpp>
#include <fstream>
#include <iostream>
#include <memory>

std::shared_ptr<std::ostream> createSink() {
    auto out = std::make_unique<boost::iostreams::filtering_ostream>();
    out->push(boost::iostreams::gzip_compressor());
    out->push(boost::iostreams::file_sink{"test.gz"});
    return out;
}

std::shared_ptr<std::istream> createSource() {

    auto in = std::make_unique<boost::iostreams::filtering_istream>();
    in->push(boost::iostreams::gzip_decompressor{});
    in->push(boost::iostreams::file_source{"test.gz"});
    if (!in) {
        std::cout << "could not open file\n";
        std::terminate();
    }
    return in;
}

int main(int argc, char *argv[]) {
    using std::literals::operator""s;
    {
        auto out = createSink();
        auto str = "hello hello there!\n"s;
        *out << str;
    }

    {
        auto in = createSource();
        boost::iostreams::copy(*in, std::cout);
        std::cout.flush();
    }

    return 0;
}
