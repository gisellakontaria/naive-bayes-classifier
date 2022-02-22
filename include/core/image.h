#pragma once

#include <string>
#include <istream>
#include <ostream>
#include <iostream>
#include <vector>

using std::string;
using std::istream;
using std::ifstream;
using std::ostream;
using std::vector;

namespace naivebayes {

/***
 * Class that models the image object that will be analyzed
 */
class Image {

public:
 /***
  * Image constructor
  */
  Image() = default;

 /***
  * Image constructor that reads text file and sets it to Image object
  * @param image_file
  */
  Image(const string& image_file);

 /***
  * Sets label of an image
  * @param label digit between 0-9 that represents the image
  */
  void SetLabel(const size_t& label);

 /***
   * Label getter
   * @return label of image
   */
  const size_t& GetLabel() const;

 /***
  * Overloads >> operator to read an Image object and convert it to a 2D vector
  * @param input stream to be read from
  * @param image object to be read
  * @return input stream being read from
  */
  friend istream& operator>>(istream& input, Image& image);

 /***
  * Overloads << operator to print 2D vector of image
  * @param output stream being printed to
  * @param image Image object to be printed
  * @return output stream being printed to
  */
  friend ostream& operator<<(ostream& output, Image& image);

 /***
  * Overload == operator to check if two images are equal
  * @param other image to be checked against this image
  * @return true if image are identical
  */
  bool operator==(Image other) const;

  // 2D vector filled with 0 and 1 that represents a given image
  vector<vector<size_t>> image_vector_;

private:
  static const size_t kImageSize = 28;

  static const size_t kUnshadedValue = 0;

  static const size_t kShadedValue = 1;

  // label (a digit) the image represents
  size_t label_;

};

}  // namespace naivebayes

/*

You can (and should) create more classes and files in include/core (header
 files) and src/core (source files); this project is too big to only have a
 single class.

Make sure to add any files that you create to CMakeLists.txt.

*/
