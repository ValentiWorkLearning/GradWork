#include "ap_application.hpp"
#include "graphics/lvgl/lvgl.h"

int main(void)
{
    lv_init();
    Application mainApp;

    mainApp.runDisplayTest();
    mainApp.runApplicationLoop();

    return 0;
}
