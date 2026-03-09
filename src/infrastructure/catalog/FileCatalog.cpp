#include "FileCatalog.h"

#include <fstream>
#include <sstream>
#include <stdexcept>
#include <utility>

#include "domain/core/common/PressureUnit.h"
#include "application/models/catalog/Displacement.h"
#include "application/models/catalog/Gauge.h"
#include "application/models/catalog/GaugePrecision.h"
#include "application/models/catalog/PressureUnit.h"
#include "application/models/catalog/Printer.h"

namespace infra::catalog {

namespace {

inline std::string trim(const std::string& s) {
    const auto begin = s.find_first_not_of(" \t\r\n");
    if (begin == std::string::npos) {
        return {};
    }

    const auto end = s.find_last_not_of(" \t\r\n");
    return s.substr(begin, end - begin + 1);
}

inline bool shouldSkipLine(const std::string& line) {
    const auto t = trim(line);
    return t.empty() || t[0] == '#';
}

inline std::vector<std::string> split(const std::string& line, char delim = ';') {
    std::vector<std::string> result;
    std::stringstream ss(line);
    std::string part;

    while (std::getline(ss, part, delim)) {
        result.push_back(trim(part));
    }

    return result;
}

inline int toInt(const std::string& s, const std::string& fieldName) {
    try {
        size_t pos = 0;
        int value = std::stoi(s, &pos);
        if (pos != s.size()) {
            throw std::runtime_error("");
        }
        return value;
    } catch (...) {
        throw std::runtime_error("Failed to parse int field '" + fieldName + "': " + s);
    }
}

inline double toDouble(const std::string& s, const std::string& fieldName) {
    try {
        size_t pos = 0;
        double value = std::stod(s, &pos);
        if (pos != s.size()) {
            throw std::runtime_error("");
        }
        return value;
    } catch (...) {
        throw std::runtime_error("Failed to parse double field '" + fieldName + "': " + s);
    }
}

inline std::runtime_error badFormat(
    const std::string& filePath,
    std::size_t lineNo,
    const std::string& message
) {
    return std::runtime_error(
        "Catalog parse error in '" + filePath + "', line " +
        std::to_string(lineNo) + ": " + message
    );
}

inline domain::common::PressureUnit parsePressureUnit(const std::string& s) {
    using Unit = domain::common::PressureUnit;

    if (s == "Pa")      return Unit::Pa;
    if (s == "kPa")     return Unit::kPa;
    if (s == "MPa")     return Unit::MPa;
    if (s == "bar")     return Unit::bar;
    if (s == "atm")     return Unit::atm;
    if (s == "mmHg")    return Unit::mmHg;
    if (s == "mmH2O")   return Unit::mmH2O;
    if (s == "kgf_cm2") return Unit::kgf_cm2;
    if (s == "kgf_m2")  return Unit::kgf_m2;

    throw std::runtime_error("Unknown pressure unit: " + s);
}

template<typename T>
void loadNotImplemented() {
    static_assert(sizeof(T) == 0, "FileCatalog<T>::load() specialization is not implemented for this type");
}

} // namespace

template<typename T>
void FileCatalog<T>::load() {
    loadNotImplemented<T>();
}

// ===== СПЕЦИАЛИЗАЦИИ =====

template<>
void FileCatalog<application::models::Displacement>::load() {
    items().clear();

    std::ifstream in(filePath_);
    if (!in.is_open()) {
        throw std::runtime_error("Cannot open catalog file: " + filePath_);
    }

    std::string line;
    std::size_t lineNo = 0;

    while (std::getline(in, line)) {
        ++lineNo;

        if (shouldSkipLine(line)) {
            continue;
        }

        const auto parts = split(line);
        if (parts.size() != 2) {
            throw badFormat(filePath_, lineNo, "Displacement must contain 2 fields: id;name");
        }

        application::models::Displacement item{};
        item.id = toInt(parts[0], "id");
        item.name = parts[1];

        items().push_back(std::move(item));
    }
}

template<>
void FileCatalog<application::models::Gauge>::load() {
    items().clear();

    std::ifstream in(filePath_);
    if (!in.is_open()) {
        throw std::runtime_error("Cannot open catalog file: " + filePath_);
    }

    std::string line;
    std::size_t lineNo = 0;

    while (std::getline(in, line)) {
        ++lineNo;

        if (shouldSkipLine(line)) {
            continue;
        }

        const auto parts = split(line);
        if (parts.size() < 2) {
            throw badFormat(filePath_, lineNo, "Gauge must contain at least 2 fields: name;point1;...");
        }

        application::models::Gauge item{};
        item.name = parts[0];

        std::vector<float> points;
        for (std::size_t i = 1; i < parts.size(); ++i) {
            points.push_back(static_cast<float>(toDouble(parts[i], "point")));
        }

        item.points = std::move(points);
        items().push_back(std::move(item));
    }
}

template<>
void FileCatalog<application::models::GaugePrecision>::load() {
    items().clear();

    std::ifstream in(filePath_);
    if (!in.is_open()) {
        throw std::runtime_error("Cannot open catalog file: " + filePath_);
    }

    std::string line;
    std::size_t lineNo = 0;

    while (std::getline(in, line)) {
        ++lineNo;

        if (shouldSkipLine(line)) {
            continue;
        }

        application::models::GaugePrecision item{};
        item.value = toDouble(trim(line), "value");
        items().push_back(std::move(item));
    }
}

template<>
void FileCatalog<application::models::PressureUnit>::load() {
    items().clear();

    std::ifstream in(filePath_);
    if (!in.is_open()) {
        throw std::runtime_error("Cannot open catalog file: " + filePath_);
    }

    std::string line;
    std::size_t lineNo = 0;

    while (std::getline(in, line)) {
        ++lineNo;

        if (shouldSkipLine(line)) {
            continue;
        }

        application::models::PressureUnit item{};
        item.unit = parsePressureUnit(trim(line));
        items().push_back(std::move(item));
    }
}

template<>
void FileCatalog<application::models::Printer>::load() {
    items().clear();

    std::ifstream in(filePath_);
    if (!in.is_open()) {
        throw std::runtime_error("Cannot open catalog file: " + filePath_);
    }

    std::string line;
    std::size_t lineNo = 0;

    while (std::getline(in, line)) {
        ++lineNo;

        if (shouldSkipLine(line)) {
            continue;
        }

        const auto parts = split(line);
        if (parts.size() != 2) {
            throw badFormat(filePath_, lineNo, "Printer must contain 2 fields: name;path");
        }

        application::models::Printer item{};
        item.name = parts[0];
        item.path = parts[1];

        items().push_back(std::move(item));
    }
}

// ===== ЯВНЫЕ ИНСТАНЦИРОВАНИЯ =====

template class FileCatalog<application::models::Printer>;
template class FileCatalog<application::models::Displacement>;
template class FileCatalog<application::models::Gauge>;
template class FileCatalog<application::models::GaugePrecision>;
template class FileCatalog<application::models::PressureUnit>;

} // namespace infra::catalog