#pragma once

#include <gmock/gmock.h>

#include "base_mocked_page.hpp"

#include "ih/pages/gs_ihealth_page_view.hpp"

class FakeHealthPage : public FakeBasePage<Graphics::Views::IHealthWatchPage>
{

public:
    FakeHealthPage(std::string_view _pageName) noexcept : FakeBasePage{_pageName}
    {
    }

public:
    void setStepsCount(std::uint8_t _newStepsValue) noexcept override
    {
    }

    void setHeartrate(std::uint8_t _newHeartrateValue) noexcept override
    {
    }

    void setCalloriesCount(std::uint8_t _newCalloriesCount) noexcept override
    {
    }
};
