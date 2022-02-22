//
// Created by Gisella Kontaria on 11/04/21.
//

#include <core/naive_bayes_classifier.h>
#include <vector>
#include <string>
#include <fstream>
#include <iostream>

using std::vector;
using std::string;

namespace naivebayes {

Classifier::Classifier(string file_name) {
  Model data = Model(file_name);
  CountProbabilites(data);
  // SaveProbabilitiesToFile("data/savedpriors.txt", "data/savedprobabilities.txt");
  CalculateAccuracy(data);
  std::cout << "Accuracy = " << classifier_accuracy_ <<std::endl;
}

Classifier::Classifier(string saved_priors_file, string saved_prob_file) {
  ReadProbabilitiesFromFile(saved_priors_file, saved_priors_file);
}

size_t Classifier::ClassifyImage(Image image_to_classify) {
  likelihood_score_vector_.clear();
  for (size_t class_value = 0; class_value < kTotalPossibleClasses; class_value++) {
    double probability = 0;
    probability += log(prior_probabilities_vector_.at(class_value));
    for (size_t row = 0; row < kImageSize; row++) {
      for (size_t col = 0; col < kImageSize; col++) {
        size_t shading = image_to_classify.image_vector_[row][col];
        probability += log(feature_probabilities_vec_[row][col][class_value][shading]);
      }
    }
    likelihood_score_vector_.push_back(probability);
  }
  double max_likelihood_score = likelihood_score_vector_.at(0);
  size_t predicted_class = 0;
  for (size_t class_value = 0; class_value < kTotalPossibleClasses; class_value++) {
    if (likelihood_score_vector_.at(class_value) > max_likelihood_score) {
      max_likelihood_score = likelihood_score_vector_.at(class_value);
      predicted_class = class_value;
    }
  }
  return predicted_class;
}

void Classifier::CountProbabilites(Model& data) {
  // calculate prior probabilities
  for (size_t label = 0; label < kTotalPossibleClasses; label++) {
    prior_probabilities_vector_.push_back(CalculatePriorProbabilityHelper(label, data));
  }

  // calculate feature probabilities
  for (size_t row = 0; row < kImageSize; row++) {
    for (size_t col = 0; col < kImageSize; col++) {
      for (size_t class_value = 0; class_value < kTotalPossibleClasses; class_value++) {
        for (size_t shading = 0; shading < kPossibleShadings; shading++) {
          feature_probabilities_vec_[row][col][class_value][shading] = CalculateFeatureProbabilityHelper(class_value, shading, row, col, data);
        }
      }
    }
  }
}

void Classifier::CalculateAccuracy(Model& data) {
  size_t accurate_prediction_count = 0;
  for (size_t count = 0; count < data.GetVectorSize(); count++) {
    if (data.GetTrainingImagesVector().at(count).GetLabel() == ClassifyImage(data.GetTrainingImagesVector().at(count))) {
      accurate_prediction_count++;
    }
  }
  classifier_accuracy_ = ((double) accurate_prediction_count / data.GetVectorSize()) * 100;
}

void Classifier::SaveProbabilitiesToFile(string& prior_prob_file, string& feature_prob_file) {
  std::ofstream out;

  // save prior probability
  out.open(prior_prob_file);
  if (!out) {
    throw std::invalid_argument("File doesn't exist");
  }
  for (auto prior_probability : prior_probabilities_vector_) {
    out << prior_probability << std::endl;
  }
  out.close();

  // save feature probability
  out.open(feature_prob_file);
  if (!out) {
    throw std::invalid_argument("File doesn't exist");
  }
  for (size_t class_value = 0; class_value < kTotalPossibleClasses; class_value++) {
    out << std::endl << "Label = " << class_value;
    for (size_t shading = 0; shading < kPossibleShadings; shading++) {
      out << std::endl << "Shading = " << shading << std::endl;
      for (size_t row = 0; row < kImageSize; row++) {
        for (size_t col = 0; col < kImageSize; col++) {
          out << feature_probabilities_vec_[row][col][class_value][shading] << kSpacing;
        }
        out << std::endl;
      }
    }
  }
  out.close();
}

void Classifier::ReadProbabilitiesFromFile(string& prior_prob_file, string& feature_prob_file) {
  std::ifstream in;

  // read prior probability
  in.open(prior_prob_file);
  if (!in) {
    throw std::invalid_argument("Prior probability file cannot be opened");
  }
  double prior_probability;
  while (in >> prior_probability) {
    prior_probabilities_vector_.push_back(prior_probability);
  }
  in.close();

  // read feature probability
  in.open(feature_prob_file);
  if (!in) {
    throw std::invalid_argument("Feature probability file cannot be opened");
  }

  for (size_t class_value = 0; class_value < kTotalPossibleClasses; class_value++) {
    for (size_t shading = 0; shading < kPossibleShadings; shading++) {
      for (size_t row = 0; row < kImageSize; row++) {
        for (size_t col = 0; col < kImageSize; col++) {
          while (!in.eof()) {
            string line;
              std::getline(in, line);
                if (line.empty()) {
                  break;
                }
                if (line.length() < 28) {
                  continue;
                }
                double feature_probability;
                in >> feature_probability;
                feature_probabilities_vec_[row][col][class_value][shading] = feature_probability;
          }
        }
      }
    }
  }
  in.close();
}

double Classifier::CalculatePriorProbabilityHelper(size_t class_value, Model& data) {
  // count occurences for each label
  size_t count = 0;
  for (size_t label = 0; label < data.GetVectorSize(); label++) {
    if (class_value == data.GetTrainingImagesVector().at(label).GetLabel()) {
      count++;
    }
  }

  // return the prior probability
  return ((double) kLaplaceConstant + (double) count)
    / (kTotalPossibleClasses * kLaplaceConstant + data.GetVectorSize());
}

double Classifier::CalculateFeatureProbabilityHelper(size_t class_value, size_t shading, size_t row, size_t col, Model& data) {
  size_t count_image_in_class = 0;
  size_t count_tile_with_appropriate_shading = 0;

  for (size_t i = 0; i < data.GetVectorSize(); i++) {
    if (data.GetTrainingImagesVector().at(i).GetLabel() == class_value) {
      count_image_in_class++;
      if (data.GetTrainingImagesVector().at(i).image_vector_[row][col] == shading) {
        count_tile_with_appropriate_shading++;
      }
    }
 }

  return ((double) kLaplaceConstant + count_tile_with_appropriate_shading)
    / ((double) 2 * kLaplaceConstant + count_image_in_class);
}

const vector<vector<vector<vector<double>>>>& Classifier::GetFeatureProbabilitiesVector() const {
  return feature_probabilities_vec_;
}

const vector<double>& Classifier::GetPriorProbabilitiesVector() const {
  return prior_probabilities_vector_;
}

const double & Classifier::GetClassifierAccuracy() const {
  return classifier_accuracy_;
}

const vector<double> & Classifier::GetLikelihoodScoreVector() const {
  return likelihood_score_vector_;
}

}