#pragma once

#include <memory>
#include <atomic>

#include <etl/vector.h>
#include <etl/queue.h>

#include <pca10040.h>
#include <nrfx_spim.h>

#define FMT_HEADER_ONLY
#include <fmt/core.h>
#include <logger/logger_service.hpp>

namespace Interface::SpiTemplated
{

namespace SpiInstance
{
	struct M1
    {
        static constexpr std::uint8_t ClockPin = SPIM1_SCK_PIN;
        static constexpr std::uint8_t MisoPin = SPIM1_MISO_PIN;
        static constexpr std::uint8_t MosiPin = SPIM1_MOSI_PIN;
        static constexpr std::uint8_t SlaveSelectPin = SPIM1_SS_PIN;
        static constexpr size_t HandleIdx = 0;
    };
	struct M2
    {
        static constexpr std::uint8_t ClockPin = SPIM2_SCK_PIN;
        static constexpr std::uint8_t MisoPin = SPIM2_MISO_PIN;
        static constexpr std::uint8_t MosiPin = SPIM2_MOSI_PIN;
        static constexpr std::uint8_t SlaveSelectPin = SPIM2_SS_PIN;

        static constexpr size_t HandleIdx = 1;
    };

    constexpr size_t InstanceCount = 2;
    static std::array<nrfx_spim_t,InstanceCount> HandleStorage{
            nrfx_spim_t{                                                           
                .p_reg        = NRF_SPIM1,
                .drv_inst_idx = NRFX_SPIM1_INST_IDX
            },
            nrfx_spim_t{                                                           
                .p_reg        = NRF_SPIM2,
                .drv_inst_idx = NRFX_SPIM2_INST_IDX
            }
    };
}

template<typename PeripheralInstance>
class NordicSpi
{

public:
    using This_t = NordicSpi<PeripheralInstance>;
    NordicSpi()noexcept
    {

        nrfx_spim_config_t spiConfig{};

        spiConfig.sck_pin = PeripheralInstance::ClockPin;
        spiConfig.mosi_pin = PeripheralInstance::MosiPin;
        spiConfig.miso_pin = PeripheralInstance::MisoPin;
        spiConfig.ss_pin = PeripheralInstance::SlaveSelectPin;
        spiConfig.ss_active_high = false;
        spiConfig.irq_priority = NRFX_SPIM_DEFAULT_CONFIG_IRQ_PRIORITY;
        spiConfig.orc = 0xFF;
        spiConfig.frequency = NRF_SPIM_FREQ_8M;
        spiConfig.mode = NRF_SPIM_MODE_0;
        spiConfig.bit_order = NRF_SPIM_BIT_ORDER_MSB_FIRST;

        APP_ERROR_CHECK(
            nrfx_spim_init(
            &SpiInstance::HandleStorage[PeripheralInstance::HandleIdx],
            &spiConfig,
            spimEventHandlerThisOne,
            this
            )
        );
    }

    void sendChunk(
        const std::uint8_t* _pBuffer
        , const size_t _bufferSize
    )noexcept
    {
        nrfx_spim_xfer_desc_t xferDesc =
            NRFX_SPIM_XFER_TX(
                _pBuffer,
                _bufferSize
            );

        nrfx_err_t transmissionError = nrfx_spim_xfer(
            &SpiInstance::HandleStorage[PeripheralInstance::HandleIdx],
            &xferDesc,
            0
        );
        APP_ERROR_CHECK(transmissionError);
    }

    void receiveChunk(
        const std::uint8_t* _pTransmitZeroArray,
        const std::uint8_t* _pDestinationArray,
        size_t _bufferSize
    )
    {
        nrfx_spim_xfer_desc_t xferDesc =
            NRFX_SPIM_XFER_TRX(
                _pTransmitZeroArray,
                _bufferSize,
                _pDestinationArray,
                _bufferSize
            );

        nrfx_err_t transmissionError = nrfx_spim_xfer(
            &SpiInstance::HandleStorage[PeripheralInstance::HandleIdx],
            &xferDesc,
            0
        );
        APP_ERROR_CHECK(transmissionError);
    }

    using TTransactionCompletedHandler = std::function<void()>;
    void setTransactionCompletedHandler(const TTransactionCompletedHandler& _handler)noexcept
    {
        m_transactionCompleted = _handler;
    }

private:

    static void spimEventHandlerThisOne(
        nrfx_spim_evt_t const* _pEvent,
        void* _pContext
    )noexcept
    {
        if (_pEvent->type == NRFX_SPIM_EVENT_DONE)
        {
            auto pThis = reinterpret_cast<This_t*>(_pContext);
            pThis->m_transactionCompleted();
        }
    }

public:
    TTransactionCompletedHandler m_transactionCompleted;
};

}