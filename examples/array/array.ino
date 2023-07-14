#include "hard_debug.h"

uint32_t array0[6] = {1,2,3,4,5,6};
uint16_t array1[6] = {1,2,3,4,5,6};
uint8_t array2[4] = {1,2,3,4};
float array3[4] = {1,2,3,4};

void setup()
{
  vTaskDelay(pdMS_TO_TICKS(5000));
  debug.print("*************BEGIN**************");
  debug.print("***********FLAT*ARRAY***********");
  debug.print(array0, 6);
  debug.print("************MATRIX**************");
  debug.print(array1, 2U, 3U);
  debug.print("************MATRIX**************");
  debug.print(array2, 2U, 2U);
  debug.print("***********FLAT*ARRAY***********");
  debug.print(array3, 4);
  debug.print("************MATRIX**************");
  debug.print(array3, 2U, 2U);
  debug.print("********************************");
  debug.print("**************END***************");
}

void loop(){}