#include "ap_application.hpp"
#include <etl/memory.h>
#include "utils/CoroutineExample.hpp"

int main(void)
{
    //testMe();

    Application mainApp;

    mainApp.runApplicationLoop();

    return 0;
}
