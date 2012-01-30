#include "TypeInfo.h"

using std::string;

namespace collision {

TypeInfo::TypeInfo(const std::type_info & t): m_id(t.name()) {}

const string TypeInfo::id() const {
    return m_id;
}

const bool TypeInfo::operator<(const TypeInfo & that) const {
    return this->m_id < that.m_id;
}

} // namespace collision
