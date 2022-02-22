//
// Created by Gisella Kontaria on 13/04/21.
//

#include <catch2/catch.hpp>
#include <visualizer/sketchpad.h>

using naivebayes::visualizer::Sketchpad;

TEST_CASE("Test if vector is initialized to all 0") {
    vector<vector<size_t>> vec_{28 , vector<size_t>(28, 0)};

    for (size_t row = 0; row < 28; row++) {
        for (size_t col = 0; col < 28; col++) {
            REQUIRE(vec_[row][col] == 0);
        }
    }
}

TEST_CASE("Test if vector clears") {
    Sketchpad sketchpad(glm::vec2(0,0),28,100,1.15);
    sketchpad.Clear();

    for (size_t row = 0; row < 28; row++) {
        for (size_t col = 0; col < 28; col++) {
            REQUIRE(sketchpad.vec_[row][col] == 0);
        }
    }
}

TEST_CASE("Test if HandleBrush method shades a pixel") {
    Sketchpad sketchpad(glm::vec2(0,0),28,100,1.15);
    sketchpad.HandleBrush(glm::vec2(0,0));

    REQUIRE(sketchpad.vec_[0][0] == 1);
}