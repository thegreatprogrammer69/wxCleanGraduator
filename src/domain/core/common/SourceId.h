#ifndef WXSOURCEID_H
#define WXSOURCEID_H
#include <functional>

namespace domain::common {
    struct SourceId {
        explicit SourceId(int id) : id(id) {}
        SourceId() : id(-1) {}
        ~SourceId() = default;
        int id;
        bool operator==(const SourceId& other) const { return id == other.id; }
        bool operator<(const SourceId& other) const { return id < other.id; }
    };
}

namespace std {

    template<>
    struct hash<domain::common::SourceId>
    {
        size_t operator()(const domain::common::SourceId& source) const noexcept
        {
            return std::hash<int>{}(source.id);
        }
    };

} // namespace std

#endif //WXSOURCEID_H