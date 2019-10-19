#pragma once

#include "display_st7789v_constants.hpp"

#include <array>
#include <utility>
#include <cstddef>
#include <memory>

namespace FrameBuffer
{
    using RowType = std::array<DisplayDriver::EncodedColor,120 >;
    using FrameBufferType = std::array<RowType,120>; 

class DisplayBuffer
{

public:

    void drawPixel(
            std::uint8_t _x
        ,   std::uint8_t _y
        ,   DisplayDriver::Colors _color
    );

    void fillColor( DisplayDriver::Colors _color );

    void fillRectangle(
            std::uint8_t _x
        ,   std::uint8_t _y
        ,   std::uint8_t _width
        ,   std::uint8_t _height
        ,   DisplayDriver::Colors _color
    );

public:

    const RowType& getNextTransmissionRow();

    bool isAllBufferTransmitted();

private:

    using CoordsPair = std::pair<std::uint8_t,std::uint8_t>;

    CoordsPair getFrameBufferCoords( std::uint16_t _realDisplayX, std::uint16_t _realDisplayY );

    static constexpr std::uint8_t RowRepeatsCount = 4; // Number of repeating bufferTransmissions;

    std::uint8_t getTranmissionRowIndex();

private:

    static FrameBufferType DisplayFrameBuffer;

    std::uint8_t m_changedRowsBegin;
    std::uint8_t m_changedRowsEnd;

    std::uint8_t m_rowTranmisionsCount;
};

std::unique_ptr<DisplayBuffer> createFrameBuffer();

};