#include "esphome_platform.h"

namespace esphome {
namespace knx {

ESPHomePlatform::ESPHomePlatform(esphome::uart::UARTDevice *uart) : uart_(uart) {}

void ESPHomePlatform::restart() {
  // Implement restart logic using ESPHome API
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
  if (!this->uart_->read_byte(&data))
    return -1;
  return data;
}

size_t ESPHomePlatform::readBytesUart(uint8_t *buffer, size_t length) {
  if (this->uart_->read_array(buffer, length))
    return length;
  return 0;
}

}  // namespace knx
}  // namespace esphome
