#ifndef PARAMETERVIEW_H
#define PARAMETERVIEW_H

#include "IParameterStore.h"

namespace utils::config {

    template<typename T>
    class ParameterView {
    public:
        explicit ParameterView(IParameterStore& store) : store_(store) {}

        // Реализация этих методов зависит от структуры T.
        // Обычно для конкретной структуры T делают полную специализацию шаблона,
        // чтобы View знал, какие именно поля читать и писать.
        T load(const T& defaults = {});
        void save(const T& value);

    private:
        IParameterStore& store_;
    };

} // namespace utils::config

#endif //PARAMETERVIEW_H