#ifndef FMTLOGGER_H
#define FMTLOGGER_H

#include <string>
#include <fmt/format.h>

#include "domain/ports/logging/ILogger.h"

namespace fmtlog {

    class Logger final {
    public:

        explicit Logger(domain::ports::ILogger& logger)
            : logger_(logger) {}

        template<typename... Args>
        void info(fmt::format_string<Args...> fmt, Args&&... args)
        {
            logger_.info(fmt::format(fmt, std::forward<Args>(args)...));
        }

        template<typename... Args>
        void warn(fmt::format_string<Args...> fmt, Args&&... args)
        {
            logger_.warn(fmt::format(fmt, std::forward<Args>(args)...));
        }

        template<typename... Args>
        void error(fmt::format_string<Args...> fmt, Args&&... args)
        {
            last_error_ = fmt::format(fmt, std::forward<Args>(args)...);
            logger_.error(last_error_);
        }

        std::string lastError()
        {
            auto e = last_error_;
            last_error_.clear();
            return e;
        }

    private:

        domain::ports::ILogger& logger_;
        std::string last_error_;
    };

}

#endif