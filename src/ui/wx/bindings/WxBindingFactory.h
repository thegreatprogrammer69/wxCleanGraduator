#ifndef WXCLEANGRADUATOR_WXBINDINGFACTORY_H
#define WXCLEANGRADUATOR_WXBINDINGFACTORY_H

#include "WxBoolBinding.h"
#include "WxSliderFloatBinding.h"
#include "WxTextBinding.h"
#include <memory>

namespace ui::wx::bindings
{

    class WxBindingFactory
    {
    public:
        template<typename TBinding, typename... TArgs>
        TBinding& create(TArgs&&... args)
        {
            auto binding = std::make_unique<TBinding>(std::forward<TArgs>(args)...);
            auto* raw = binding.get();
            bindings_.push_back(std::move(binding));
            return *raw;
        }

    private:
        std::vector<std::unique_ptr<domain::ports::IPropertyObserver>> bindings_;
    };

}

#endif //WXCLEANGRADUATOR_WXBINDINGFACTORY_H