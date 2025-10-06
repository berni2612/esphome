#pragma once

#include "bau_systemB.h"
#include "platform.h"

#include "esphome/core/component.h"
#include "esphome/components/uart/uart.h"

namespace esphome {
namespace knx {

class KnxComponent : public uart::UARTDevice, public Component {
 public:
  void setup() override;
  void loop() override;
  void dump_config() override;

  uint32_t startup_time() const { return this->startup_time_; }
  void startup_time(uint32_t time_ms) { this->startup_time_ = time_ms; }

  bool prog_mode() const {
    return this->bau_ != nullptr && this->bau_->enabled() && this->bau_->deviceObject().progMode();
  }
  void prog_mode(bool value) {
    if (this->bau_ != nullptr && this->bau_->enabled())
      this->bau_->deviceObject().progMode(value);
  }

 protected:
  static void knx_loop(void *arg);

  Platform *platform_{nullptr};
  BauSystemB *bau_{nullptr};

  uint32_t startup_time_{5000};  // ms
};

}  // namespace knx
}  // namespace esphome
