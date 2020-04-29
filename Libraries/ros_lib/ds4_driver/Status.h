#ifndef _ROS_ds4_driver_Status_h
#define _ROS_ds4_driver_Status_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "std_msgs/Header.h"
#include "sensor_msgs/Imu.h"
#include "ds4_driver/Trackpad.h"

namespace ds4_driver
{

  class Status : public ros::Msg
  {
    public:
      typedef std_msgs::Header _header_type;
      _header_type header;
      typedef float _axis_left_x_type;
      _axis_left_x_type axis_left_x;
      typedef float _axis_left_y_type;
      _axis_left_y_type axis_left_y;
      typedef float _axis_right_x_type;
      _axis_right_x_type axis_right_x;
      typedef float _axis_right_y_type;
      _axis_right_y_type axis_right_y;
      typedef float _axis_l2_type;
      _axis_l2_type axis_l2;
      typedef float _axis_r2_type;
      _axis_r2_type axis_r2;
      typedef int32_t _button_dpad_up_type;
      _button_dpad_up_type button_dpad_up;
      typedef int32_t _button_dpad_down_type;
      _button_dpad_down_type button_dpad_down;
      typedef int32_t _button_dpad_left_type;
      _button_dpad_left_type button_dpad_left;
      typedef int32_t _button_dpad_right_type;
      _button_dpad_right_type button_dpad_right;
      typedef int32_t _button_cross_type;
      _button_cross_type button_cross;
      typedef int32_t _button_circle_type;
      _button_circle_type button_circle;
      typedef int32_t _button_square_type;
      _button_square_type button_square;
      typedef int32_t _button_triangle_type;
      _button_triangle_type button_triangle;
      typedef int32_t _button_l1_type;
      _button_l1_type button_l1;
      typedef int32_t _button_l2_type;
      _button_l2_type button_l2;
      typedef int32_t _button_l3_type;
      _button_l3_type button_l3;
      typedef int32_t _button_r1_type;
      _button_r1_type button_r1;
      typedef int32_t _button_r2_type;
      _button_r2_type button_r2;
      typedef int32_t _button_r3_type;
      _button_r3_type button_r3;
      typedef int32_t _button_share_type;
      _button_share_type button_share;
      typedef int32_t _button_options_type;
      _button_options_type button_options;
      typedef int32_t _button_trackpad_type;
      _button_trackpad_type button_trackpad;
      typedef int32_t _button_ps_type;
      _button_ps_type button_ps;
      typedef sensor_msgs::Imu _imu_type;
      _imu_type imu;
      typedef float _battery_percentage_type;
      _battery_percentage_type battery_percentage;
      typedef int32_t _battery_full_charging_type;
      _battery_full_charging_type battery_full_charging;
      typedef ds4_driver::Trackpad _touch0_type;
      _touch0_type touch0;
      typedef ds4_driver::Trackpad _touch1_type;
      _touch1_type touch1;
      typedef int32_t _plug_usb_type;
      _plug_usb_type plug_usb;
      typedef int32_t _plug_audio_type;
      _plug_audio_type plug_audio;
      typedef int32_t _plug_mic_type;
      _plug_mic_type plug_mic;

    Status():
      header(),
      axis_left_x(0),
      axis_left_y(0),
      axis_right_x(0),
      axis_right_y(0),
      axis_l2(0),
      axis_r2(0),
      button_dpad_up(0),
      button_dpad_down(0),
      button_dpad_left(0),
      button_dpad_right(0),
      button_cross(0),
      button_circle(0),
      button_square(0),
      button_triangle(0),
      button_l1(0),
      button_l2(0),
      button_l3(0),
      button_r1(0),
      button_r2(0),
      button_r3(0),
      button_share(0),
      button_options(0),
      button_trackpad(0),
      button_ps(0),
      imu(),
      battery_percentage(0),
      battery_full_charging(0),
      touch0(),
      touch1(),
      plug_usb(0),
      plug_audio(0),
      plug_mic(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += this->header.serialize(outbuffer + offset);
      union {
        float real;
        uint32_t base;
      } u_axis_left_x;
      u_axis_left_x.real = this->axis_left_x;
      *(outbuffer + offset + 0) = (u_axis_left_x.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_axis_left_x.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_axis_left_x.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_axis_left_x.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->axis_left_x);
      union {
        float real;
        uint32_t base;
      } u_axis_left_y;
      u_axis_left_y.real = this->axis_left_y;
      *(outbuffer + offset + 0) = (u_axis_left_y.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_axis_left_y.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_axis_left_y.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_axis_left_y.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->axis_left_y);
      union {
        float real;
        uint32_t base;
      } u_axis_right_x;
      u_axis_right_x.real = this->axis_right_x;
      *(outbuffer + offset + 0) = (u_axis_right_x.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_axis_right_x.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_axis_right_x.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_axis_right_x.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->axis_right_x);
      union {
        float real;
        uint32_t base;
      } u_axis_right_y;
      u_axis_right_y.real = this->axis_right_y;
      *(outbuffer + offset + 0) = (u_axis_right_y.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_axis_right_y.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_axis_right_y.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_axis_right_y.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->axis_right_y);
      union {
        float real;
        uint32_t base;
      } u_axis_l2;
      u_axis_l2.real = this->axis_l2;
      *(outbuffer + offset + 0) = (u_axis_l2.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_axis_l2.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_axis_l2.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_axis_l2.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->axis_l2);
      union {
        float real;
        uint32_t base;
      } u_axis_r2;
      u_axis_r2.real = this->axis_r2;
      *(outbuffer + offset + 0) = (u_axis_r2.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_axis_r2.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_axis_r2.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_axis_r2.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->axis_r2);
      union {
        int32_t real;
        uint32_t base;
      } u_button_dpad_up;
      u_button_dpad_up.real = this->button_dpad_up;
      *(outbuffer + offset + 0) = (u_button_dpad_up.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_button_dpad_up.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_button_dpad_up.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_button_dpad_up.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->button_dpad_up);
      union {
        int32_t real;
        uint32_t base;
      } u_button_dpad_down;
      u_button_dpad_down.real = this->button_dpad_down;
      *(outbuffer + offset + 0) = (u_button_dpad_down.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_button_dpad_down.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_button_dpad_down.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_button_dpad_down.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->button_dpad_down);
      union {
        int32_t real;
        uint32_t base;
      } u_button_dpad_left;
      u_button_dpad_left.real = this->button_dpad_left;
      *(outbuffer + offset + 0) = (u_button_dpad_left.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_button_dpad_left.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_button_dpad_left.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_button_dpad_left.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->button_dpad_left);
      union {
        int32_t real;
        uint32_t base;
      } u_button_dpad_right;
      u_button_dpad_right.real = this->button_dpad_right;
      *(outbuffer + offset + 0) = (u_button_dpad_right.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_button_dpad_right.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_button_dpad_right.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_button_dpad_right.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->button_dpad_right);
      union {
        int32_t real;
        uint32_t base;
      } u_button_cross;
      u_button_cross.real = this->button_cross;
      *(outbuffer + offset + 0) = (u_button_cross.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_button_cross.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_button_cross.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_button_cross.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->button_cross);
      union {
        int32_t real;
        uint32_t base;
      } u_button_circle;
      u_button_circle.real = this->button_circle;
      *(outbuffer + offset + 0) = (u_button_circle.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_button_circle.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_button_circle.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_button_circle.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->button_circle);
      union {
        int32_t real;
        uint32_t base;
      } u_button_square;
      u_button_square.real = this->button_square;
      *(outbuffer + offset + 0) = (u_button_square.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_button_square.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_button_square.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_button_square.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->button_square);
      union {
        int32_t real;
        uint32_t base;
      } u_button_triangle;
      u_button_triangle.real = this->button_triangle;
      *(outbuffer + offset + 0) = (u_button_triangle.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_button_triangle.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_button_triangle.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_button_triangle.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->button_triangle);
      union {
        int32_t real;
        uint32_t base;
      } u_button_l1;
      u_button_l1.real = this->button_l1;
      *(outbuffer + offset + 0) = (u_button_l1.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_button_l1.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_button_l1.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_button_l1.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->button_l1);
      union {
        int32_t real;
        uint32_t base;
      } u_button_l2;
      u_button_l2.real = this->button_l2;
      *(outbuffer + offset + 0) = (u_button_l2.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_button_l2.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_button_l2.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_button_l2.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->button_l2);
      union {
        int32_t real;
        uint32_t base;
      } u_button_l3;
      u_button_l3.real = this->button_l3;
      *(outbuffer + offset + 0) = (u_button_l3.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_button_l3.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_button_l3.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_button_l3.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->button_l3);
      union {
        int32_t real;
        uint32_t base;
      } u_button_r1;
      u_button_r1.real = this->button_r1;
      *(outbuffer + offset + 0) = (u_button_r1.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_button_r1.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_button_r1.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_button_r1.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->button_r1);
      union {
        int32_t real;
        uint32_t base;
      } u_button_r2;
      u_button_r2.real = this->button_r2;
      *(outbuffer + offset + 0) = (u_button_r2.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_button_r2.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_button_r2.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_button_r2.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->button_r2);
      union {
        int32_t real;
        uint32_t base;
      } u_button_r3;
      u_button_r3.real = this->button_r3;
      *(outbuffer + offset + 0) = (u_button_r3.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_button_r3.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_button_r3.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_button_r3.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->button_r3);
      union {
        int32_t real;
        uint32_t base;
      } u_button_share;
      u_button_share.real = this->button_share;
      *(outbuffer + offset + 0) = (u_button_share.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_button_share.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_button_share.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_button_share.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->button_share);
      union {
        int32_t real;
        uint32_t base;
      } u_button_options;
      u_button_options.real = this->button_options;
      *(outbuffer + offset + 0) = (u_button_options.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_button_options.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_button_options.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_button_options.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->button_options);
      union {
        int32_t real;
        uint32_t base;
      } u_button_trackpad;
      u_button_trackpad.real = this->button_trackpad;
      *(outbuffer + offset + 0) = (u_button_trackpad.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_button_trackpad.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_button_trackpad.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_button_trackpad.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->button_trackpad);
      union {
        int32_t real;
        uint32_t base;
      } u_button_ps;
      u_button_ps.real = this->button_ps;
      *(outbuffer + offset + 0) = (u_button_ps.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_button_ps.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_button_ps.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_button_ps.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->button_ps);
      offset += this->imu.serialize(outbuffer + offset);
      union {
        float real;
        uint32_t base;
      } u_battery_percentage;
      u_battery_percentage.real = this->battery_percentage;
      *(outbuffer + offset + 0) = (u_battery_percentage.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_battery_percentage.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_battery_percentage.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_battery_percentage.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->battery_percentage);
      union {
        int32_t real;
        uint32_t base;
      } u_battery_full_charging;
      u_battery_full_charging.real = this->battery_full_charging;
      *(outbuffer + offset + 0) = (u_battery_full_charging.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_battery_full_charging.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_battery_full_charging.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_battery_full_charging.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->battery_full_charging);
      offset += this->touch0.serialize(outbuffer + offset);
      offset += this->touch1.serialize(outbuffer + offset);
      union {
        int32_t real;
        uint32_t base;
      } u_plug_usb;
      u_plug_usb.real = this->plug_usb;
      *(outbuffer + offset + 0) = (u_plug_usb.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_plug_usb.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_plug_usb.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_plug_usb.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->plug_usb);
      union {
        int32_t real;
        uint32_t base;
      } u_plug_audio;
      u_plug_audio.real = this->plug_audio;
      *(outbuffer + offset + 0) = (u_plug_audio.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_plug_audio.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_plug_audio.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_plug_audio.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->plug_audio);
      union {
        int32_t real;
        uint32_t base;
      } u_plug_mic;
      u_plug_mic.real = this->plug_mic;
      *(outbuffer + offset + 0) = (u_plug_mic.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_plug_mic.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_plug_mic.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_plug_mic.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->plug_mic);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += this->header.deserialize(inbuffer + offset);
      union {
        float real;
        uint32_t base;
      } u_axis_left_x;
      u_axis_left_x.base = 0;
      u_axis_left_x.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_axis_left_x.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_axis_left_x.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_axis_left_x.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->axis_left_x = u_axis_left_x.real;
      offset += sizeof(this->axis_left_x);
      union {
        float real;
        uint32_t base;
      } u_axis_left_y;
      u_axis_left_y.base = 0;
      u_axis_left_y.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_axis_left_y.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_axis_left_y.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_axis_left_y.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->axis_left_y = u_axis_left_y.real;
      offset += sizeof(this->axis_left_y);
      union {
        float real;
        uint32_t base;
      } u_axis_right_x;
      u_axis_right_x.base = 0;
      u_axis_right_x.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_axis_right_x.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_axis_right_x.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_axis_right_x.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->axis_right_x = u_axis_right_x.real;
      offset += sizeof(this->axis_right_x);
      union {
        float real;
        uint32_t base;
      } u_axis_right_y;
      u_axis_right_y.base = 0;
      u_axis_right_y.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_axis_right_y.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_axis_right_y.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_axis_right_y.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->axis_right_y = u_axis_right_y.real;
      offset += sizeof(this->axis_right_y);
      union {
        float real;
        uint32_t base;
      } u_axis_l2;
      u_axis_l2.base = 0;
      u_axis_l2.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_axis_l2.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_axis_l2.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_axis_l2.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->axis_l2 = u_axis_l2.real;
      offset += sizeof(this->axis_l2);
      union {
        float real;
        uint32_t base;
      } u_axis_r2;
      u_axis_r2.base = 0;
      u_axis_r2.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_axis_r2.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_axis_r2.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_axis_r2.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->axis_r2 = u_axis_r2.real;
      offset += sizeof(this->axis_r2);
      union {
        int32_t real;
        uint32_t base;
      } u_button_dpad_up;
      u_button_dpad_up.base = 0;
      u_button_dpad_up.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_button_dpad_up.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_button_dpad_up.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_button_dpad_up.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->button_dpad_up = u_button_dpad_up.real;
      offset += sizeof(this->button_dpad_up);
      union {
        int32_t real;
        uint32_t base;
      } u_button_dpad_down;
      u_button_dpad_down.base = 0;
      u_button_dpad_down.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_button_dpad_down.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_button_dpad_down.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_button_dpad_down.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->button_dpad_down = u_button_dpad_down.real;
      offset += sizeof(this->button_dpad_down);
      union {
        int32_t real;
        uint32_t base;
      } u_button_dpad_left;
      u_button_dpad_left.base = 0;
      u_button_dpad_left.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_button_dpad_left.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_button_dpad_left.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_button_dpad_left.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->button_dpad_left = u_button_dpad_left.real;
      offset += sizeof(this->button_dpad_left);
      union {
        int32_t real;
        uint32_t base;
      } u_button_dpad_right;
      u_button_dpad_right.base = 0;
      u_button_dpad_right.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_button_dpad_right.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_button_dpad_right.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_button_dpad_right.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->button_dpad_right = u_button_dpad_right.real;
      offset += sizeof(this->button_dpad_right);
      union {
        int32_t real;
        uint32_t base;
      } u_button_cross;
      u_button_cross.base = 0;
      u_button_cross.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_button_cross.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_button_cross.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_button_cross.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->button_cross = u_button_cross.real;
      offset += sizeof(this->button_cross);
      union {
        int32_t real;
        uint32_t base;
      } u_button_circle;
      u_button_circle.base = 0;
      u_button_circle.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_button_circle.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_button_circle.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_button_circle.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->button_circle = u_button_circle.real;
      offset += sizeof(this->button_circle);
      union {
        int32_t real;
        uint32_t base;
      } u_button_square;
      u_button_square.base = 0;
      u_button_square.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_button_square.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_button_square.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_button_square.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->button_square = u_button_square.real;
      offset += sizeof(this->button_square);
      union {
        int32_t real;
        uint32_t base;
      } u_button_triangle;
      u_button_triangle.base = 0;
      u_button_triangle.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_button_triangle.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_button_triangle.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_button_triangle.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->button_triangle = u_button_triangle.real;
      offset += sizeof(this->button_triangle);
      union {
        int32_t real;
        uint32_t base;
      } u_button_l1;
      u_button_l1.base = 0;
      u_button_l1.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_button_l1.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_button_l1.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_button_l1.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->button_l1 = u_button_l1.real;
      offset += sizeof(this->button_l1);
      union {
        int32_t real;
        uint32_t base;
      } u_button_l2;
      u_button_l2.base = 0;
      u_button_l2.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_button_l2.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_button_l2.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_button_l2.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->button_l2 = u_button_l2.real;
      offset += sizeof(this->button_l2);
      union {
        int32_t real;
        uint32_t base;
      } u_button_l3;
      u_button_l3.base = 0;
      u_button_l3.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_button_l3.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_button_l3.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_button_l3.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->button_l3 = u_button_l3.real;
      offset += sizeof(this->button_l3);
      union {
        int32_t real;
        uint32_t base;
      } u_button_r1;
      u_button_r1.base = 0;
      u_button_r1.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_button_r1.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_button_r1.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_button_r1.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->button_r1 = u_button_r1.real;
      offset += sizeof(this->button_r1);
      union {
        int32_t real;
        uint32_t base;
      } u_button_r2;
      u_button_r2.base = 0;
      u_button_r2.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_button_r2.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_button_r2.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_button_r2.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->button_r2 = u_button_r2.real;
      offset += sizeof(this->button_r2);
      union {
        int32_t real;
        uint32_t base;
      } u_button_r3;
      u_button_r3.base = 0;
      u_button_r3.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_button_r3.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_button_r3.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_button_r3.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->button_r3 = u_button_r3.real;
      offset += sizeof(this->button_r3);
      union {
        int32_t real;
        uint32_t base;
      } u_button_share;
      u_button_share.base = 0;
      u_button_share.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_button_share.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_button_share.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_button_share.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->button_share = u_button_share.real;
      offset += sizeof(this->button_share);
      union {
        int32_t real;
        uint32_t base;
      } u_button_options;
      u_button_options.base = 0;
      u_button_options.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_button_options.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_button_options.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_button_options.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->button_options = u_button_options.real;
      offset += sizeof(this->button_options);
      union {
        int32_t real;
        uint32_t base;
      } u_button_trackpad;
      u_button_trackpad.base = 0;
      u_button_trackpad.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_button_trackpad.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_button_trackpad.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_button_trackpad.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->button_trackpad = u_button_trackpad.real;
      offset += sizeof(this->button_trackpad);
      union {
        int32_t real;
        uint32_t base;
      } u_button_ps;
      u_button_ps.base = 0;
      u_button_ps.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_button_ps.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_button_ps.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_button_ps.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->button_ps = u_button_ps.real;
      offset += sizeof(this->button_ps);
      offset += this->imu.deserialize(inbuffer + offset);
      union {
        float real;
        uint32_t base;
      } u_battery_percentage;
      u_battery_percentage.base = 0;
      u_battery_percentage.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_battery_percentage.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_battery_percentage.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_battery_percentage.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->battery_percentage = u_battery_percentage.real;
      offset += sizeof(this->battery_percentage);
      union {
        int32_t real;
        uint32_t base;
      } u_battery_full_charging;
      u_battery_full_charging.base = 0;
      u_battery_full_charging.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_battery_full_charging.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_battery_full_charging.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_battery_full_charging.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->battery_full_charging = u_battery_full_charging.real;
      offset += sizeof(this->battery_full_charging);
      offset += this->touch0.deserialize(inbuffer + offset);
      offset += this->touch1.deserialize(inbuffer + offset);
      union {
        int32_t real;
        uint32_t base;
      } u_plug_usb;
      u_plug_usb.base = 0;
      u_plug_usb.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_plug_usb.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_plug_usb.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_plug_usb.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->plug_usb = u_plug_usb.real;
      offset += sizeof(this->plug_usb);
      union {
        int32_t real;
        uint32_t base;
      } u_plug_audio;
      u_plug_audio.base = 0;
      u_plug_audio.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_plug_audio.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_plug_audio.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_plug_audio.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->plug_audio = u_plug_audio.real;
      offset += sizeof(this->plug_audio);
      union {
        int32_t real;
        uint32_t base;
      } u_plug_mic;
      u_plug_mic.base = 0;
      u_plug_mic.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_plug_mic.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_plug_mic.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_plug_mic.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->plug_mic = u_plug_mic.real;
      offset += sizeof(this->plug_mic);
     return offset;
    }

    const char * getType(){ return "ds4_driver/Status"; };
    const char * getMD5(){ return "410582f2082b7ace5412b7159665c723"; };

  };

}
#endif
