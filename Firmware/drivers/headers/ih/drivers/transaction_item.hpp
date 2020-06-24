#pragma once

#include <functional>
#include <variant>

namespace Interface::Spi
{

struct Transaction
{
    std::function<void()> beforeTransaction;
    std::function<void()> afterTransaction;
    std::function<void()> transactionAction;

    size_t repeatsCount;
};

struct TransactionDescriptor
{
    std::function<void()> beforeTransaction;
    std::function<void()> afterTransaction;

    struct DataSequence
    {
        const std::uint8_t* dataBlock;
        const size_t blockSize;
    };

    std::variant<std::uint8_t,DataSequence> transactionData;
};

};
