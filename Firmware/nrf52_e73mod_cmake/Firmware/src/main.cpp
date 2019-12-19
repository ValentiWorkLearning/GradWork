#include "ap_application.hpp"

int main(void)
{
    Application mainApp;

    mainApp.runDisplayTest();
    mainApp.runApplicationLoop();

    return 0;
}
