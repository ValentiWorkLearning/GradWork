//#include <display/display_coro_compact_gc9a01.hpp>
//
//#define FMT_HEADER_ONLY 
//#include <fmt/core.h>
//#include <logger/logger_service.hpp>
//
//namespace DisplayDriver
//{
//
//GC9A01Compact::GC9A01Compact(std::unique_ptr<Interface::Spi::SpiBusAsync>&& _busPtr, std::uint16_t _width, std::uint16_t _height) noexcept
//    : BaseSpiDisplayCoroutine(
//        std::move(_busPtr)
//        , _width
//        , _height
//    )
//{
//}
//
//void
//GC9A01Compact::initialize() noexcept
//{
//    initDisplay();
//}
//
//void
//GC9A01Compact::fillRectangle(
//    std::uint16_t _x,
//    std::uint16_t _y,
//    std::uint16_t _width,
//    std::uint16_t _height,
//    IDisplayDriver::TColor* _colorToFill
//) noexcept
//{
//
//}
//
//void
//GC9A01Compact::initDisplay() noexcept
//{
//    BaseSpiDisplayCoroutine::resetResetPin();
//    Delay::waitFor( 100 );
//    BaseSpiDisplayCoroutine::setResetPin();
//    //static std::array Test = std::array<std::uint8_t, CommandsSize>{0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09,0x0A};
//    //co_await BaseSpiDisplayCoroutine::sendChunk(Test.data(), Test.size());
//    size_t CommandCount = CommandsTransactionsCount;
//    const std::uint8_t* pBuffer = Commands.data();
//    while(CommandCount--)
//    {
//        const std::uint8_t* Command = pBuffer++;
//        const std::uint8_t NumArgs = *pBuffer++;
//        const std::uint8_t Delay = *pBuffer++;
//
//        co_await BaseSpiDisplayCoroutine::sendCommandImpl(Command);
//        if (NumArgs) {
//            co_await BaseSpiDisplayCoroutine::sendChunk(pBuffer++, NumArgs);
//            pBuffer+=(NumArgs - 1);
//        }
//        if(Delay)
//            Delay::waitFor(Delay);
//    }
//    m_displayInitialized.set();
//}
//
//CoroUtils::VoidTask
//GC9A01Compact::setAddrWindow(
//    std::uint16_t _x,
//    std::uint16_t _y,
//    std::uint16_t _width,
//    std::uint16_t _height
//) noexcept
//{
//        // TODO be careful here;
//    std::uint16_t width = _width - _x;
//    std::uint16_t height = _height - _y;
//
//    std::uint16_t correctedX = _x;
//    std::uint16_t correctedY = _y;
//
//    uint32_t xa = ((uint32_t)correctedX << 16) | ( correctedX + width);// (_x+_width-1);
//    int32_t ya = ((uint32_t)correctedY << 16) | ( correctedY +  height); //(_y+_height-1); 
//
//    static std::array xAxisCommand =
//        std::array{
//                static_cast<std::uint8_t>( 0x2a )
//            ,   static_cast<std::uint8_t>( xa >> 24 )
//            ,   static_cast<std::uint8_t>( xa >> 16 )
//            ,   static_cast<std::uint8_t>( xa >> 8 )
//            ,   static_cast<std::uint8_t>( xa )
//        };
//    static std::array yAxisCommand =
//        std::array{
//                static_cast<std::uint8_t>( 0x2b )
//            ,   static_cast<std::uint8_t>( ya >> 24 )
//            ,   static_cast<std::uint8_t>( ya >> 16 )
//            ,   static_cast<std::uint8_t>( ya >> 8 )
//            ,   static_cast<std::uint8_t>( ya )
//        };
//
//    co_await CoroUtils::when_all_sequence(
//            sendCommandFast(xAxisCommand.data(), xAxisCommand.size())
//        ,   sendCommandFast(yAxisCommand.data(), yAxisCommand.size())
//    );
//}
//
//bool
//GC9A01Compact::isInitialized() const noexcept
//{
//    return m_displayInitialized.isSet();
//}
//
//std::unique_ptr<GC9A01Compact> createDisplayDriverCompactCoroBasedGC9A01(
//    std::unique_ptr<Interface::Spi::SpiBusAsync>&& _busPtr,
//    std::uint16_t _width,
//    std::uint16_t _height
//) noexcept
//{
//    return std::make_unique<GC9A01Compact>(
//        std::move(_busPtr),
//        _width,
//        _height
//    );
//}
//
//}
