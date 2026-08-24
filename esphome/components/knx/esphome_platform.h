#pragma once

#include <knx/platform.h>

#include "esphome/components/uart/uart.h"

#include "esphome/core/preferences.h"

namespace esphome {
namespace knx {

class ESPHomePlatform : public ::Platform {
 public:
  ESPHomePlatform(uint32_t objectIdHash, esphome::uart::UARTDevice *uart);

  void restart() override;
  void fatalError() override;
  void setupUart() override;
  void closeUart() override;
  int uartAvailable() override;
  size_t writeUart(const uint8_t data) override;
  size_t writeUart(const uint8_t *buffer, size_t size) override;
  int readUart() override;
  size_t readBytesUart(uint8_t *buffer, size_t length) override;

  uint8_t *getEepromBuffer(uint32_t size) override;
  void commitToEeprom() override;

 protected:
  struct alignas(4) EEPROMBuffer {
    uint8_t data[KNX_FLASH_SIZE];
  };

  esphome::uart::UARTDevice *uart_;
  esphome::ESPPreferenceObject pref_;
  EEPROMBuffer _eepromBuffer{};
};

}  // namespace knx
}  // namespace esphome
