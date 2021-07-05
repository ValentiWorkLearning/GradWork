#pragma once

namespace SpiMock
{

class SpiMocker
{
public:
    SpiMocker() = default;

    ~SpiMocker() = default;

public:
    MOCK_METHOD(std::span<const std::uint8_t>, receivedData, ());
    MOCK_METHOD(void, sentData, (std::span<const std::uint8_t>));

private:
    GTEST_DISALLOW_COPY_AND_ASSIGN_(SpiMocker);
};

}; // namespace Gpio