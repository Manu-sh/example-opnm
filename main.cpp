#include <pnm/ppm/PPM.hpp>
#include <pnm/pgm/PGM.hpp>
#include <pnm/pbm/PBM.hpp>

#include <pnm/pnm.hpp>
#include <pnm/common.hpp>

#include <fstream>
#include <ios>
#include <string>

using std::literals::string_literals::operator""s;

static std::ifstream ifstream_open(const char *filename) {
    using std::ios_base;
    std::ifstream fpnm;
    fpnm.exceptions(ios_base::badbit);
    fpnm.open(filename, ios_base::in|ios_base::binary);
    if (!fpnm) throw std::invalid_argument{"Unable to open file: "s + filename};
    return fpnm;
}


int main() {

    PNM<pnm::monochrome_t> chessboard{1920, 1080};
    bool color = pnm::monochrome_t::BLACK;

    for (int h = 0; h < chessboard.height(); ++h, color = !color)
        for (int w = 0; w < chessboard.width(); ++w, color = !color)
            chessboard(h, w, color);

    chessboard.write_file_content("chessboard-bin.pbm");
    chessboard.write_file_content("chessboard-ascii.pbm", 1);

    {
        auto is = ifstream_open("chessboard-ascii.pbm");
        auto image = PNM<pnm::monochrome_t>::parse(is);
        image.write_file_content("out-chessboard-ascii.pbm", 1);
    }

    {
        auto is = ifstream_open("chessboard-bin.pbm");
        auto image = PNM<pnm::monochrome_t>::parse(is);
        image.write_file_content("out-chessboard-bin.pbm", 0);
    }


    PNM<pnm::monochrome_t> pbm{3, 2};

    pbm(0,0, {255, 0,   0}); // since bits aren't addressable you will use a different syntax

    // every pixel is converted to black or white after a grayscale conversion see here: https://github.com/Manu-sh/pnm/blob/master/include/pnm/pixels/monochrome.hpp#L15
    pbm(0,1, {0,   255, 0});
    pbm(0,2, {0,   255, 0});

    pbm(1,0, {255, 255, 0});
    pbm(1,1, {255, 255, 255});
    pbm(1,2, {0,   0,   0});

    pbm.write_file_content("bin.pbm");
    pbm.write_file_content("ascii.pbm", 1);

    {
        auto is = ifstream_open("ascii.pbm");
        auto image = PNM<pnm::monochrome_t>::parse(is);
        image.write_file_content("out-ascii-ascii.pbm", 1);
    }

    {
        auto is = ifstream_open("bin.pbm");
        auto image = PNM<pnm::monochrome_t>::parse(is);
        image.write_file_content("out-bin-bin.pbm", 0);
    }



    PNM<pnm::rgb<pnm::BIT_8>> ppm{3, 2};

    ppm(0,0) = {255, 0,   0};
    ppm(0,1) = {0,   255, 0};
    ppm(0,2) = {0,   0,   255};

    ppm(1,0) = {255, 255, 0};
    ppm(1,1) = {255, 255, 255};
    ppm(1,2) = {0,   0,   0};


    ppm.write_file_content("bin.ppm");
    ppm.write_file_content("ascii.ppm", 1);


    {
        auto is = ifstream_open("ascii.ppm");
        auto image = PNM<pnm::rgb<pnm::BIT_8>>::parse(is);
        image.write_file_content("out-ascii-ascii.ppm", 1);
    }

    {
        auto is = ifstream_open("bin.ppm");
        auto image = PNM<pnm::rgb<pnm::BIT_8>>::parse(is);
        image.write_file_content("out-bin-bin.ppm", 0);
    }



    PNM<pnm::grayscale<pnm::BIT_8>> pgm{3, 2};

    pgm(0,0) = {255, 0,   0};
    pgm(0,1) = {0,   255, 0};
    pgm(0,2) = {0,   0,   255};

    pgm(1,0) = {255, 255, 0};
    pgm(1,1) = {255, 255, 255};
    pgm(1,2) = {0,   0,   0};

    pgm.write_file_content("bin.pgm");
    pgm.write_file_content("ascii.pgm", 1);

    {
        auto is = ifstream_open("ascii.pgm");
        auto image = PNM<pnm::grayscale<pnm::BIT_8>>::parse(is);
        image.write_file_content("out-ascii-ascii.pgm", 1);
    }

    {
        auto is = ifstream_open("bin.pgm");
        auto image = PNM<pnm::grayscale<pnm::BIT_8>>::parse(is);
        image.write_file_content("out-bin-bin.pgm", 0);
    }

}
