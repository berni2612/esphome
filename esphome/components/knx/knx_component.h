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

 protected:
  Platform *platform_{nullptr};
  BauSystemB *bau_{nullptr};
};

}  // namespace knx
}  // namespace esphome
