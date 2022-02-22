#include <core/naive_bayes_classifier.h>

using naivebayes::Model;
using naivebayes::Image;
using naivebayes::Classifier;

int main() {
    Classifier("data/testimagesandlabels.txt");
    return 0;
}
