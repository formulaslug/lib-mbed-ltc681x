#pragma once

#include <cstdint>

#include "LTC681xCommand.h"

#define LTC681x_WAKEUP_DELAY 420

class LTC681xBusCommand {
public:
  //
  // Addressing mode to use when sending a bus command
  //
  enum class AddressingMode : uint8_t {
    kBroadcast = 0x00,
    kChain = 0x00,
    kAddress = 0x01
  };

  //
  // Build an addressed bus command
  //
  LTC681xBusCommand(LTC681xCommand& command, uint8_t address);

  //
  // Build a broadcast/chain bus command
  //
  LTC681xBusCommand(LTC681xCommand& command);

  uint16_t toValue();

  AddressingMode mode;
  uint8_t address;
};

class LTC681xBus {
public:
  enum class LTC681xBusStatus : uint8_t {
    Ok,
    BadPec
  };

  virtual LTC681xBusStatus WakeupBus() const = 0;

  virtual LTC681xBusStatus SendCommand(LTC681xBusCommand cmd) const = 0;
  virtual LTC681xBusStatus SendDataCommand(LTC681xBusCommand cmd, uint8_t* data) const = 0;
  virtual LTC681xBusStatus SendReadCommand(LTC681xBusCommand cmd, uint8_t* data) const = 0;

protected:
  static uint16_t calculatePec(uint8_t length, uint8_t *data);
  static void getCommandBytes(uint8_t* buf, LTC681xBusCommand cmd);
  static void getDataBytes(uint8_t* buf, uint8_t data[6]);
};
