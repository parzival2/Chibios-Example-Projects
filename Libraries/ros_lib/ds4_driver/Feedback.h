#ifndef _ROS_ds4_driver_Feedback_h
#define _ROS_ds4_driver_Feedback_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace ds4_driver
{

  class Feedback : public ros::Msg
  {
    public:
      typedef bool _set_led_type;
      _set_led_type set_led;
      typedef float _led_r_type;
      _led_r_type led_r;
      typedef float _led_g_type;
      _led_g_type led_g;
      typedef float _led_b_type;
      _led_b_type led_b;
      typedef bool _set_led_flash_type;
      _set_led_flash_type set_led_flash;
      typedef float _led_flash_on_type;
      _led_flash_on_type led_flash_on;
      typedef float _led_flash_off_type;
      _led_flash_off_type led_flash_off;
      typedef bool _set_rumble_type;
      _set_rumble_type set_rumble;
      typedef float _rumble_duration_type;
      _rumble_duration_type rumble_duration;
      typedef float _rumble_small_type;
      _rumble_small_type rumble_small;
      typedef float _rumble_big_type;
      _rumble_big_type rumble_big;

    Feedback():
      set_led(0),
      led_r(0),
      led_g(0),
      led_b(0),
      set_led_flash(0),
      led_flash_on(0),
      led_flash_off(0),
      set_rumble(0),
      rumble_duration(0),
      rumble_small(0),
      rumble_big(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      union {
        bool real;
        uint8_t base;
      } u_set_led;
      u_set_led.real = this->set_led;
      *(outbuffer + offset + 0) = (u_set_led.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->set_led);
      union {
        float real;
        uint32_t base;
      } u_led_r;
      u_led_r.real = this->led_r;
      *(outbuffer + offset + 0) = (u_led_r.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_led_r.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_led_r.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_led_r.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->led_r);
      union {
        float real;
        uint32_t base;
      } u_led_g;
      u_led_g.real = this->led_g;
      *(outbuffer + offset + 0) = (u_led_g.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_led_g.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_led_g.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_led_g.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->led_g);
      union {
        float real;
        uint32_t base;
      } u_led_b;
      u_led_b.real = this->led_b;
      *(outbuffer + offset + 0) = (u_led_b.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_led_b.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_led_b.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_led_b.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->led_b);
      union {
        bool real;
        uint8_t base;
      } u_set_led_flash;
      u_set_led_flash.real = this->set_led_flash;
      *(outbuffer + offset + 0) = (u_set_led_flash.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->set_led_flash);
      union {
        float real;
        uint32_t base;
      } u_led_flash_on;
      u_led_flash_on.real = this->led_flash_on;
      *(outbuffer + offset + 0) = (u_led_flash_on.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_led_flash_on.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_led_flash_on.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_led_flash_on.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->led_flash_on);
      union {
        float real;
        uint32_t base;
      } u_led_flash_off;
      u_led_flash_off.real = this->led_flash_off;
      *(outbuffer + offset + 0) = (u_led_flash_off.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_led_flash_off.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_led_flash_off.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_led_flash_off.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->led_flash_off);
      union {
        bool real;
        uint8_t base;
      } u_set_rumble;
      u_set_rumble.real = this->set_rumble;
      *(outbuffer + offset + 0) = (u_set_rumble.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->set_rumble);
      union {
        float real;
        uint32_t base;
      } u_rumble_duration;
      u_rumble_duration.real = this->rumble_duration;
      *(outbuffer + offset + 0) = (u_rumble_duration.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_rumble_duration.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_rumble_duration.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_rumble_duration.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->rumble_duration);
      union {
        float real;
        uint32_t base;
      } u_rumble_small;
      u_rumble_small.real = this->rumble_small;
      *(outbuffer + offset + 0) = (u_rumble_small.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_rumble_small.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_rumble_small.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_rumble_small.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->rumble_small);
      union {
        float real;
        uint32_t base;
      } u_rumble_big;
      u_rumble_big.real = this->rumble_big;
      *(outbuffer + offset + 0) = (u_rumble_big.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_rumble_big.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_rumble_big.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_rumble_big.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->rumble_big);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      union {
        bool real;
        uint8_t base;
      } u_set_led;
      u_set_led.base = 0;
      u_set_led.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->set_led = u_set_led.real;
      offset += sizeof(this->set_led);
      union {
        float real;
        uint32_t base;
      } u_led_r;
      u_led_r.base = 0;
      u_led_r.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_led_r.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_led_r.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_led_r.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->led_r = u_led_r.real;
      offset += sizeof(this->led_r);
      union {
        float real;
        uint32_t base;
      } u_led_g;
      u_led_g.base = 0;
      u_led_g.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_led_g.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_led_g.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_led_g.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->led_g = u_led_g.real;
      offset += sizeof(this->led_g);
      union {
        float real;
        uint32_t base;
      } u_led_b;
      u_led_b.base = 0;
      u_led_b.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_led_b.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_led_b.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_led_b.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->led_b = u_led_b.real;
      offset += sizeof(this->led_b);
      union {
        bool real;
        uint8_t base;
      } u_set_led_flash;
      u_set_led_flash.base = 0;
      u_set_led_flash.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->set_led_flash = u_set_led_flash.real;
      offset += sizeof(this->set_led_flash);
      union {
        float real;
        uint32_t base;
      } u_led_flash_on;
      u_led_flash_on.base = 0;
      u_led_flash_on.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_led_flash_on.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_led_flash_on.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_led_flash_on.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->led_flash_on = u_led_flash_on.real;
      offset += sizeof(this->led_flash_on);
      union {
        float real;
        uint32_t base;
      } u_led_flash_off;
      u_led_flash_off.base = 0;
      u_led_flash_off.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_led_flash_off.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_led_flash_off.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_led_flash_off.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->led_flash_off = u_led_flash_off.real;
      offset += sizeof(this->led_flash_off);
      union {
        bool real;
        uint8_t base;
      } u_set_rumble;
      u_set_rumble.base = 0;
      u_set_rumble.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->set_rumble = u_set_rumble.real;
      offset += sizeof(this->set_rumble);
      union {
        float real;
        uint32_t base;
      } u_rumble_duration;
      u_rumble_duration.base = 0;
      u_rumble_duration.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_rumble_duration.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_rumble_duration.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_rumble_duration.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->rumble_duration = u_rumble_duration.real;
      offset += sizeof(this->rumble_duration);
      union {
        float real;
        uint32_t base;
      } u_rumble_small;
      u_rumble_small.base = 0;
      u_rumble_small.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_rumble_small.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_rumble_small.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_rumble_small.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->rumble_small = u_rumble_small.real;
      offset += sizeof(this->rumble_small);
      union {
        float real;
        uint32_t base;
      } u_rumble_big;
      u_rumble_big.base = 0;
      u_rumble_big.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_rumble_big.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_rumble_big.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_rumble_big.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->rumble_big = u_rumble_big.real;
      offset += sizeof(this->rumble_big);
     return offset;
    }

    const char * getType(){ return "ds4_driver/Feedback"; };
    const char * getMD5(){ return "e6ff655a0461aca2c8725df811fe5c33"; };

  };

}
#endif
