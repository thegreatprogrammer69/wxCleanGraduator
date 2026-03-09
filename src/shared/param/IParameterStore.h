#ifndef IPARAMETERSTORE_H
#define IPARAMETERSTORE_H

#include <string>
#include <cstdint>

namespace utils::config {

    class IParameterStore {
    public:
        virtual ~IParameterStore() = default;

        virtual bool has(const std::string& key) const noexcept = 0;

        virtual std::string getString(const std::string& key, const std::string& defaultValue = "") const = 0;
        virtual bool getBool(const std::string& key, bool defaultValue = false) const = 0;
        virtual int getInt(const std::string& key, int defaultValue = 0) const = 0;
        virtual float getFloat(const std::string& key, float defaultValue = 0.0f) const = 0;
        virtual std::uint32_t getHex(const std::string& key, std::uint32_t defaultValue = 0) const = 0;

        virtual void set(const std::string& key, const std::string& value) = 0;
        virtual void set(const std::string& key, bool value) = 0;
        virtual void set(const std::string& key, int value) = 0;
        virtual void set(const std::string& key, float value) = 0;
        virtual void setHex(const std::string& key, std::uint32_t value) = 0;
    };

} // namespace utils::config

#endif //IPARAMETERSTORE_H