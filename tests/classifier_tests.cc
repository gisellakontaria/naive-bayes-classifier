//
// Created by Gisella Kontaria on 11/04/21.
//

#include <catch2/catch.hpp>
#include <core/naive_bayes_classifier.h>

using naivebayes::Model;
using naivebayes::Image;
using naivebayes::Classifier;

TEST_CASE("Classifier constructor test") {
    Classifier data("data/tenimages.txt");

    SECTION("Feature probability vector initialized") {
        REQUIRE(!data.GetFeatureProbabilitiesVector().empty());
        REQUIRE(data.GetFeatureProbabilitiesVector().size() == 28);
    }

    SECTION("Prior probability vector initialized") {
        REQUIRE(!data.GetPriorProbabilitiesVector().empty());
        REQUIRE(data.GetPriorProbabilitiesVector().size() == 10);
    }

    SECTION("Likelihood score vector initialized") {
        REQUIRE(!data.GetLikelihoodScoreVector().empty());
        REQUIRE(data.GetLikelihoodScoreVector().size() == 10);
    }
}

TEST_CASE("Count probabilities test") {
    SECTION("Prior probability calculations") {
        Classifier data("data/model_five.txt");

        REQUIRE(data.GetPriorProbabilitiesVector().at(0) == Approx(0.091).epsilon(0.001));
        REQUIRE(data.GetPriorProbabilitiesVector().at(1) == Approx(0.091).epsilon(0.001));
        REQUIRE(data.GetPriorProbabilitiesVector().at(2) == Approx(0.091).epsilon(0.001));
        REQUIRE(data.GetPriorProbabilitiesVector().at(3) == Approx(0.091).epsilon(0.001));
        REQUIRE(data.GetPriorProbabilitiesVector().at(4) == Approx(0.091).epsilon(0.001));
        REQUIRE(data.GetPriorProbabilitiesVector().at(5) == Approx(0.182).epsilon(0.001));
        REQUIRE(data.GetPriorProbabilitiesVector().at(6) == Approx(0.091).epsilon(0.001));
        REQUIRE(data.GetPriorProbabilitiesVector().at(7) == Approx(0.091).epsilon(0.001));
        REQUIRE(data.GetPriorProbabilitiesVector().at(8) == Approx(0.091).epsilon(0.001));
        REQUIRE(data.GetPriorProbabilitiesVector().at(9) == Approx(0.091).epsilon(0.001));
    }

    SECTION("Feature probability calculations") {
        Classifier data("data/trainingimagesandlabels.txt");

        REQUIRE(!data.GetFeatureProbabilitiesVector().empty());
        // check if the perimeters have the same probabilities, they should all be unshaded always
        REQUIRE(data.GetFeatureProbabilitiesVector()[0][0][0][0] == Approx(0.99792).epsilon(0.00001));
        REQUIRE(data.GetFeatureProbabilitiesVector()[27][27][9][0] == Approx(0.99799).epsilon(0.00001));
    }

    SECTION("Check if probabilities for all classes values are added properly to vector") {
        Classifier data("data/trainingimagesandlabels.txt");

        REQUIRE(data.GetPriorProbabilitiesVector().size() == 10);
        REQUIRE(data.GetFeatureProbabilitiesVector().size() == 28);
    }
}

TEST_CASE("Testing image classification") {
    Image image("data/oneimage_five.txt");
    Classifier data("data/trainingimagesandlabels.txt");

    SECTION("Test if the image is classified correctly") {
        double predicted_class = data.ClassifyImage(image);
        REQUIRE(predicted_class == 5);
    }
}

TEST_CASE("Testing accuracy calculation") {
    Classifier data("data/trainingimagesandlabels.txt");

    SECTION("Test if accuracy is beyond 0.7") {
        REQUIRE(data.GetClassifierAccuracy() >= 0.7);
    }

    SECTION("Test if likelihood score vector correspond to predicted class") {
        REQUIRE(data.GetLikelihoodScoreVector().size() == 10);
        REQUIRE(data.GetLikelihoodScoreVector().at(0) == Approx(-361.50).epsilon(0.01));
        REQUIRE(data.GetLikelihoodScoreVector().at(1) == Approx(-303.04).epsilon(0.01));
        REQUIRE(data.GetLikelihoodScoreVector().at(2) == Approx(-195.24).epsilon(0.01));
        REQUIRE(data.GetLikelihoodScoreVector().at(3) == Approx(-271.90).epsilon(0.01));
        REQUIRE(data.GetLikelihoodScoreVector().at(4) == Approx(-260.99).epsilon(0.01));
        REQUIRE(data.GetLikelihoodScoreVector().at(5) == Approx(-268.43).epsilon(0.01));
        REQUIRE(data.GetLikelihoodScoreVector().at(6) == Approx(-260.44).epsilon(0.01));
        REQUIRE(data.GetLikelihoodScoreVector().at(7) == Approx(-338.05).epsilon(0.01));
        REQUIRE(data.GetLikelihoodScoreVector().at(8) == Approx(-215.35).epsilon(0.01));
        REQUIRE(data.GetLikelihoodScoreVector().at(9) == Approx(-265.83).epsilon(0.01));
    }
}

TEST_CASE("Testing reading probabilities from saved file") {
    Classifier data("data/savedpriors_test.txt","data/savedprobabilities_test.txt");

    REQUIRE(data.GetPriorProbabilitiesVector().size() == 10);
    REQUIRE(data.GetPriorProbabilitiesVector().at(0) == 0.0909091);
    REQUIRE(data.GetFeatureProbabilitiesVector()[0][0][0][0] == 0.5);
}
