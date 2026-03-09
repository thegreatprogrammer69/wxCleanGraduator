#include "ApplicationBootstrap.h"

#include "application/ports/logging/ILogSourcesStorage.h"
#include "domain/ports/clock/ISessionClock.h"
#include "domain/ports/logging/ILogger.h"
#include "domain/ports/video_source/IVideoSource.h"
#include "infrastructure/clock/SessionClock.h"
#include "infrastructure/clock/UptimeClock.h"
#include "infrastructure/factory/VideoSourceFactory.h"
#include "infrastructure/logging/ConsoleLogger.h"
#include "infrastructure/logging/FileLogger.h"
#include "infrastructure/logging/NamedMultiLogger.h"
#include "infrastructure/storage/LogSourcesStorage.h"
#include "shared/ini/IniFile.h"

ApplicationBootstrap::ApplicationBootstrap(
    const std::filesystem::path &setup_dir,
    const std::filesystem::path &catalogs_dir,
    const std::filesystem::path &logs_dir)
        : setup_dir_(setup_dir), catalogs_dir_(catalogs_dir), logs_dir_(logs_dir)
{
}

ApplicationBootstrap::~ApplicationBootstrap() {
}

void ApplicationBootstrap::initialize() {
    createLogSourcesStorage();

    createSessionClock();
    createClock();

    createDisplacementCatalog();
    createGaugeCatalog();
    createPrecisionCatalog();
    createPrinterCatalog();
    createPressureUnitCatalog();

    createAnglemeter();
    createCalibrator();

    createVideoSources();
    createAngleSources();
    createVideoSourcesStorage();
    createVideoSourcesManager();

    createPressureSource();
    createMotorDriver();

    createInfoSettingsStorage();
}

domain::ports::ILogger & ApplicationBootstrap::createLogger(const std::string &logger_name) {
    auto multi_logger = std::make_unique<infra::logging::NamedMultiLogger>(*uptime_clock, logger_name);

    std::filesystem::path log_path = logs_dir_ / (logger_name + ".log");
    auto file_logger = std::make_unique<infra::logging::FileLogger>(log_path);
    multi_logger->addLogger(*file_logger);

    auto console_logger = std::make_unique<infra::logging::ConsoleLogger>();
    multi_logger->addLogger(*console_logger);

    infra::logging::NamedMultiLogger &multi_logger_ref = *multi_logger;

    loggers.emplace_back(std::move(file_logger));
    loggers.emplace_back(std::move(console_logger));
    loggers.emplace_back(std::move(multi_logger));


    application::models::LogSource log_source;
    log_source.name = logger_name;
    log_source.source = &multi_logger_ref;

    dynamic_cast<infra::storage::LogSourcesStorage*>(log_sources_storage.get())->addLogSource(log_source);

    return multi_logger_ref;
}

void ApplicationBootstrap::createLogSourcesStorage() {
    log_sources_storage = std::make_unique<infra::storage::LogSourcesStorage>();
}

void ApplicationBootstrap::createSessionClock() {
    session_clock = std::make_unique<infra::clock::SessionClock>();
}

void ApplicationBootstrap::createClock() {
    uptime_clock = std::make_unique<infra::clock::UptimeClock>();
    session_clock = std::make_unique<infra::clock::SessionClock>();
}

void ApplicationBootstrap::createAnglemeter() {
}

void ApplicationBootstrap::createCalibrator() {

}

void ApplicationBootstrap::createVideoSources() {
    utils::ini::IniFile config;
    config.load(setup_dir_ / "video_sources.ini");
    for (int i = 1; i <= 8; i++) {
        const auto section_name = "camera_" + std::to_string(i);
        if (!config.hasSection(section_name)) continue;

        infra::camera::VideoSourcePorts ports {
            createLogger(section_name),
            *session_clock,
        };

        infra::factory::VideoSourceFactory factory(config[section_name], ports);

        video_sources.push_back(std::move(factory.load()));
    }
}

void ApplicationBootstrap::createAngleSources() {
}

void ApplicationBootstrap::createVideoSourcesStorage() {
}

void ApplicationBootstrap::createVideoSourcesManager() {
}

void ApplicationBootstrap::createPressureSource() {
}

void ApplicationBootstrap::createMotorDriver() {
}

void ApplicationBootstrap::createDisplacementCatalog() {
}

void ApplicationBootstrap::createPrinterCatalog() {
}

void ApplicationBootstrap::createPrecisionCatalog() {
}

void ApplicationBootstrap::createPressureUnitCatalog() {
}

void ApplicationBootstrap::createGaugeCatalog() {
}

void ApplicationBootstrap::createInfoSettingsStorage() {
}

void ApplicationBootstrap::createProcessRunner() {
}
