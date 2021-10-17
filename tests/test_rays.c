#include <stdlib.h>
#include "ctest.h"
#include "../src/bitboard.h"
#include "../src/rays.h"

CTEST(ray_generation, rays_north) {
    initRays();
    enum Square sq = SQ_B2;
    Board exp = 0x0202020202020000;
    ASSERT_EQUAL(exp, rays[NORTH][sq]);
};

CTEST(ray_generation, rays_south) {
    initRays();
    enum Square sq = SQ_E8;
    Board exp = 0x0010101010101010;
    ASSERT_EQUAL(exp, rays[SOUTH][sq]);
};

CTEST(ray_generation, rays_east) {
    initRays();
    enum Square sq = SQ_C5;
    Board exp = 0x000000F800000000;
    ASSERT_EQUAL(exp, rays[EAST][sq]);
};

CTEST(ray_generation, rays_west) {
    initRays();
    enum Square sq = SQ_H1;
    Board exp = 0x000000000000007F;
    ASSERT_EQUAL(exp, rays[WEST][sq]);
}

CTEST(ray_generation, rays_north_west) {
    initRays();
    enum Square sq = SQ_C4;
    Board exp = 0x0000040800000000 >> 2;
    ASSERT_EQUAL(exp, rays[NORTH_WEST][sq]);
}

CTEST(ray_generation, rays_north_east) {
    initRays();
    enum Square sq = SQ_C4;
    //Board exp = 0x8040201000000000 >> 1;
    Board exp = (A1_H8_DIAGONAL >> 1) & ~A_FILE & ~B_FILE & ~C_FILE;
    ASSERT_EQUAL(exp, rays[NORTH_EAST][sq]);
}

CTEST(ray_generation, rays_south_west) {
    initRays();
    enum Square sq = SQ_C4;
    Board exp = 0x0000000000040201 >> 1;
    ASSERT_EQUAL(exp, rays[SOUTH_WEST][sq]);
}

CTEST(ray_generation, rays_south_east) {
    initRays();
    enum Square sq = SQ_C4;
    Board exp = 0x0000000000204080 >> 2;
    ASSERT_EQUAL(exp, rays[SOUTH_EAST][sq]);
}

CTEST(ray_generation, rays_north_on_border) {
    initRays();
    enum Square sq = SQ_E8;
    Board exp = 0x0;
    ASSERT_EQUAL(exp, rays[NORTH][sq]);
};

CTEST(ray_generation, rays_south_on_border) {
    initRays();
    enum Square sq = SQ_A1;
    Board exp = 0x0;
    ASSERT_EQUAL(exp, rays[SOUTH][sq]);
};

CTEST(ray_generation, rays_east_on_border) {
    initRays();
    enum Square sq = SQ_H6;
    Board exp = 0x0;
    ASSERT_EQUAL(exp, rays[EAST][sq]);
};

CTEST(ray_generation, rays_west_on_border) {
    initRays();
    enum Square sq = SQ_A7;
    Board exp = 0x0;
    ASSERT_EQUAL(exp, rays[WEST][sq]);
}

CTEST(ray_generation, rays_north_west_on_border) {
    initRays();
    enum Square sq = SQ_A1;
    Board exp = 0x0;
    ASSERT_EQUAL(exp, rays[NORTH_WEST][sq]);
};

CTEST(ray_generation, rays_south_west_on_border) {
    initRays();
    enum Square sq = SQ_H1;
    Board exp = 0x0;
    ASSERT_EQUAL(exp, rays[SOUTH_WEST][sq]);
};

CTEST(ray_generation, rays_north_east_on_border) {
    initRays();
    enum Square sq = SQ_H1;
    Board exp = 0x0;
    ASSERT_EQUAL(exp, rays[NORTH_EAST][sq]);
};

CTEST(ray_generation, rays_south_east_on_border) {
    initRays();
    enum Square sq = SQ_A1;
    Board exp = 0x0;
    ASSERT_EQUAL(exp, rays[SOUTH_EAST][sq]);
}