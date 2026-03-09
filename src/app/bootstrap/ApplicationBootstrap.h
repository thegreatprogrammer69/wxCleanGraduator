#ifndef WXCLEANGRADUATOR_APPLICATIONBOOTSTRAP_H
#define WXCLEANGRADUATOR_APPLICATIONBOOTSTRAP_H
#include <filesystem>
#include <memory>
#include <vector>


namespace application::ports {
    struct ILogSourcesStorage;
}

namespace domain::ports {
    struct IVideoSource;
    struct ISessionClock;
    struct IClock;
    struct ILogger;
}

class ApplicationBootstrap {
public:
    explicit ApplicationBootstrap(const std::filesystem::path &setup_dir, const std::filesystem::path &catalogs_dir, const std::filesystem::path &logs_dir);
    ~ApplicationBootstrap();

    void initialize();

    domain::ports::ILogger& createLogger(const std::string &logger_name);

    ////////////////////////////////////////////////////////////////////////////////////////
    std::unique_ptr<domain::ports::IClock> uptime_clock;

    ////////////////////////////////////////////////////////////////////////////////////////
    // Логеры
    std::unique_ptr<application::ports::ILogSourcesStorage> log_sources_storage;
    std::vector<std::unique_ptr<domain::ports::ILogger>> loggers;

    ////////////////////////////////////////////////////////////////////////////////////////
    // Время процесса
    std::unique_ptr<domain::ports::ISessionClock> session_clock;

    ////////////////////////////////////////////////////////////////////////////////////////
    // Видеокамеры
    std::vector<std::unique_ptr<domain::ports::IVideoSource>> video_sources;
    // std::vector<std::unique_ptr<domain::ports::IAngleSource>> angle_sources;
    // std::unique_ptr<application::ports::IVideoAngleSourcesStorage> videoangle_sources_storage;
    // Оркестратор, открывающий и закрывающий камеры по индексам
    // std::unique_ptr<application::orchestrators::VideoSourceManager> video_source_manager;

    ////////////////////////////////////////////////////////////////////////////////////////
    // Источник давления. Может быть какой-то датик давления, например ДМ5002М
    // std::unique_ptr<domain::ports::IPressureSource> pressure_source;

    ////////////////////////////////////////////////////////////////////////////////////////
    // Драйвер двигателя
    // std::unique_ptr<domain::ports::IMotorDriver> motor_driver;

    ////////////////////////////////////////////////////////////////////////////////////////
    // Задатчик давления. Делавет весь процесс градуировки
    // std::unique_ptr<domain::ports::IPressureActuator> pressure_actuator;

    ////////////////////////////////////////////////////////////////////////////////////////
    // Хранение результата
    // std::unique_ptr<domain::ports::IResultStore> result_store;


    ////////////////////////////////////////////////////////////////////////////////////////
    // Каталоги
    // std::unique_ptr<application::ports::IDisplacementCatalog> displacement_catalog;
    // std::unique_ptr<application::ports::IGaugeCatalog> gauge_catalog;
    // std::unique_ptr<application::ports::IGaugePrecisionCatalog> precision_catalog;
    // std::unique_ptr<application::ports::IPressureUnitCatalog> pressure_unit_catalog;
    // std::unique_ptr<application::ports::IPrinterCatalog> printer_catalog;

    ////////////////////////////////////////////////////////////////////////////////////////
    // Сохранение настроек
    // std::unique_ptr<application::ports::IInfoSettingsStorage> info_settings_storage;


    ////////////////////////////////////////////////////////////////////////////////////////
    // Реагирует на состояние и запускает какие-либо процессы


private:
    std::filesystem::path setup_dir_;
    std::filesystem::path catalogs_dir_;
    std::filesystem::path logs_dir_;

    ////////////////////////////////////////////////////////////////////////////////////////
    void createLogSourcesStorage();

    ////////////////////////////////////////////////////////////////////////////////////////
    void createSessionClock();
    void createClock();

    ////////////////////////////////////////////////////////////////////////////////////////
    void createAnglemeter();
    void createCalibrator();

    ////////////////////////////////////////////////////////////////////////////////////////
    void createVideoSources();
    void createAngleSources();
    void createVideoSourcesStorage();
    void createVideoSourcesManager();

    ////////////////////////////////////////////////////////////////////////////////////////
    void createPressureSource();
    void createMotorDriver();

    ////////////////////////////////////////////////////////////////////////////////////////
    void createDisplacementCatalog();
    void createPrinterCatalog();
    void createPrecisionCatalog();
    void createPressureUnitCatalog();
    void createGaugeCatalog();

    ////////////////////////////////////////////////////////////////////////////////////////
    void createInfoSettingsStorage();

    ////////////////////////////////////////////////////////////////////////////////////////
    void createProcessRunner();


};


#endif //WXCLEANGRADUATOR_APPLICATIONBOOTSTRAP_H