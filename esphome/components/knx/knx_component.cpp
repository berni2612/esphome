#include "knx_component.h"

#include "esphome_platform.h"
#include "bau07B0.h"

#include "esphome/core/log.h"

namespace esphome {
namespace knx {

static const char *TAG = "knx.component";

void KnxComponent::setup() {
  // Initialize the KNX platform
  if (this->platform_ == nullptr) {
    static constexpr uint32_t PREF_KEY = 0xA1B2C3D4;
    this->platform_ = new ESPHomePlatform(PREF_KEY, this);
  }
  if (this->bau_ == nullptr) {
    this->bau_ = new Bau07B0(*this->platform_);
  }

  this->bau_->deviceObject().version(0x0000);  // Version 0.0
  this->bau_->readMemory();

  if (this->bau_->configured()) {
    ESP_LOGI(TAG, "KNX component configured with address %u", this->bau_->deviceObject().individualAddress());
  } else {
    ESP_LOGW(TAG, "KNX component not yet configured");
    this->mark_failed();
  }
#if defined(USE_ESP32)
  // Yes, configMAX_PRIORITIES - 1 is the highest possible priority for a FreeRTOS task (priorities range from 0 to
  // configMAX_PRIORITIES - 1). The ESPHome main loop typically runs at priority 1 (see esphome/core/application.cpp).
  // To run the KNX loop at one higher priority, use priority 2.
  xTaskCreatePinnedToCore(knx_loop, "knx_loop", 4096, this, 2, nullptr, 0);
#else
#error "KNX component is only supported on ESP32"
#endif

  // // Serial/UART device initialization is typically done here.
  // // Note that a number of read/write methods are available in the UARTDevice
  // // class. See "uart/uart.h" for details.
  // uint8_t initialize_cmd = 0x12;  // Example command to initialize the device
  // this->write_byte(initialize_cmd);

  // uint8_t response;
  // if (this->read_byte(&response)) {
  //   this->mark_failed();  // Mark the component as failed if communication fails
  //   return;
  // }
  // if (response != 0) {  // Example check for a specific response
  //   ESP_LOGE(TAG, "Initialization failed; response: %d", response);
  //   this->mark_failed();  // Mark the component as failed if the response is not
  //                         // as expected
  //   return;
  // }
}

void KnxComponent::loop() {}

void KnxComponent::dump_config() {
  ESP_LOGCONFIG(TAG, "KNX Component:");
  ESP_LOGCONFIG(TAG, "  Startup time: %u ms", this->startup_time_);
}

void KnxComponent::knx_loop(void *arg) {
  auto self = reinterpret_cast<KnxComponent *>(arg);

  // Wait for the startup time to elapse
  ESP_LOGI(TAG, "Waiting %u ms for KNX startup", self->startup_time_);
  delay(self->startup_time_);
  ESP_LOGI(TAG, "KNX startup time elapsed, entering main loop");

  self->bau_->enabled(true);

  while (true) {
    self->bau_->loop();

    // sleep for 1ms
    delay(1);
  }
}

}  // namespace knx
}  // namespace esphome
