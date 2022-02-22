//
// Created by Gisella Kontaria on 03/04/21.
//

#ifndef NAIVE_BAYES_NAIVE_BAYES_MODEL_H
#define NAIVE_BAYES_NAIVE_BAYES_MODEL_H

#include <vector>
#include <string>
#include "image.h"

using std::vector;
using std::string;

namespace naivebayes {

/***
 * Class that trains a given data read from a file
 * Does this by parsing data into labels and images
 * Also includes some probability computations to analyze images
 */
class Model {

public:
 /***
  * Model constructor taking a training data file and parsing it into images
  * @param file_name containing data to be trained
  */
  Model(string file_name);

  // Getters
  const vector<Image>& GetTrainingImagesVector() const;

  const size_t& GetVectorSize() const;

private:
  // a vector containing Images of model trained from file
  vector<Image> training_images_vector_;

  size_t vector_size_;
};

}

#endif //NAIVE_BAYES_NAIVE_BAYES_MODEL_H
