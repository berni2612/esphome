#pragma once

#include "config.h"
#if MASK_VERSION == 0x07B0

#include "bau_systemB_device.h"
#include "tpuart_data_link_layer.h"

namespace esphome {
namespace knx {

class Bau07B0 : public BauSystemBDevice, public ITpUartCallBacks {
 public:
  Bau07B0(Platform &platform);
  void loop() override;
  bool enabled() override;
  void enabled(bool value) override;

 protected:
  InterfaceObject *getInterfaceObject(uint8_t idx);
  InterfaceObject *getInterfaceObject(ObjectType objectType, uint8_t objectInstance);

  // For TP1 only
  bool isAckRequired(uint16_t address, bool isGrpAddr) override;

 private:
  TpUartDataLinkLayer _dlLayer;
};

}  // namespace knx
}  // namespace esphome

#endif
