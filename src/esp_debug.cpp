#include "esp_debug.h"

static portMUX_TYPE debugMux = portMUX_INITIALIZER_UNLOCKED;
Debugger debug(115200);


Debugger::Debugger(unsigned long int baud){
#if !DEBUG_MODE
  return;
#endif
  log_print_i++;
  Serial.begin(baud);
  Serial.println("Debug Enabled!");
}

bool Debugger::enabled(){
  return (bool) log_print_i;
}

void Debugger::_print(String content, bool same){
  taskENTER_CRITICAL(&debugMux);
  vTaskDelay(pdMS_TO_TICKS(10));
  
  if (!same)
  {
    Serial.print("Debug[0x");
    vTaskDelay(pdMS_TO_TICKS(10));
    Serial.print(log_print_i, HEX);
    vTaskDelay(pdMS_TO_TICKS(10));
    Serial.print("]: ");
    vTaskDelay(pdMS_TO_TICKS(10));
    log_print_i++;
  }
  
  
  Serial.print(content);
  
  taskEXIT_CRITICAL(&debugMux);
}

void Debugger::_println(String content, bool same){
  taskENTER_CRITICAL(&debugMux);
  vTaskDelay(pdMS_TO_TICKS(10));
  
  if (!same)
  {
    Serial.print("Debug[0x");
    vTaskDelay(pdMS_TO_TICKS(10));
    Serial.print(log_print_i, HEX);
    vTaskDelay(pdMS_TO_TICKS(10));
    Serial.print("]: ");
    vTaskDelay(pdMS_TO_TICKS(10));
    log_print_i++;
  }
  
  
  Serial.println(content);
  
  taskEXIT_CRITICAL(&debugMux);
}