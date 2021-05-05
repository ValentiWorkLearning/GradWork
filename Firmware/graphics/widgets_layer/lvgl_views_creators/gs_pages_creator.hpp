#pragma once

#include "ih/creators/gs_ipages_creator.hpp"

namespace Graphics::Views
{

class LvglPagesCreator
    : public IPagesCreator
{
public:

    ~LvglPagesCreator() override;

public:

    std::unique_ptr<Graphics::Views::IClockWatchPage>
        createClockPage(Theme::IThemeController* _pThemeController)noexcept override;

    std::unique_ptr<Graphics::Views::IHealthWatchPage>
        createHealthPage(Theme::IThemeController* _pThemeController)noexcept override;

    std::unique_ptr<Graphics::Views::IPlayerWatchPage>
        createPlayerPage(Theme::IThemeController* _pThemeController)noexcept override;
};

IPagesCreator::Ptr createLvglPagesCreator()noexcept;

}