//
// Created by Gisella Kontaria on 03/04/21.
//

#include <core/naive_bayes_model.h>
#include <vector>
#include <string>
#include <fstream>

using std::vector;
using std::string;
using std::istream;
using std::ifstream;
using std::ostream;

namespace naivebayes {

Model::Model(string file_name) {
  // parse data in file into vector of images
  if (file_name.empty()) {
    throw new std::invalid_argument("File cannot be empty");
  }
  ifstream reader;
  reader.open(file_name);
  if (!reader) {
    throw new std::invalid_argument("File doesn't exist");
  }
  while (!reader.eof()) {
    size_t label;
    string line;
    std::getline(reader, line);
    if (line.empty()) {
      break;
    }
    label = std::stoi(line);

    Image image;
    image.SetLabel(label);

    reader >> image;
    training_images_vector_.push_back(image);
  }
  reader.close();
  vector_size_ = training_images_vector_.size();
}

const vector<Image>& Model::GetTrainingImagesVector() const {
  return training_images_vector_;
}

const size_t& Model::GetVectorSize() const {
  return vector_size_;
}

}