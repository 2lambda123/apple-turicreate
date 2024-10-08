#include "Result.hpp"

#include "DataType.hpp"
#include "Format.hpp"
#include "ResultReason.hpp"
#include "ResultType.hpp"

#include <sstream>

namespace CoreML {

  static const char* m_prefix = "validator error: ";

  Result::Result()
    : Result(ResultType::NO_ERROR, ResultReason::UNKNOWN, "not an error")
  { }

  Result::Result(ResultType type, const std::string& message)
    : Result(type, ResultReason::UNKNOWN, message)
  { }

  Result::Result(ResultType type, ResultReason reason, const std::string& message)
    : m_type(type)
    , m_reason(reason)
    , m_message(m_prefix + message) { }

bool Result::good() const {
      return (m_type == ResultType::NO_ERROR || m_type == ResultType::POTENTIALLY_INVALID_NEURAL_NETWORK_SHAPES);
  }

  ResultReason Result::reason() const {
    return m_reason;
  }
ResultType Result::type() const {
    return m_type;
  }

  const std::string& Result::message() const {
    return m_message;
  }

  Result Result::typeMismatchError(
      const FeatureType& expected,
      const FeatureType& actual,
      const std::string& parameterName) {

    Result out;
    std::stringstream ss;
    ss << "Type mismatch for \"";
    ss << parameterName <<"\". Expected ";
    ss << expected.toString() << ", ";
    ss << "found ";
    ss << actual.toString() << ".";
    out.m_message = ss.str();
    out.m_type = ResultType::TYPE_MISMATCH;
    return out;
  }

  Result Result::featureTypeInvariantError(
      const std::vector<FeatureType>& allowed,
      const FeatureType& actual) {

    Result out;
    std::stringstream ss;
    ss << "Feature type invariant violation. Expected feature type ";
    ss << actual.toString() << " to be one of: ";
    for (size_t i=0; i<allowed.size(); i++) {
      ss << allowed[i].toString();
      if (i != allowed.size() - 1) {
        ss << ", ";
      }
    }
    out.m_message = ss.str();
    out.m_type = ResultType::FEATURE_TYPE_INVARIANT_VIOLATION;
    return out;
  }

}
