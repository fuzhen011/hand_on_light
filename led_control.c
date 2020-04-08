/***************************************************************************//**
 * @file
 * @brief Led control for managing led hardware
 *******************************************************************************
 * # License
 * <b>Copyright 2018 Silicon Laboratories Inc. www.silabs.com</b>
 *******************************************************************************
 *
 * The licensor of this software is Silicon Laboratories Inc. Your use of this
 * software is governed by the terms of Silicon Labs Master Software License
 * Agreement (MSLA) available at
 * www.silabs.com/about-us/legal/master-software-license-agreement. This
 * software is distributed to you in Source Code format and is governed by the
 * sections of the MSLA applicable to Source Code.
 *
 ******************************************************************************/

#include <math.h>

#include "led_control.h"

#include "thunderboard/board.h"

/***********************************************************************************************//**
 * @addtogroup LED
 * @{
 **************************************************************************************************/

/***********************************************************************************************//**
 * @addtogroup led_control
 * @{
 **************************************************************************************************/

/// Color representation in RGB space
typedef struct {
  uint8_t R;  ///< Red value
  uint8_t G;  ///< Green value
  uint8_t B;  ///< Blue value
}RGB_t;

/***************************************************************************//**
 * Convert temperature to RGB color using approximation functions.
 *
 * @param[in] temperature  Color temperature in Kelvins.
 *
 * @return RGB color representing given temperature.
 ******************************************************************************/
RGB_t Temperature_to_RGB(uint16_t temperature)
{
  RGB_t color;
  double temp_R, temp_G, temp_B;

  //approximation of temperature using RGB
  if (temperature < 6563) {
    temp_R = 255;
    if (temperature < 1925) {
      temp_B = 0;
    } else {
      temp_B = temperature - 1918.74282;
      temp_B = 2.55822107 * pow(temp_B, 0.546877914);
    }
    if ( temperature < 909) {
      temp_G = 0;
    } else {
      temp_G = temperature - 636.62578769;
      temp_G = 73.13384712 * log(temp_G) - 383.76244858;
    }
  } else {
    temp_R = temperature - 5882.02392431;
    temp_R = -29.28670147 * log(temp_R) + 450.50427359;
    temp_R = temp_R + 0.5;
    temp_G = temperature - 5746.13180276;
    temp_G = -18.69512921 * log(temp_G) + 377.39334366;
    temp_B = 255;
  }

  color.R = temp_R > 255 ? 255 : (temp_R >= 0 ? (int)(temp_R + 0.5) : 0);
  color.G = temp_G > 255 ? 255 : (temp_G >= 0 ? (int)(temp_G + 0.5) : 0);
  color.B = temp_B > 255 ? 255 : (temp_B >= 0 ? (int)(temp_B + 0.5) : 0);

  return color;
}

/***************************************************************************//**
 * Change lightness of given color temperature.
 *
 * @param[in] color  RGB color representing color temperature.
 * @param[in] level  Lightness level of given color.
 *
 * @return RGB color representing given temperature and lightness level.
 ******************************************************************************/
RGB_t RGB_to_LightnessRGB(RGB_t color, uint16_t level)
{
  uint32_t temp_level;
  RGB_t new_color;

  temp_level = color.R * (uint32_t) level / 65535;
  new_color.R = temp_level;
  temp_level = color.G * (uint32_t) level / 65535;
  new_color.G = temp_level;
  temp_level = color.B * (uint32_t) level / 65535;
  new_color.B = temp_level;

  return new_color;
}

/*******************************************************************************
 * Initialize LEDs hardware.
 ******************************************************************************/
void LEDS_control_init(void)
{
  // configure Thunderboard RGB LEDs
  BOARD_init();
  BOARD_rgbledEnable(true, 0x0F);
  BOARD_rgbledSetRawColor(0, 0, 0);
}

/*******************************************************************************
 * Set LED color based on lightness and temperature.
 *
 * @param[in] level        Lightness level.
 * @param[in] temperature  Color temperature in Kelvins.
 ******************************************************************************/
void LEDS_SetColor(uint16_t level, uint16_t temperature)
{
  RGB_t color = Temperature_to_RGB(temperature);
  color = RGB_to_LightnessRGB(color, level);

  BOARD_rgbledSetColor(color.R, color.G, color.B);
}

/** @} (end addtogroup led_control) */
/** @} (end addtogroup LED) */
