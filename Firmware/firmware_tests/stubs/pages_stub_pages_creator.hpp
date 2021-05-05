#pragma once

#include "ih/creators/gs_ipages_creator.hpp"

namespace Graphics::StubViews
{

class StubPagesCreator
    :   public Graphics::Views::IPagesCreator
{
public:

    ~StubPagesCreator() override;

public:

    std::unique_ptr<Graphics::Views::IClockWatchPage>
        createClockPage(Graphics::Theme::IThemeController* _pThemeController)noexcept override;

    std::unique_ptr<Graphics::Views::IHealthWatchPage>
        createHealthPage(Graphics::Theme::IThemeController* _pThemeController)noexcept override;

    std::unique_ptr<Graphics::Views::IPlayerWatchPage>
        createPlayerPage(Graphics::Theme::IThemeController* _pThemeController)noexcept override;
};

Graphics::Views::IPagesCreator::Ptr createStubPagesCreator()noexcept;

}