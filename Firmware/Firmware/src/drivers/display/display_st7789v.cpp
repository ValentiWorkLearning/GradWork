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
        m_completedTransitionsCount{}
    ,   m_width{ _width }
    ,   m_height { _height }
    ,   m_pBusPtr{ _busPtr }
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
    Interface::Spi::Transaction commandTransaction{};

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

    Interface::Spi::Transaction chunkTransaction{};

    chunkTransaction.beforeTransaction =
        [ this ]
        {
            setDcPin();
        };
    
    chunkTransaction.transactionAction =
        [ this, chunkToSend = std::move( chunk ) ]
        {
            m_pBusPtr->sendChunk(
                    reinterpret_cast<const std::uint8_t*>( chunkToSend.data() )
                ,   chunkToSend.size()
            );
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
        m_rowStart = 40;
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

void St7789V::fillRectangle(
        std::uint16_t _x
    ,   std::uint16_t _y
    ,   std::uint16_t _width
    ,   std::uint16_t _height
    ,   IDisplayDriver::TColor* _colorToFill
)
{
    if( (_x >= m_width) || (_y >= m_height )) return;
    if( _width >= m_width) _width = m_width - _x;
    if( _height>= m_height) _height = m_height - _y;

    constexpr size_t DmaBufferSize = Interface::Spi::SpiBus::DmaBufferSize;

    const size_t BytesSizeX = ( _width - _x + 1 );
    const size_t BytesSizeY = ( _height - _y + 1);
    const size_t BytesSquare = BytesSizeX *  BytesSizeY;

    const size_t FullDmaTransactionsCount =  ( BytesSquare* sizeof ( IDisplayDriver::TColor ) )  / DmaBufferSize;
    const size_t ChunkedTransactionsCount = ( BytesSquare* sizeof ( IDisplayDriver::TColor ) )  % DmaBufferSize;

    setAddrWindow(
            _x
        ,   _y
        ,   _width
        ,   _height
    );

    sendCommand( DisplayReg::RAMWR );

    m_completedTransitionsCount = 0;

    if( FullDmaTransactionsCount > 0 )
    {
        Interface::Spi::Transaction fullTransaction{};
        fullTransaction.beforeTransaction =
            [ this ]
            {
                setDcPin();
            };

        fullTransaction.transactionAction =
            [this, _colorToFill]
            {
                std::uint32_t addrOffset = Interface::Spi::SpiBus::DmaBufferSize
                            *   getTransitionOffset();

                m_pBusPtr->sendChunk(
                        reinterpret_cast<const std::uint8_t*>( _colorToFill ) + addrOffset
                    ,   Interface::Spi::SpiBus::DmaBufferSize
                );
            };

        if( FullDmaTransactionsCount > 1 )
            fullTransaction.repeatsCount = FullDmaTransactionsCount - 1;

        if( ChunkedTransactionsCount == 0 )
            fullTransaction.afterTransaction = 
                [this]
                {
                    onRectArreaFilled.emit();
                    resetDcPin();
                };

        m_pBusPtr->addTransaction( std::move( fullTransaction ) );
    }

    if( ChunkedTransactionsCount > 0 )
    {
        Interface::Spi::Transaction chunkTransmission{};
        chunkTransmission.beforeTransaction =
            [ this ]
            {
                setDcPin();
            };

        chunkTransmission.transactionAction =
            [this, _colorToFill,ChunkedTransactionsCount ,FullDmaTransactionsCount ]
            {
                const size_t transmissionOffset = FullDmaTransactionsCount >= 1
                    ?   DmaBufferSize * getTransitionOffset() : 0;

                m_pBusPtr->sendChunk(
                        reinterpret_cast<const std::uint8_t*>( _colorToFill ) + transmissionOffset
                    ,   ChunkedTransactionsCount
                );
            };
            chunkTransmission.afterTransaction = 
                [this]
                {
                    onRectArreaFilled.emit();
                    resetDcPin();
                };

        m_pBusPtr->addTransaction( std::move( chunkTransmission ) );
    }
    
    m_pBusPtr->runQueue();
}

std::uint32_t St7789V::getTransitionOffset()
{
    return m_completedTransitionsCount++;
}

void St7789V::setAddrWindow(
            std::uint16_t _x
        ,   std::uint16_t _y
        ,   std::uint16_t _width
        ,   std::uint16_t _height
)
{
    // TODO be careful here;
    std::uint16_t width = _width - _x;
    std::uint16_t height = _height - _y;

    std::uint16_t correctedX = _x + m_columnStart;
    std::uint16_t correctedY = _y + m_rowStart;

    uint32_t xa = ((uint32_t)correctedX << 16) | ( correctedX + width);// (_x+_width-1);
    int32_t ya = ((uint32_t)correctedY << 16) | ( correctedY +  height); //(_y+_height-1); 

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
