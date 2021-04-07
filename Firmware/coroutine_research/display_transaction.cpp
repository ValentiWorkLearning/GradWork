#include <ih/drivers/ih_display_idisplay.hpp>
#include <ih/drivers/ih_display_driver_creator.hpp>

#include <utils/CoroUtils.hpp>


int main(void)
{
    auto pDisplayDriver = DisplayCreator::createDisplayDriver();
    pDisplayDriver->initialize();

    while(true)
    {
        CoroUtils::CoroQueueMainLoop::GetInstance().processQueue();
    }

    return 0;
}