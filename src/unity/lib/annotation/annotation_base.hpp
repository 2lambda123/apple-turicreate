#ifndef TURI_ANNOTATIONS_ANNOTATION_BASE_HPP
#define TURI_ANNOTATIONS_ANNOTATION_BASE_HPP

#include <map>
#include <memory>
#include <string>
#include <vector>

#include <flexible_type/flexible_type.hpp>

#include <unity/lib/unity_sarray.hpp>
#include <unity/lib/unity_sframe.hpp>

#include "build/format/cpp/annotate.pb.h"
#include "build/format/cpp/data.pb.h"
#include "build/format/cpp/meta.pb.h"

namespace annotate_spec = TuriCreate::Annotation::Specification;

namespace turi {
namespace annotate {

/**
 *
 * Fallback
 *
 * If the user forgets to assign a return variable in their Python script this
 * global will hold the last annotated sframe
 */
struct annotation_global {
  std::shared_ptr<unity_sframe> annotation_sframe;
};

/**
 * Every annotation backend extends from this class. This forces the annotation
 * api to remain consistent across all implementations. The reason the virtual
 * methods exist rather than a switch statement in the annotate method is to
 * expose this functionality to the capi so that other developers have the
 * ability to tie their own annotations UI's to use this api.
 */
class AnnotationBase {
public:
  AnnotationBase(){};
  AnnotationBase(const std::shared_ptr<unity_sframe> &data,
                 const std::vector<std::string> &data_columns,
                 const std::string &annotation_column);

  virtual ~AnnotationBase(){};

  void annotate(const std::string &path_to_client);

  size_t size();

  std::shared_ptr<unity_sframe> returnAnnotations(bool drop_null = false);

  std::shared_ptr<annotation_global> get_annotation_registry();

  virtual annotate_spec::MetaData metaData() = 0;

  virtual annotate_spec::Data getItems(size_t start, size_t end) = 0;

  virtual annotate_spec::Annotations getAnnotations(size_t start,
                                                    size_t end) = 0;

  virtual bool
  setAnnotations(const annotate_spec::Annotations &annotations) = 0;

protected:
  std::shared_ptr<unity_sframe> m_data;
  const std::vector<std::string> m_data_columns;
  std::string m_annotation_column;

  void _addAnnotationColumn();
  void _addIndexColumn();
  void _checkDataSet();
  void _reshapeIndicies(size_t &start, size_t &end);
};

} // namespace annotate
} // namespace turi

#endif
