//
// Created by Gisella Kontaria on 04/04/21.
//

#include <catch2/catch.hpp>
#include <core/image.h>

using naivebayes::Image;

TEST_CASE("Operator >> tests") {
    SECTION("Test if there is char '#' or '+' 0 will be changed to 1") {
        Image image("data/onetileshadedimage.txt");

        REQUIRE(image.image_vector_[0][0] == 1);
    }

    SECTION("Test if by default the 2D vector is filled with 0") {
        Image image("data/onetileshadedimage.txt");

        REQUIRE(image.image_vector_[0][1] == 0);
        REQUIRE(image.image_vector_[27][27] == 0);
    }
}

TEST_CASE("Operator == test") {
    Image image("data/oneimage_four.txt");
    Image copy("data/oneimage_four.txt");

    REQUIRE(image == copy);
}