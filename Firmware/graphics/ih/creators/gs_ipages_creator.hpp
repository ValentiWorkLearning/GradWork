#pragma once

#include "ih/gs_ipage_view_object.hpp"

#include <memory>

namespace Graphics::Views
{
    class IClockWatchPage;
    class IHealthWatchPage;
    class IPlayerWatchPage;
}

namespace Graphics::Views
{
class IPagesCreator
{
public:
    using Ptr = std::unique_ptr<IPagesCreator>;

    [[nodiscard]] virtual std::unique_ptr<Graphics::Views::IClockWatchPage>
        createClockPage(Theme::IThemeController* _pThemeController) = 0;

    [[nodiscard]] virtual std::unique_ptr<Graphics::Views::IHealthWatchPage>
        createHealthPage(Theme::IThemeController* _pThemeController) = 0;

    [[nodiscard]] virtual std::unique_ptr<Graphics::Views::IPlayerWatchPage>
      createPlayerPage(Theme::IThemeController* _pThemeController) = 0;

    virtual ~IPagesCreator() = default;
};

}