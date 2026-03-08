#ifndef WXCLEANGRADUATOR_CATALOG_H
#define WXCLEANGRADUATOR_CATALOG_H

#include <string>
#include <vector>

namespace infra {

    template<typename T>
    class Catalog {
    public:
        explicit Catalog(std::string filePath);

        void load();

        const std::vector<T>& items() const noexcept;
        std::vector<T>& items() noexcept;

    private:
        std::string filePath_;
        std::vector<T> items_;
    };

} // namespace infra

#endif //WXCLEANGRADUATOR_CATALOG_H