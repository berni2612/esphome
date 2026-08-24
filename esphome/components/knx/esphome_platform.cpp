#include "esphome_platform.h"

#include "esphome/core/preferences.h"
#include "esphome/core/application.h"

namespace esphome {
namespace knx {

ESPHomePlatform::ESPHomePlatform(uint32_t objectIdHash, esphome::uart::UARTDevice *uart) : uart_(uart) {
  this->pref_ = global_preferences->make_preference<EEPROMBuffer>(objectIdHash);
  this->pref_.load(&this->_eepromBuffer);
}

void ESPHomePlatform::restart() {
  // Implement restart using ESPHome API
  App.safe_reboot();
}

void ESPHomePlatform::fatalError() {
  // Implement fatal error handling using ESPHome API
}

void ESPHomePlatform::setupUart() {
  // UART setup is handled by ESPHome's UART component
}

void ESPHomePlatform::closeUart() {
  // UART closing is handled by ESPHome's UART component
}

int ESPHomePlatform::uartAvailable() { return this->uart_->available(); }

size_t ESPHomePlatform::writeUart(const uint8_t data) {
  this->uart_->write_byte(data);
  return 1;
}

size_t ESPHomePlatform::writeUart(const uint8_t *buffer, size_t size) {
  this->uart_->write_array(buffer, size);
  return size;
}

int ESPHomePlatform::readUart() {
  uint8_t data;
  if (!this->uart_->available() || !this->uart_->read_byte(&data))
    return -1;
  return data;
}

size_t ESPHomePlatform::readBytesUart(uint8_t *buffer, size_t length) {
  if (this->uart_->available() >= length && this->uart_->read_array(buffer, length))
    return length;
  return 0;
}

uint8_t *ESPHomePlatform::getEepromBuffer(uint32_t size) {
  if (size > KNX_FLASH_SIZE) {
    return nullptr;
  }
  return this->_eepromBuffer.data;
}

void ESPHomePlatform::commitToEeprom() { this->pref_.save(&this->_eepromBuffer); }

}  // namespace knx
}  // namespace esphome
