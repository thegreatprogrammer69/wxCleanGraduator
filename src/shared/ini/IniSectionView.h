#ifndef INISECTIONVIEW_H
#define INISECTIONVIEW_H

namespace utils::ini {
    class IniSection;

    template<typename T>
    class IniSectionView {
    public:
        IniSectionView(IniSection& section);

        T load(const T& defaults = {});
        void save(const T& value);

    private:
        IniSection& section_;
    };
}

#endif //INISECTIONVIEW_H