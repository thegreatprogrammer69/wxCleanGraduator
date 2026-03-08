#ifndef WXCLEANGRADUATOR_CATALOG_H
#define WXCLEANGRADUATOR_CATALOG_H

#include <string>
#include <vector>
#include "domain/ports/catalog/ICatalog.h"

namespace infra::catalog {

    template<typename T>
    class FileCatalog : public domain::ports::ICatalog<T> {
    public:
        explicit FileCatalog(std::string filePath)
            : filePath_(std::move(filePath)) {}

        void load();

        const std::vector<T>& items() const noexcept override {
            return items_;
        }

        std::vector<T>& items() noexcept override {
            return items_;
        }

    private:
        std::string filePath_;
        std::vector<T> items_;
    };

}

#endif //WXCLEANGRADUATOR_CATALOG_H