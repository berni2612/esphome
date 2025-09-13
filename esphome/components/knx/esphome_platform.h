#include "platform.h"

#include "esphome/components/uart/uart.h"

namespace esphome {
namespace knx {

class ESPHomePlatform : public Platform {
 public:
  ESPHomePlatform(esphome::uart::UARTDevice *uart);

  void restart() override;
  void fatalError() override;
  void setupUart() override;
  void closeUart() override;
  int uartAvailable() override;
  size_t writeUart(const uint8_t data) override;
  size_t writeUart(const uint8_t *buffer, size_t size) override;
  int readUart() override;
  size_t readBytesUart(uint8_t *buffer, size_t length) override;

 protected:
  esphome::uart::UARTDevice *uart_;
};

}  // namespace knx
}  // namespace esphome
