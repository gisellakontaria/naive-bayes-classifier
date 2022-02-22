//
// Created by Gisella Kontaria on 11/04/21.
//

#ifndef NAIVE_BAYES_NAIVE_BAYES_CLASSIFIER_H
#define NAIVE_BAYES_NAIVE_BAYES_CLASSIFIER_H

#include <vector>
#include <string>
#include <cmath>
#include "naive_bayes_model.h"


using std::vector;
using std::string;

namespace naivebayes {

/***
* Class that stores all probabilities and does classification of data
*/
class Classifier {

public:
 /***
  * Classifier constructor taking in a file, trains it into a model, and count the probabilities
  * @param file_name to be read from
  */
  Classifier(string file_name);

 /***
  * Classifier constructor that reads data from previously saved file
  * @param saved_priors_file File storing priors probability
  * @param string File storing feature probability
  */
  Classifier(string saved_priors_file, string saved_prob_file);

 /***
   * Function that takes in an Image object and classifies it
   * @param image_to_classify Image to be classified into one of the labels
   * @return predicted label that the Image belongs to
   */
  size_t ClassifyImage(Image image_to_classify);

 /***
  * Function that calculates the accuracy of classifier
  * @param data is testing data
  */
  void CalculateAccuracy(Model& data);

 /***
  * Function that counts feature and prior probabilities of a training model
  * @param data
  */
  void CountProbabilites(Model& data);

 /***
  * Function that saves probabilities to a file
  * @param prior_prob_file to save prior probabilities to
  * @param feature_prob_file to save feature probabilities to
  */
  void SaveProbabilitiesToFile(string& prior_prob_file, string& feature_prob_file);

 /***
  * Function that reads probabilities from text
  * @param prior_prob_file file to read prior probabilities from
  * @param feature_prob_file to read feature probabilities from
  */
  void ReadProbabilitiesFromFile(string& prior_prob_file, string& feature_prob_file);

  // Getters
  const vector<double>& GetPriorProbabilitiesVector() const ;

  const vector<vector<vector<vector<double>>>>& GetFeatureProbabilitiesVector() const;

  const double& GetClassifierAccuracy() const;

  const vector<double>& GetLikelihoodScoreVector() const ;

private:
  const size_t kTotalPossibleClasses = 10;

  const size_t kImageSize = 28;

  const double kPossibleShadings = 2;

  const double kLaplaceConstant = 1;

  char kSpacing = ' ';

  double classifier_accuracy_;

  // 4D vector that stores the feature probability of each tile in format: vector[class_value][shading][row][col]
  vector<vector<vector<vector<double>>>> feature_probabilities_vec_{kImageSize, {kImageSize, {kTotalPossibleClasses, {kPossibleShadings, 0}}}};

  // vector storing the probability of a class value (0-9) occuring
  vector<double> prior_probabilities_vector_;

  // vector storing likelihood score of each label in a given image
  vector<double> likelihood_score_vector_;

  // helper function that calculates feature probability of certain class value, shaded/unshaded, at F(i,j) position
  double CalculateFeatureProbabilityHelper(size_t class_value, size_t shading, size_t row, size_t col, Model& data);

  // helper function that calculates probability of a certain class value
  double CalculatePriorProbabilityHelper(size_t class_value, Model& data);

};

}

#endif //NAIVE_BAYES_NAIVE_BAYES_CLASSIFIER_H
