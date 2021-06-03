#pragma once

#include "ih/gs_ipage_view_object.hpp"

#include <cstdint>
#include <string>

namespace Graphics::Views
{

class IPlayerWatchPage : public IPageViewObject
{

public:
    virtual void setPause() noexcept = 0;

    virtual void setPlaying() noexcept = 0;

public:
    static constexpr std::string_view PlayerPageName = "PlayerPage";
};

} // namespace Graphics::Views
