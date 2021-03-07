#include "ap_application.hpp"

#include <ih/drivers/ih_display_idisplay.hpp>
#include <ih/drivers/ih_display_driver_creator.hpp>
#include <board/watchboard.hpp>

//#include <etl/memory.h>
//#include "utils/CoroutineExample.hpp"

int main(void)
{
    auto pBoard = WatchBoard::createBoard();
    auto pDisplayDriver = DisplayCreator::createDisplayDriver();
    pDisplayDriver->initialize();

    while(true)
    {
        pBoard->ledToggle();
    }
    //testMe();

//    Application mainApp;

//    mainApp.runApplicationLoop();


    return 0;
}
