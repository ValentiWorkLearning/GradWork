#pragma once

#include <gmock/gmock.h>

#include"base_mocked_page.hpp"

#include "ih/pages/gs_iplayer_page_view.hpp"

class FakePlayerPage
	: public FakeBasePage<Graphics::Views::IPlayerWatchPage>
{

public:

	FakePlayerPage(std::string_view _pageName)
		: FakeBasePage{ _pageName }
	{
	}

public:

	void setPause()override
	{
	}

	void setPlaying()override
	{
	}
};



