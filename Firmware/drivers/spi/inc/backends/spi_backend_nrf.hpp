#pragma once

#include <memory>
#include <atomic>

#include <etl/vector.h>
#include <etl/queue.h>

namespace Interface::SpiTemplated
{

namespace SpiInstance
{
	struct M1 {};
	struct M2 {};
}

template<typename PeripheralInstance>
class NordicSpi
{

public:

    void sendChunk(
        const std::uint8_t* _pBuffer
        , const size_t _bufferSize
    )noexcept
    {
        nrfx_spim_xfer_desc_t xferDesc =
            NRFX_SPIM_XFER_TX(
                _pBuffer
                , _bufferSize
            );

        nrfx_err_t transmissionError = nrfx_spim_xfer(
            &m_spiHandle
            , &xferDesc
            , 0
        );

        APP_ERROR_CHECK(transmissionError);
    }

    using TTransactionCompletedHandler = std::function<void()>;
    void setTransactionCompletedHandler(TTransactionCompletedHandler&& _handler)
    {
        m_transactionCompleted = std::move(_handler);
    }

private:

    static void spimEventHandler(
        nrfx_spim_evt_t const* _pEvent
        , void* _pContext
    )noexcept
    {
        if (_pEvent->type == NRFX_SPIM_EVENT_DONE)
        {
            auto pThis = reinterpret_cast<SpiBusAsync::SpiAsyncBackendImpl*>(_pContext);
            pThis->m_transactionCompleted();
        }
    }

public:
    nrfx_spim_t m_spiHandle;
    TTransactionCompletedHandler m_transactionCompleted;
};

}