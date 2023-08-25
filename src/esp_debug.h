#ifndef _DEBUG_H_
#define _DEBUG_H_

#include <Arduino.h>
#include "esp_array.h" // https://github.com/guilhAbreu/EspMath

using namespace espmath;

/**
 * @brief Enable or disable the debug mode.
 * 
 * If debug mode is enabled, then debug prints via serial port will be displayed.
 * If debug mode is disabled, then debug prints won't take effect. Also, Serial.begin() won't be called.
 * 
 * @note Debug prints don't affect the performance of the app if debug mode is disabled.
 */
#define DEBUG_MODE 1

/**
 * @brief Implement methods to consistent print debug output via serial port
 * 
 */
class Debugger{
public:

  /**
   * @brief Construct a new Debugger object
   * 
   * @param baud The baud rate
   */
  Debugger(unsigned long int baud = 115200);

  /**
   * @brief Get the information about the debug mode status
   * 
   * @return true If debug mode is enabled.
   * @return false If debug mode is disabled.
   */
  bool enabled();

  /**
   * @brief Print out content via serial port
   * 
   * @tparam T Content type
   * @param content The content
   * @param newLine If true then print will break the line.
   * @param same If true, Debug log won't be printed.
   */
  template<typename T>
  void print(const T content, bool newLine = true, bool same = false)
  {
    if (!log_print_i) return;
    newLine ? _println(String(content)) : _print(String(content), same);
  }

  template<typename T>
  void print(const T* const array, size_t _length, unsigned char opt = DEC)
  {
    if (log_print_i > 0 && _length > 0)
    {
      _print("[" + String(array[0], opt));
      for(size_t i = 1; i < _length; i++)
      {
        _print(", " + String(array[i], opt), true);
      }
      _println(String("]"), true);
    }
  }

  void print(const fixed* const array, size_t _length, unsigned int dec = 4)
  {
    if (log_print_i > 0 && _length > 0)
    {
      _print("[" + String((float)array[0], dec));
      for(size_t i = 1; i < _length; i++)
      {
        _print(", " + String((float)array[i], dec), true);
      }
      _println(String("]"), true);
    }
  }

  template<typename T>
  void print(const T* const array, size_t rows, size_t columns, unsigned char opt = DEC)
  {
    if (log_print_i > 0 && rows*columns > 0)
    {
      for (size_t j = 0; j < rows; j++)
      {
        _print("|" + String(array[j*columns + 0], opt));
        for(size_t i = 1; i < columns; i++)
          _print(" " + String(array[j*columns + i], opt), true);
        _println(String("|"), true);
      }
    }
  }
  
  void print(const float* const array, size_t _length, unsigned int decimals = 4)
  {
    if (log_print_i > 0 && _length > 0)
    {
      _print("[" + String(array[0], decimals));
      for(size_t i = 1; i < _length; i++)
      {
        _print(", " + String(array[i], decimals), true);
      }
      _println(String("]"), true);
    }
  }

  void print(const float* const array, size_t rows, size_t columns, unsigned int decimals = 4)
  {
    if (log_print_i > 0 && rows*columns > 0)
    {
      for (size_t j = 0; j < rows; j++)
      {
        _print("|" + String(array[j*columns + 0], decimals));
        for(size_t i = 1; i < columns; i++)
          _print(" " + String(array[j*columns + i], decimals), true);
        _println(String("|"), true);
      }
    }
  }
private:
  uint64_t log_print_i = 0;

  /**
   * @brief Actually write outputs via serial port
   * 
   * @param content
   * @param same If true, Debug log won't be printed.
   */
  void _println(String content, bool same = false);

  /**
   * @brief Actually write outputs via serial port without \n
   * 
   * @param content 
   * @param same If true, Debug log won't be printed.
   */
  void _print(String content, bool same = false);
};

/**
 * @brief Global debugger object
 * 
 */
extern Debugger debug;

#endif