### Practical C++20 coroutines notes for ARM Cortex-M

Достаточно много времени прошло с предыдущей заметки на тему использования сопрограмм. Изначально было в планах продемонстрировать на чем-то концепцию и как именно их можно было применять. На тот момент вариант примера в виде мигания светодиодиком подошел отлично. Но он был слишком простой. Необходимо было придумать что-то более сложное и более полезное, что-ли. Таким образом и появилась идея переписать драйвер дисплея и SPI-флешки в проекте-долгострое.

Изначально, идея переписывания с подхода в виде транзакций появилась как только возникла необходимость расширения транзакционности read-транзакциями. Для формирования очереди отправки этот подход был достаточно удобным, но для очереди приема получалось что-то вроде callback-hell подхода.

В общих чертах, транзакционный подход представлял собой следующую идею:
```cpp
template <typename... Args> void sendCommand(std::uint8_t _command, Args... _commandArgs) noexcept
{
    sendCommand(_command);
    sendChunk(static_cast<std::uint8_t>(_commandArgs)...);
}

template <typename... Args> void sendChunk(Args... _chunkArgs) noexcept
{
    std::array chunk = {static_cast<std::uint8_t>(_chunkArgs)...};
    Interface::Spi::Transaction chunkTransaction{};

    chunkTransaction.beforeTransaction = [this] { setDcPin(); };

    chunkTransaction.transactionAction = [this, chunkToSend = std::move(chunk)] {
        m_pBusPtr->sendChunk(
            reinterpret_cast<const std::uint8_t*>(chunkToSend.data()), chunkToSend.size());
    };

    chunkTransaction.afterTransaction = [this] { resetDcPin(); };

    m_pBusPtr->addTransaction(std::move(chunkTransaction));
}
```

Т.е. у нас есть некоторое действие до транзакции, сама транзакция и действие, которое будет выполнено после нее. Использование так-же было достаточно удобным:
```cpp
sendCommand(DisplayReg::SLPOUT);
sendCommand(DisplayReg::COLMOD, 0x55);
sendCommand(DisplayReg::MADCTL, 0x08);
sendCommand(DisplayReg::CASET, 0x00, 0, 0, 240);
```
Этот подход достаточно хорошо себя показал в работе. Типовая задача для применения имела следующий вид:

1. Выставить состояние порта D/C для дисплея  для выбора типа принимаемых данных (команда или данные) 
2. Сформировать DMA- транзакцию
3. По ее окончанию выполнить следующую отправку, если блок данных был не полностью отправлен
4. Или вернуть состояние порта D/C в исходное состояние и перейти к обработке следующей транзакции

Недостатки стали проявляться при попытке реализации драйвера для SPI-FLASH которая должна была быть использована в связке с Little FS() 