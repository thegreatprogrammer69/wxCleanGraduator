#ifndef INIFILE_H
#define INIFILE_H

#include <string>
#include <unordered_map>
#include <cstdint>
#include <filesystem>

#include "shared/param/IParameterStore.h"


namespace utils::ini {

    class IniSection : public utils::config::IParameterStore {
    public:
        bool has(const std::string& key) const noexcept override;

        std::string getString(const std::string& key,
                              const std::string& defaultValue = "") const override;

        bool getBool(const std::string& key, bool defaultValue = false) const override;
        int getInt(const std::string& key, int defaultValue = 0) const override;
        float getFloat(const std::string& key, float defaultValue = 0.0f) const override;
        std::uint32_t getHex(const std::string& key,
                             std::uint32_t defaultValue = 0) const override;

        void set(const std::string& key, const std::string& value) override;
        void set(const std::string& key, bool value) override;
        void set(const std::string& key, int value) override;
        void set(const std::string& key, float value) override;
        void setHex(const std::string& key, std::uint32_t value) override;

        // Метод, специфичный для INI (его нет в интерфейсе)
        const std::unordered_map<std::string, std::string>& values() const noexcept;

    private:
        std::unordered_map<std::string, std::string> values_;
    };

    class IniFile {
    public:
        bool load(const std::filesystem::path& path);
        bool save(const std::filesystem::path& path) const;

        const std::unordered_map<std::string, IniSection>& sections() const;

        IniSection& operator[](const std::string& section);
        const IniSection& operator[](const std::string& section) const;

        bool hasSection(const std::string& section) const noexcept;

    private:
        std::unordered_map<std::string, IniSection> sections_;
    };

} // namespace utils::ini

#endif //INIFILE_H