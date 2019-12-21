#include "display_st7789v.hpp"
#include "display_st7789v_constants.hpp"

#include "spi/transaction_item.hpp"

#include "nrf_delay.h"
#include "pca10040.h"

#include <array>

namespace DisplayReg = DisplayDriver::St7789vRegisters;

namespace DisplayDriver
{

St7789V::St7789V(
            Interface::Spi::SpiBus* _busPtr
        ,   std::uint16_t _width
        ,   std::uint16_t _height
    )
    :   
        m_width{ _width }
    ,   m_height { _height }
    ,   m_pBusPtr{ _busPtr }
    ,   m_completedTransitionsCount{}
{
    initGpio();
    initDisplay();
    initColumnRow( _width, _height );
}

void
St7789V::initDisplay()
{
    nrf_gpio_pin_clear( DISP_RST );
    nrf_delay_ms( 100 );
    nrf_gpio_pin_set( DISP_RST );

    sendCommand(    DisplayReg::SWRESET    );
    nrf_delay_ms( 150 );
    sendCommand(    DisplayReg::SLPOUT     );
    sendCommand(    DisplayReg::COLMOD     , 0x55   );
    sendCommand(    DisplayReg::MADCTL     , 0x08   );
    sendCommand(    DisplayReg::CASET      , 0x00,0,0,240 );
    sendCommand(    DisplayReg::RASET      , 0x00, 0, 320>>8, 320&0xFF );
    sendCommand(    DisplayReg::INVON      );
    sendCommand(    DisplayReg::NORON      );
    sendCommand(    DisplayReg::DISPON     );
    sendCommand(    DisplayReg::MADCTL     , 0xC0   ); // 0xC0 for inverted orientation

    m_pBusPtr->runQueue();
}

void St7789V::sendCommand(
        std::uint8_t _command
)
{
    Interface::Spi::Transaction commandTransaction;

    commandTransaction.beforeTransaction =
        [ this ]
        {
            resetDcPin();
        };
    
    commandTransaction.transactionAction =
        [ this, _command ]
        {
            m_pBusPtr->sendData( _command );
        };

    commandTransaction.afterTransaction =
        [ this ]
        {
            setDcPin();
        };
    
    m_pBusPtr->addTransaction( std::move( commandTransaction ) );

}

template< typename ... Args >
void St7789V::sendCommand(
        std::uint8_t _command
    ,   Args... _commandArgs
    )
{
    sendCommand( _command );
    sendChunk( _commandArgs... );
}

template< typename ... Args >
void St7789V::sendChunk(
        Args... _chunkArgs
)
{
    std::array chunk = { _chunkArgs... };

    Interface::Spi::Transaction chunkTransaction;

    chunkTransaction.beforeTransaction =
        [ this ]
        {
            setDcPin();
        };
    
    chunkTransaction.transactionAction =
        [ this, chunk ]
        {
            m_pBusPtr->sendChunk( chunk );
        };

    chunkTransaction.afterTransaction =
        [ this ]
        {
            resetDcPin();
        };
    
    m_pBusPtr->addTransaction( std::move( chunkTransaction ) );
}

void St7789V::initColumnRow(
        std::uint16_t _width
    ,   std::uint16_t _height
)
{
    if(
            _width == DisplayDriver::St7789v::Disp208_240::Width
        &&  _height == DisplayDriver::St7789v::Disp208_240::Height
    )
    {
        m_columnStart = 0;
        m_rowStart = 80;
    }
    else if(
            _width == DisplayDriver::St7789v::Disp240_320::Width
        &&  _height == DisplayDriver::St7789v::Disp240_320::Height
    )
    {
        m_columnStart = 0;
        m_rowStart = 0;
    }
}

void St7789V::turnOn()
{
    sendCommand( DisplayReg::DISPON );
}

void St7789V::turnOff()
{
    sendCommand( DisplayReg::DISPOFF );
}

void St7789V::fillColor( DisplayDriver::Colors _color )
{
//    fillRectangle(
//            0
//        ,   0
//        ,   m_width
//        ,   m_height
//        ,   _color
//    );
}


void St7789V::fillRectangle(
        std::uint16_t _x
    ,   std::uint16_t _y
    ,   std::uint16_t _width
    ,   std::uint16_t _height
    ,   IDisplayDriver::TColor* _colorToFill
)
{
    if((_x >= m_width) || (_y >= m_height )) return;
    if((_x + _width - 1) >= m_width) _width = m_width - _x;
    if((_y + _height - 1) >= m_height) _height = m_height - _y;

    std::uint16_t areaXSize = _x + _width;
    std::uint16_t areaYSize = _y + _height;

    constexpr size_t DmaBufferSize = Interface::Spi::SpiBus::DmaBufferSize;

    const size_t FullDmaTransactionsCount = ( areaXSize * areaYSize * 2 ) / DmaBufferSize;
    const size_t ChunkedTransactionsCount = ( areaXSize * areaYSize * 2 ) % DmaBufferSize;

    setAddrWindow(
            _x
        ,   _y
        ,   _x + _width - 1
        ,   _y + _height - 1
    );

    sendCommand( DisplayReg::RAMWR );

    if( FullDmaTransactionsCount > 0 )
    {
        Interface::Spi::Transaction fullTransaction;
        fullTransaction.beforeTransaction =
            [ this ]
            {
                setDcPin();
            };

        m_completedTransitionsCount = 0;

        fullTransaction.transactionAction =
            [this, &_colorToFill]
            {
                m_pBusPtr->sendChunk(
                        reinterpret_cast<const std::uint8_t*>( _colorToFill ) + DmaBufferSize
                            *   getTransitionOffset()
                    ,   DmaBufferSize
                );
            };

        if( FullDmaTransactionsCount > 1 )
            fullTransaction.repeatsCount = FullDmaTransactionsCount;

        m_pBusPtr->addTransaction( std::move( fullTransaction ) );
    }

    if( ChunkedTransactionsCount > 0 )
    {
        Interface::Spi::Transaction chunkTransmission;
        chunkTransmission.beforeTransaction =
            [ this ]
            {
                setDcPin();
            };

        chunkTransmission.transactionAction =
            [this, &_colorToFill,ChunkedTransactionsCount ,FullDmaTransactionsCount ]
            {
                m_pBusPtr->sendChunk(
                        reinterpret_cast<const std::uint8_t*>( _colorToFill ) + DmaBufferSize * FullDmaTransactionsCount
                    ,   ChunkedTransactionsCount
                );
            };
        m_pBusPtr->addTransaction( std::move( chunkTransmission ) );
    }

    m_pBusPtr->runQueue();
}

std::uint32_t St7789V::getTransitionOffset()
{
    return ++m_completedTransitionsCount;
}

//void St7789V::startFrameBufferTransimission()
//{
//    m_transactionStartedId = m_pBusPtr->onTransactionStarted.connect(
//            [ this ]
//            {
//                fillTranasctionBuffer();
//            }
//        ,   m_transactionStartedId
//    );

//    m_transactionCompletedId = m_pBusPtr->onTransactionCompleted.connect(
//            [ this ]
//            {
//                setDcPin();
//                transmitRestBuffer();
//            }
//        ,   m_transactionCompletedId
//    );
//}

void St7789V::setAddrWindow(
            std::uint16_t _x
        ,   std::uint16_t _y
        ,   std::uint16_t _width
        ,   std::uint16_t _height
)
{
    _x +=m_columnStart;
    _y +=m_rowStart;

    uint32_t xa = ((uint32_t)_x << 16) | (_x+_width-1);
    uint32_t ya = ((uint32_t)_y << 16) | (_y+_height-1); 

    sendCommand(
            DisplayReg::CASET
        ,   static_cast<std::uint8_t>( xa >> 24 )
        ,   static_cast<std::uint8_t>( xa >> 16 )
        ,   static_cast<std::uint8_t>( xa >> 8 )
        ,   static_cast<std::uint8_t>( xa )
    );

    sendCommand(
            DisplayReg::RASET
        ,   static_cast<std::uint8_t>( ya >> 24 )
        ,   static_cast<std::uint8_t>( ya >> 16 )
        ,   static_cast<std::uint8_t>( ya >> 8 )
        ,   static_cast<std::uint8_t>( ya )
    );
    
}

void St7789V::initGpio()
{
    nrf_gpio_cfg_output( DISP_RST );
    nrf_gpio_cfg_output( DISP_DC_PIN );
}

void St7789V::resetDcPin()
{
    nrf_gpio_pin_clear( DISP_DC_PIN );
}
    
void St7789V::setDcPin()
{
    nrf_gpio_pin_set( DISP_DC_PIN );
}

//void St7789V::fillTranasctionBuffer()
//{
//    m_isSwapBufferReady = false;

//    const FrameBuffer::RowType& rowToTransmit{ m_frameBuffer->getNextTransmissionRow() };

//    std::uint16_t dmaBufferIndex{};

//    for( DisplayDriver::EncodedColor pixel: rowToTransmit )
//    {
//        using TUnderlyingColor = std::underlying_type_t<DisplayDriver::Colors>;

//        DisplayDriver::Colors decodedColor = DisplayDriver::fromEncodedColor( pixel );
//        TUnderlyingColor underlyingColor = static_cast<TUnderlyingColor>( decodedColor );

//        std::uint8_t msbColor = underlyingColor >> 8;
//        std::uint8_t lsbColor = underlyingColor & 0xFF;

//        DmaSwapBuffer[ dmaBufferIndex++ ] = msbColor;
//        DmaSwapBuffer[ dmaBufferIndex++ ] = lsbColor;
//        DmaSwapBuffer[ dmaBufferIndex++ ] = msbColor;
//        DmaSwapBuffer[ dmaBufferIndex++ ] = lsbColor;
//    }
//    m_isSwapBufferReady = true;
//    onSwapBufferReady.emit();

//}

std::unique_ptr<St7789V>
createDisplayDriver(
        Interface::Spi::SpiBus* _busPtr
    ,   std::uint16_t _width
    ,   std::uint16_t _height
)
{
    return std::make_unique<St7789V>(
            _busPtr
        ,   _width
        ,   _height
    );
}

};
