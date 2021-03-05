#pragma once

#include <cstdint>

#include "mbed.h"

#include "LTC681xBus.h"

class LTC681xParallelBus : public LTC681xBus {
public:
  LTC681xParallelBus(SPI* spiDriver) : m_spiDriver(spiDriver) {};

  LTC681xBusStatus WakeupBus();

  LTC681xBusStatus SendCommand(LTC681xBusCommand cmd);
  LTC681xBusStatus SendDataCommand(LTC681xBusCommand cmd, uint8_t* data);
  LTC681xBusStatus SendReadCommand(LTC681xBusCommand cmd, uint8_t* data);
private:
  SPI* m_spiDriver;
};
