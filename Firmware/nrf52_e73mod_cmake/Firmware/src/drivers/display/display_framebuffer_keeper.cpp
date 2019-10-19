#include "display_framebuffer_keeper.hpp"


namespace FrameBuffer
{

void DisplayBuffer::drawPixel(
        std::uint8_t _x
    ,   std::uint8_t _y
    ,   DisplayDriver::Colors _color
)
{
    DisplayFrameBuffer[ _x ][ _y ] =  DisplayDriver::toEncodedColor( _color );
    m_changedRowsBegin = m_changedRowsEnd = _y;
}

void DisplayBuffer::fillColor( DisplayDriver::Colors _color )
{
    fillRectangle( 0,0,120,120,_color );
}

void DisplayBuffer::fillRectangle(
        std::uint8_t _x
    ,   std::uint8_t _y
    ,   std::uint8_t _width
    ,   std::uint8_t _height
    ,   DisplayDriver::Colors _color
)
{
    // if((_x >= m_width) || (_y >= m_height )) return;
    // if((_x + _width - 1) >= m_width) _width = m_width - _x;
    // if((_y + _height - 1) >= m_height) _height = m_height - _y;


    for( std::uint8_t i{_x}; i < _width; ++i )
    {
        for( std::uint8_t j{_y}; j< _height; ++j )
        {
            drawPixel( i,j,_color );
        }
    }

    m_changedRowsBegin = _y;
    m_changedRowsEnd = _y + _height;
}


const RowType& DisplayBuffer::getNextTransmissionRow()
{
    return DisplayBuffer::DisplayFrameBuffer[ getTranmissionRowIndex() ];
}

std::uint8_t DisplayBuffer::getTranmissionRowIndex()
{
    if( m_rowTranmisionsCount < RowRepeatsCount )
    {
        ++m_rowTranmisionsCount;
        return m_changedRowsBegin;
    }
    else
    {
        m_rowTranmisionsCount = 0;
        return ++m_changedRowsBegin;
    }
}

bool DisplayBuffer::isAllBufferTransmitted()
{
    return m_changedRowsBegin == m_changedRowsEnd;
}

DisplayBuffer::CoordsPair
DisplayBuffer::getFrameBufferCoords( std::uint16_t _realDisplayX, std::uint16_t _realDisplayY )
{
    return{ _realDisplayX/2, _realDisplayY/2 };
}


FrameBuffer::FrameBufferType
DisplayBuffer::DisplayFrameBuffer{};


std::unique_ptr<DisplayBuffer> createFrameBuffer()
{
    return std::make_unique<DisplayBuffer>();
}

};