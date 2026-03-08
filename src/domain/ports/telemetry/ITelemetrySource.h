#ifndef ITELEMETRYSOURCE_H
#define ITELEMETRYSOURCE_H
#include <vector>

#include "domain/core/telemetry/TelemetryField.h"
#include "domain/core/telemetry/TelemetryValue.h"

namespace domain::ports {

    struct ITelemetrySource {
        virtual ~ITelemetrySource() = default;
        // Статическая схема
        virtual std::vector<telemetry::TelemetryField> telemetrySchema() const = 0;
        // Динамические значения
        virtual std::vector<telemetry::TelemetryValue> telemetryValues() const = 0;
    };

}

#endif //ITELEMETRYSOURCE_H