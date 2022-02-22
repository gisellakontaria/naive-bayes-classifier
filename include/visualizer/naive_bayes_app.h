#pragma once

#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "sketchpad.h"
#include "core/naive_bayes_classifier.h"

namespace naivebayes {

namespace visualizer {

/**
 * Allows a user to draw a digit on a sketchpad and uses Naive Bayes to
 * classify it.
 */
class NaiveBayesApp : public ci::app::App {
 public:
  NaiveBayesApp();

  void draw() override;
  void mouseDown(ci::app::MouseEvent event) override;
  void mouseDrag(ci::app::MouseEvent event) override;
  void keyDown(ci::app::KeyEvent event) override;

  // provided that you can see the entire UI on your screen.
  const double kWindowSize = 875;
  const double kMargin = 100;
  const size_t kImageDimension = 28;

 private:
  Sketchpad sketchpad_;

  // label prediction of drawing on screen
  int current_prediction_ = -1;

  // Classifier object to classify image on sketchpad
  Classifier classifier_ = Classifier("data/testimagesandlabels.txt");

  // drawing on sketchpad to be converted to this Image object and passed to classifier
  Image image_to_classify_ = Image();
};

}  // namespace visualizer

}  // namespace naivebayes
