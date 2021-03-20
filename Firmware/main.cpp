#include "ap_application.hpp"

#include <ih/drivers/ih_display_idisplay.hpp>
#include <ih/drivers/ih_display_driver_creator.hpp>
#include <board/watchboard.hpp>

#include <utils/CoroUtils.hpp>
#include "pca10040.h"
#include "boards.h"
#include "bsp.h"
#include "nrf_delay.h"

//#include <etl/memory.h>
//#include "utils/CoroutineExample.hpp"

int main(void)
{
    auto pBoard = WatchBoard::createBoard();
    auto pDisplayDriver = DisplayCreator::createDisplayDriver();
    pDisplayDriver->initialize();

    while(true)
    {
        //bsp_board_led_invert(0);
        //nrf_delay_ms(20);
        //pBoard->ledToggle();
        CoroUtils::CoroQueueMainLoop::GetInstance().processQueue();
    }
    //testMe();

//    Application mainApp;

//    mainApp.runApplicationLoop();


    return 0;
}
