#ifndef WXCLEANGRADUATOR_ICATALOG_H
#define WXCLEANGRADUATOR_ICATALOG_H
#include <vector>

namespace domain::ports {

    template<typename T>
    class ICatalog {
    public:
        virtual ~ICatalog() = default;

        virtual const std::vector<T>& items() const noexcept = 0;
        virtual std::vector<T>& items() noexcept = 0;
    };

}

#endif //WXCLEANGRADUATOR_ICATALOG_H