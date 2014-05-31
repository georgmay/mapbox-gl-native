#ifndef LLMR_STYLE_BUCKET_DESCRIPTION
#define LLMR_STYLE_BUCKET_DESCRIPTION

#include <string>
#include <vector>
#include <cmath>

#include "value.hpp"
#include "../util/vec.hpp"

namespace llmr {

enum class BucketType {
    None = 0,
    Fill = 1,
    Line = 2,
    Icon = 3,
    Text = 4,
    Raster = 5
};

enum class CapType {
    None = 0,
    Round = 1,
    Butt = 2,
    Square = 3
};

enum class JoinType {
    None = 0,
    Miter = 1,
    Bevel = 2,
    Round = 3
};

enum class TextPathType {
    Horizontal = 0,
    Curve = 1
};

enum class FilterOperator {
    Equal,
    NotEqual
};

enum class ExpressionOperator {
    Or,
    And
};


inline BucketType bucketType(const std::string& type) {
    if (type == "fill") return BucketType::Fill;
    else if (type == "line") return BucketType::Line;
    else if (type == "point") return BucketType::Icon;
    else if (type == "text") return BucketType::Text;
    else if (type == "raster") return BucketType::Raster;
    else return BucketType::None;
}

inline CapType capType(const std::string& cap) {
    if (cap == "round") return CapType::Round;
    else if (cap == "butt") return CapType::Butt;
    else if (cap == "square") return CapType::Square;
    else return CapType::None;
}


inline JoinType joinType(const std::string& join) {
    if (join == "miter") return JoinType::Miter;
    else if (join == "bevel") return JoinType::Bevel;
    else if (join == "round") return JoinType::Round;
    else return JoinType::None;
}

inline TextPathType textPathType(const std::string& path) {
    if (path == "horizontal") return TextPathType::Horizontal;
    else if (path == "curve") return TextPathType::Curve;
    else return TextPathType::Horizontal;
};

inline float alignmentType(const std::string& alignment) {
    if (alignment == "right") return 1.0f;
    else if (alignment == "left") return 0.0f;
    else return 0.5;
};

inline float verticalAlignmentType(const std::string& alignment) {
    if (alignment == "bottom") return 1.0f;
    else if (alignment == "top") return 0.0f;
    else return 0.5;
};

inline FilterOperator filterOperatorType(const std::string &op) {
    if (op == "!=" || op == "not") {
        return FilterOperator::NotEqual;
    } else {
        return FilterOperator::Equal;
    }
}

inline ExpressionOperator expressionOperatorType(const std::string &op) {
    if (op == "&&" || op == "and") {
        return ExpressionOperator::And;
    } else {
        return ExpressionOperator::Or;
    }
}


class BucketGeometryDescription {
public:
    CapType cap = CapType::None;
    JoinType join = JoinType::None;
    std::string font;
    std::string field;
    std::string icon;
    float size = 0.0f;
    float miter_limit = 2.0f;
    float round_limit = 1.0f;
    TextPathType path = TextPathType::Horizontal;
    float alignment = 0.5;
    float vertical_alignment = 0.5;
    float line_height = 1.2 * 24;
    float max_width = 15.0f * 24;
    float letter_spacing = 0;
    vec2<float> translate {0, 0};
    float padding = 2.0f;
    float textMinDistance = 250.0f;
    float rotate = 0.0f; // what is this?
    float maxAngleDelta = M_PI;
    bool alwaysVisible = false;
};


class BucketFilter {
public:
    inline BucketFilter(const std::string &field, const Value &value) : field(field), value(value) {};

    // Returns true if the filter passes, even if the key is missing.
    inline bool isMissingFieldOkay() const {
        switch (op) {
        case FilterOperator::NotEqual:
            return true;
        default:
            return false;
        }
    }

    inline bool compare(const Value &other) const {
        switch (op) {
        case FilterOperator::NotEqual:
            return !util::relaxed_equal(value)(other);
        default:
            return util::relaxed_equal(value)(other);
        }
    }

public:
    std::string field;
    Value value;
    FilterOperator op = FilterOperator::Equal;
};

class BucketExpression {
public:
    ExpressionOperator op = ExpressionOperator::Or;
    std::vector<BucketFilter> operands;
};

class BucketDescription {
public:
    BucketType feature_type = BucketType::None;
    BucketType type = BucketType::None;

    // Specify what data to pull into this bucket
    std::string source_name;
    std::string source_layer;

    BucketExpression filter;

    // Specifies how the geometry for this bucket should be created
    BucketGeometryDescription geometry;
};

std::ostream& operator<<(std::ostream&, const BucketDescription& bucket);
std::ostream& operator<<(std::ostream&, BucketType type);

}

#endif
