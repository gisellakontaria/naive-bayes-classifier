#include <core/image.h>
#include <fstream>


namespace naivebayes {

Image::Image(const string &image_file) {
  Image image = Image();

  // reads file and turn it into an image
  ifstream file(image_file);
  file >> image;

  // store the 2d vector
  image_vector_ = image.image_vector_;
}

void Image::SetLabel(const size_t& label) {
  label_ = label;
}

const size_t& Image::GetLabel() const {
  return label_;
}

ostream& operator<<(ostream& output, Image& image) {
  for (size_t row = 0; row < image.kImageSize; row++) {
    for (size_t col = 0; col < image.kImageSize; col++) {
      output << image.image_vector_[row][col];
    }
    output << std::endl;
  }
  return output;
}

istream& operator>>(istream& input, Image& image) {
  // Create a vector of size 28 filled with 0 (unshaded value)
  vector<size_t> v(image.kImageSize, 0);

  // Create a 2D vector of size 28x28
  vector<vector<size_t>> image_vec(image.kImageSize, v);

  string line;

  // reads lines and replaces occupied tile with 1 (shaded value)
  for (size_t line_number = 0; line_number < image.kImageSize; line_number++) {
    std::getline(input, line);
    if (line.empty()) {
      continue;
    }

    for (size_t y_index = 0; y_index < line.size(); y_index++) {
      if (line.at(y_index) == '+' || line.at(y_index) == '#') {
        image_vec[line_number][y_index] = image.kShadedValue;
      }
    }
  }

  image.image_vector_ = image_vec;
  return input;
}

bool Image::operator==(Image other) const {
  for (size_t row = 0; row < kImageSize; row++) {
    for (size_t col = 0; col < kImageSize; col++) {
      if (image_vector_[row][col] != other.image_vector_[row][col]) {
        return false;
      }
    }
  }
  return true;
}

}  // namespace naivebayes