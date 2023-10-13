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
   * @tparam T Content type. It must be convertible into String.
   * @param content The content
   * @param newLine If true then print will break the line.
   * @param same If true, Debug log won't be printed.
   */
  template<typename T>
  void print(const T content, bool newLine = true, bool same = false)
  {
#if DEBUG_MODE
    newLine ? _println(String(content)) : _print(String(content), same);
#endif
  }
  
  /**
   * @brief Print out array content via serial port
   * 
   * @tparam T Content type. It must be arithmetic.
   * @param array The content
   * @param _length Length of the array
   * @param opt Base
   */
  template<typename T>
  void print(const T* const array, unsigned int _length, unsigned char opt = DEC)
  {
#if DEBUG_MODE
    _print("[" + String(array[0], opt));
    for(unsigned int i = 1; i < _length; i++)
    {
      _print(", " + String(array[i], opt), true);
    }
    _println(String("]"), true);
#endif
  }

  /**
   * @brief Print out matrix array content via serial port
   * 
   * @tparam T Content type. It must be arithmetic.
   * @param array The content
   * @param rows 
   * @param columns
   * @param opt Base
   */
  template<typename T>
  void print(const T* const array, unsigned int rows, unsigned int columns, unsigned char opt = DEC)
  {
#if DEBUG_MODE
    for (unsigned int j = 0; j < rows; j++)
    {
      _print("|" + String(array[j*columns + 0], opt));
      for(unsigned int i = 1; i < columns; i++)
        _print(" " + String(array[j*columns + i], opt), true);
      _println(String("|"), true);
    }
#endif
  }

  /**
   * @brief Print out fixed array content via serial port
   * 
   * @param array The content
   * @param _length Length of the array
   * @param dec Decimals places
   */
  void print(const fixed* const array, unsigned int _length, unsigned int dec = 4)
  {
#if DEBUG_MODE
    _print("[" + String((float)array[0], dec));
    for(unsigned int i = 1; i < _length; i++)
    {
      _print(", " + String((float)array[i], dec), true);
    }
    _println(String("]"), true);
#endif
  }

  /**
   * @brief Print out float array content via serial port
   * 
   * @param array The content
   * @param _length Length of the array
   * @param dec Decimals places
   */
  void print(const float* const array, unsigned int _length, unsigned int dec = 4)
  {
#if DEBUG_MODE
    _print("[" + String(array[0], dec));
    for(unsigned int i = 1; i < _length; i++)
    {
      _print(", " + String(array[i], dec), true);
    }
    _println(String("]"), true);
#endif
  }

  /**
   * @brief Print out float matrix array content via serial port
   * 
   * @param array The content
   * @param rows
   * @param columns
   * @param dec Decimals places
   */
  void print(const float* const array, unsigned int rows, unsigned int columns, unsigned int dec = 4)
  {
#if DEBUG_MODE
    for (unsigned int j = 0; j < rows; j++)
    {
      _print("|" + String(array[j*columns + 0], dec));
      for(unsigned int i = 1; i < columns; i++)
        _print(" " + String(array[j*columns + i], dec), true);
      _println(String("|"), true);
    }
#endif
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