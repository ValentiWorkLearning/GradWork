#include "ap_application.hpp"

int main(void)
{
    Application::Instance().runApplicationLoop();
    return 0;
}