#pragma once

#include "display_st7789v_constants.hpp"

#include <array>
#include <utility>
#include <cstddef>
#include <memory>

namespace FrameBuffer
{
    using RowType = std::array<DisplayDriver::EncodedColor,1 >;
    using FrameBufferType = std::array<RowType,1>; 

class DisplayBuffer
{


public:

    using CoordsPair = std::pair<std::uint8_t,std::uint8_t>;

    static CoordsPair getFrameBufferCoords( std::uint16_t _realDisplayX, std::uint16_t _realDisplayY );

public:

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

    static constexpr std::uint8_t RowRepeatsCount = 2; // Number of repeating bufferTransmissions;

    std::uint8_t getTranmissionRowIndex();

private:

    static FrameBufferType DisplayFrameBuffer;

    std::uint8_t m_changedRowsBegin;
    std::uint8_t m_changedRowsEnd;

    std::uint8_t m_rowTranmisionsCount;
};

std::unique_ptr<DisplayBuffer> createFrameBuffer();

};