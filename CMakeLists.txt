set(COMPONENT_SRCS
  src/esp_debug.cpp
)

set(COMPONENT_LIBRARIES
  src/
)

idf_component_register(
  SRCS ${COMPONENT_SRCS}
  INCLUDE_DIRS ${COMPONENT_LIBRARIES}
  REQUIRES arduino-esp32 EspMath
)