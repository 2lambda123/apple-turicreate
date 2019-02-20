#ifndef TURI_ANNOTATIONS_IMAGE_CLASSIFICATION_HPP
#define TURI_ANNOTATIONS_IMAGE_CLASSIFICATION_HPP

#include "build/format/cpp/annotate.pb.h"
#include "build/format/cpp/data.pb.h"

#include <unity/lib/annotation/annotation_base.hpp>

namespace turi {
namespace annotate {

class ImageClassification : public AnnotationBase {
public:
  ImageClassification() : AnnotationBase(){};
  ImageClassification(const std::shared_ptr<unity_sframe> &data,
                      const std::vector<std::string> &data_columns,
                      const std::string &annotation_column);

  ~ImageClassification(){};

  annotate_spec::MetaData metaData();

  annotate_spec::Data getItems(size_t start, size_t end);

  annotate_spec::Annotations getAnnotations(size_t start, size_t end);

  bool setAnnotations(const annotate_spec::Annotations &annotations);

private:
  void _addAnnotationToSFrame(size_t index, std::string label);
  void _addAnnotationToSFrame(size_t index, int label);

  std::shared_ptr<unity_sarray> _filterDataSFrame(size_t &start, size_t &end);
  std::shared_ptr<unity_sarray> _filterAnnotationSFrame(size_t &start,
                                                        size_t &end);
};

} // namespace annotate
} // namespace turi
#endif