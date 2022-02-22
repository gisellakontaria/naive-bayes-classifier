#include <catch2/catch.hpp>
#include <core/naive_bayes_model.h>

using naivebayes::Model;
using naivebayes::Image;

TEST_CASE("Model constructor test") {
    REQUIRE_NOTHROW(Model("data/tenimages.txt"));
}

TEST_CASE("Test invalid files") {
    SECTION("File doesn't exist") {
        REQUIRE_THROWS(std::invalid_argument("File doesn't exist"), Model("data/trainingimages"));
    }
}

TEST_CASE("Test if labels are parsed and added correctly into Image object, check if Image vector size is correct") {
    SECTION("One label added correctly to vector") {
        Model data("data/model_five.txt");

        REQUIRE(data.GetVectorSize() == 1);
        REQUIRE(data.GetTrainingImagesVector().at(0).GetLabel() == 5);
    }

    SECTION("Two labels added correctly to image") {
        Model data("data/twoimages.txt");

        REQUIRE(data.GetVectorSize() == 2);
        REQUIRE(data.GetTrainingImagesVector().at(0).GetLabel() == 5);
        REQUIRE(data.GetTrainingImagesVector().at(1).GetLabel() == 0);
    }

    SECTION("Ten elements added correctly to vector") {
        Model data("data/tenimages.txt");

        REQUIRE(data.GetVectorSize() == 10);
        REQUIRE(data.GetTrainingImagesVector().at(0).GetLabel() == 5);
        REQUIRE(data.GetTrainingImagesVector().at(1).GetLabel() == 0);
        REQUIRE(data.GetTrainingImagesVector().at(2).GetLabel() == 4);
        REQUIRE(data.GetTrainingImagesVector().at(3).GetLabel() == 1);
        REQUIRE(data.GetTrainingImagesVector().at(4).GetLabel() == 9);
        REQUIRE(data.GetTrainingImagesVector().at(5).GetLabel() == 2);
        REQUIRE(data.GetTrainingImagesVector().at(6).GetLabel() == 1);
        REQUIRE(data.GetTrainingImagesVector().at(7).GetLabel() == 3);
        REQUIRE(data.GetTrainingImagesVector().at(8).GetLabel() == 1);
        REQUIRE(data.GetTrainingImagesVector().at(9).GetLabel() == 4);
    }
}

TEST_CASE("Test if images are parsed and added correctly into vector from file ") {
    Model data("data/tenimages.txt");

    Image first_image("data/oneimage_five.txt");

    Image last_image("data/oneimage_four.txt");

    REQUIRE(data.GetTrainingImagesVector().size() == 10);
    REQUIRE(data.GetTrainingImagesVector().front() == first_image);
    REQUIRE(data.GetTrainingImagesVector().back() == last_image);
}


/*

You can (and should) create more test files; this project is too big
for all tests to be in the same file. Remember that, for each file (foo.cc)
containing non-trivial code, you should have a corresponding test file
(foo_test.cc)

Make sure to add any files that you create to CMakeLists.txt.

*/
