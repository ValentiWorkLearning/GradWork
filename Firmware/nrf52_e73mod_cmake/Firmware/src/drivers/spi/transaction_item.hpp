#pragma once

#include <functional>

namespace Interface::Spi
{

struct Transaction
{
    std::function<void()> beforeTransaction;
    std::function<void()> afterTransaction;
    std::function<void()> transactionAction;
};

};