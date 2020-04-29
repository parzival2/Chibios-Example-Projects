#ifndef _ROS_ds4_driver_Trackpad_h
#define _ROS_ds4_driver_Trackpad_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace ds4_driver
{

  class Trackpad : public ros::Msg
  {
    public:
      typedef uint16_t _id_type;
      _id_type id;
      typedef int32_t _active_type;
      _active_type active;
      typedef float _x_type;
      _x_type x;
      typedef float _y_type;
      _y_type y;

    Trackpad():
      id(0),
      active(0),
      x(0),
      y(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      *(outbuffer + offset + 0) = (this->id >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->id >> (8 * 1)) & 0xFF;
      offset += sizeof(this->id);
      union {
        int32_t real;
        uint32_t base;
      } u_active;
      u_active.real = this->active;
      *(outbuffer + offset + 0) = (u_active.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_active.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_active.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_active.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->active);
      union {
        float real;
        uint32_t base;
      } u_x;
      u_x.real = this->x;
      *(outbuffer + offset + 0) = (u_x.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_x.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_x.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_x.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->x);
      union {
        float real;
        uint32_t base;
      } u_y;
      u_y.real = this->y;
      *(outbuffer + offset + 0) = (u_y.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_y.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_y.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_y.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->y);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      this->id =  ((uint16_t) (*(inbuffer + offset)));
      this->id |= ((uint16_t) (*(inbuffer + offset + 1))) << (8 * 1);
      offset += sizeof(this->id);
      union {
        int32_t real;
        uint32_t base;
      } u_active;
      u_active.base = 0;
      u_active.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_active.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_active.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_active.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->active = u_active.real;
      offset += sizeof(this->active);
      union {
        float real;
        uint32_t base;
      } u_x;
      u_x.base = 0;
      u_x.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_x.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_x.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_x.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->x = u_x.real;
      offset += sizeof(this->x);
      union {
        float real;
        uint32_t base;
      } u_y;
      u_y.base = 0;
      u_y.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_y.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_y.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_y.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->y = u_y.real;
      offset += sizeof(this->y);
     return offset;
    }

    const char * getType(){ return "ds4_driver/Trackpad"; };
    const char * getMD5(){ return "7f8d46ab2334dfb3664bed321f9eaf05"; };

  };

}
#endif
