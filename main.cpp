#include <pnm/ppm/PPM.hpp>
#include <pnm/pgm/PGM.hpp>
#include <pnm/pbm/PBM.hpp>

#include <pnm/pnm.hpp>
#include <pnm/common.hpp>

int main() {

	PNM<pnm::monochrome_t> chessboard{1920, 1080};
	bool color = pnm::monochrome_t::BLACK;

	for (int h = 0; h < chessboard.height(); ++h, color = !color)
	    for (int w = 0; w < chessboard.width(); ++w, color = !color)
		chessboard(h, w, color);

	chessboard.write_file_content("chessboard-bin.pbm");
	chessboard.write_file_content("chessboard-ascii.pbm", 1);

	PNM<pnm::monochrome_t> pbm{3, 2};

	pbm(0,0, {255, 0,   0}); // since bits aren't addressable you will use a different syntax
	pbm(0,1, {0,   255, 0});
	pbm(0,2, {0,   255, 0});

	pbm(1,0, {255, 255, 0});
	pbm(1,1, {255, 255, 255});
	pbm(1,2, {0,   0,   0});

	pbm.write_file_content("bin.pbm");
	pbm.write_file_content("ascii.pbm", 1);

	PNM<pnm::rgb<pnm::BIT_8>> ppm{3, 2};

	ppm(0,0) = {255, 0,   0};
	ppm(0,1) = {0,   255, 0};
	ppm(0,2) = {0,   0,   255};

	ppm(1,0) = {255, 255, 0};
	ppm(1,1) = {255, 255, 255};
	ppm(1,2) = {0,   0,   0};


	ppm.write_file_content("bin.ppm");
	ppm.write_file_content("ascii.ppm", 1);

	PNM<pnm::grayscale<pnm::BIT_8>> pgm{3, 2};

	pgm(0,0) = {255, 0,   0};
	pgm(0,1) = {0,   255, 0};
	pgm(0,2) = {0,   0,   255};

	pgm(1,0) = {255, 255, 0};
	pgm(1,1) = {255, 255, 255};
	pgm(1,2) = {0,   0,   0};

	pgm.write_file_content("bin.pgm");
	pgm.write_file_content("ascii.pgm", 1);

}
