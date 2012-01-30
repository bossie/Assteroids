#ifndef TYPE_INFO_H
#define TYPE_INFO_H

#include <typeinfo>
#include <string>

namespace collision {

class TypeInfo {
    std::string m_id;

public:
    TypeInfo(const std::type_info & t);

    const std::string id() const;
    const bool operator<(const TypeInfo & that) const;
};

} // namespace collision

#endif // TYPE_INFO_H
