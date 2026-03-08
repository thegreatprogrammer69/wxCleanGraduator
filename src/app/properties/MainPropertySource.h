#ifndef WXCLEANGRADUATOR_MEASPROPERTYSOURCE_H
#define WXCLEANGRADUATOR_MEASPROPERTYSOURCE_H
#include "application/property/PropertySourceBase.h"


class MainPropertySource final : public application::property::PropertySourceBase {
public:
    using PropertySourceBase::PropertySourceBase;

    std::vector<domain::property::PropertyField> propertySchema() const override;
};


#endif //WXCLEANGRADUATOR_MEASPROPERTYSOURCE_H