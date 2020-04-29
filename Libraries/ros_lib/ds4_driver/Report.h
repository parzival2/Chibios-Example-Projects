#ifndef _ROS_ds4_driver_Report_h
#define _ROS_ds4_driver_Report_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "std_msgs/Header.h"

namespace ds4_driver
{

  class Report : public ros::Msg
  {
    public:
      typedef std_msgs::Header _header_type;
      _header_type header;
      typedef uint8_t _left_analog_x_type;
      _left_analog_x_type left_analog_x;
      typedef uint8_t _left_analog_y_type;
      _left_analog_y_type left_analog_y;
      typedef uint8_t _right_analog_x_type;
      _right_analog_x_type right_analog_x;
      typedef uint8_t _right_analog_y_type;
      _right_analog_y_type right_analog_y;
      typedef uint8_t _l2_analog_type;
      _l2_analog_type l2_analog;
      typedef uint8_t _r2_analog_type;
      _r2_analog_type r2_analog;
      typedef bool _dpad_up_type;
      _dpad_up_type dpad_up;
      typedef bool _dpad_down_type;
      _dpad_down_type dpad_down;
      typedef bool _dpad_left_type;
      _dpad_left_type dpad_left;
      typedef bool _dpad_right_type;
      _dpad_right_type dpad_right;
      typedef bool _button_cross_type;
      _button_cross_type button_cross;
      typedef bool _button_circle_type;
      _button_circle_type button_circle;
      typedef bool _button_square_type;
      _button_square_type button_square;
      typedef bool _button_triangle_type;
      _button_triangle_type button_triangle;
      typedef bool _button_l1_type;
      _button_l1_type button_l1;
      typedef bool _button_l2_type;
      _button_l2_type button_l2;
      typedef bool _button_l3_type;
      _button_l3_type button_l3;
      typedef bool _button_r1_type;
      _button_r1_type button_r1;
      typedef bool _button_r2_type;
      _button_r2_type button_r2;
      typedef bool _button_r3_type;
      _button_r3_type button_r3;
      typedef bool _button_share_type;
      _button_share_type button_share;
      typedef bool _button_options_type;
      _button_options_type button_options;
      typedef bool _button_trackpad_type;
      _button_trackpad_type button_trackpad;
      typedef bool _button_ps_type;
      _button_ps_type button_ps;
      typedef int16_t _lin_acc_x_type;
      _lin_acc_x_type lin_acc_x;
      typedef int16_t _lin_acc_y_type;
      _lin_acc_y_type lin_acc_y;
      typedef int16_t _lin_acc_z_type;
      _lin_acc_z_type lin_acc_z;
      typedef int16_t _ang_vel_x_type;
      _ang_vel_x_type ang_vel_x;
      typedef int16_t _ang_vel_y_type;
      _ang_vel_y_type ang_vel_y;
      typedef int16_t _ang_vel_z_type;
      _ang_vel_z_type ang_vel_z;
      typedef uint16_t _trackpad_touch0_id_type;
      _trackpad_touch0_id_type trackpad_touch0_id;
      typedef uint16_t _trackpad_touch0_active_type;
      _trackpad_touch0_active_type trackpad_touch0_active;
      typedef uint16_t _trackpad_touch0_x_type;
      _trackpad_touch0_x_type trackpad_touch0_x;
      typedef uint16_t _trackpad_touch0_y_type;
      _trackpad_touch0_y_type trackpad_touch0_y;
      typedef uint16_t _trackpad_touch1_id_type;
      _trackpad_touch1_id_type trackpad_touch1_id;
      typedef uint16_t _trackpad_touch1_active_type;
      _trackpad_touch1_active_type trackpad_touch1_active;
      typedef uint16_t _trackpad_touch1_x_type;
      _trackpad_touch1_x_type trackpad_touch1_x;
      typedef uint16_t _trackpad_touch1_y_type;
      _trackpad_touch1_y_type trackpad_touch1_y;
      typedef uint8_t _timestamp_type;
      _timestamp_type timestamp;
      typedef uint8_t _battery_type;
      _battery_type battery;
      typedef bool _plug_usb_type;
      _plug_usb_type plug_usb;
      typedef bool _plug_audio_type;
      _plug_audio_type plug_audio;
      typedef bool _plug_mic_type;
      _plug_mic_type plug_mic;

    Report():
      header(),
      left_analog_x(0),
      left_analog_y(0),
      right_analog_x(0),
      right_analog_y(0),
      l2_analog(0),
      r2_analog(0),
      dpad_up(0),
      dpad_down(0),
      dpad_left(0),
      dpad_right(0),
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
      lin_acc_x(0),
      lin_acc_y(0),
      lin_acc_z(0),
      ang_vel_x(0),
      ang_vel_y(0),
      ang_vel_z(0),
      trackpad_touch0_id(0),
      trackpad_touch0_active(0),
      trackpad_touch0_x(0),
      trackpad_touch0_y(0),
      trackpad_touch1_id(0),
      trackpad_touch1_active(0),
      trackpad_touch1_x(0),
      trackpad_touch1_y(0),
      timestamp(0),
      battery(0),
      plug_usb(0),
      plug_audio(0),
      plug_mic(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += this->header.serialize(outbuffer + offset);
      *(outbuffer + offset + 0) = (this->left_analog_x >> (8 * 0)) & 0xFF;
      offset += sizeof(this->left_analog_x);
      *(outbuffer + offset + 0) = (this->left_analog_y >> (8 * 0)) & 0xFF;
      offset += sizeof(this->left_analog_y);
      *(outbuffer + offset + 0) = (this->right_analog_x >> (8 * 0)) & 0xFF;
      offset += sizeof(this->right_analog_x);
      *(outbuffer + offset + 0) = (this->right_analog_y >> (8 * 0)) & 0xFF;
      offset += sizeof(this->right_analog_y);
      *(outbuffer + offset + 0) = (this->l2_analog >> (8 * 0)) & 0xFF;
      offset += sizeof(this->l2_analog);
      *(outbuffer + offset + 0) = (this->r2_analog >> (8 * 0)) & 0xFF;
      offset += sizeof(this->r2_analog);
      union {
        bool real;
        uint8_t base;
      } u_dpad_up;
      u_dpad_up.real = this->dpad_up;
      *(outbuffer + offset + 0) = (u_dpad_up.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->dpad_up);
      union {
        bool real;
        uint8_t base;
      } u_dpad_down;
      u_dpad_down.real = this->dpad_down;
      *(outbuffer + offset + 0) = (u_dpad_down.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->dpad_down);
      union {
        bool real;
        uint8_t base;
      } u_dpad_left;
      u_dpad_left.real = this->dpad_left;
      *(outbuffer + offset + 0) = (u_dpad_left.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->dpad_left);
      union {
        bool real;
        uint8_t base;
      } u_dpad_right;
      u_dpad_right.real = this->dpad_right;
      *(outbuffer + offset + 0) = (u_dpad_right.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->dpad_right);
      union {
        bool real;
        uint8_t base;
      } u_button_cross;
      u_button_cross.real = this->button_cross;
      *(outbuffer + offset + 0) = (u_button_cross.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->button_cross);
      union {
        bool real;
        uint8_t base;
      } u_button_circle;
      u_button_circle.real = this->button_circle;
      *(outbuffer + offset + 0) = (u_button_circle.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->button_circle);
      union {
        bool real;
        uint8_t base;
      } u_button_square;
      u_button_square.real = this->button_square;
      *(outbuffer + offset + 0) = (u_button_square.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->button_square);
      union {
        bool real;
        uint8_t base;
      } u_button_triangle;
      u_button_triangle.real = this->button_triangle;
      *(outbuffer + offset + 0) = (u_button_triangle.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->button_triangle);
      union {
        bool real;
        uint8_t base;
      } u_button_l1;
      u_button_l1.real = this->button_l1;
      *(outbuffer + offset + 0) = (u_button_l1.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->button_l1);
      union {
        bool real;
        uint8_t base;
      } u_button_l2;
      u_button_l2.real = this->button_l2;
      *(outbuffer + offset + 0) = (u_button_l2.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->button_l2);
      union {
        bool real;
        uint8_t base;
      } u_button_l3;
      u_button_l3.real = this->button_l3;
      *(outbuffer + offset + 0) = (u_button_l3.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->button_l3);
      union {
        bool real;
        uint8_t base;
      } u_button_r1;
      u_button_r1.real = this->button_r1;
      *(outbuffer + offset + 0) = (u_button_r1.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->button_r1);
      union {
        bool real;
        uint8_t base;
      } u_button_r2;
      u_button_r2.real = this->button_r2;
      *(outbuffer + offset + 0) = (u_button_r2.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->button_r2);
      union {
        bool real;
        uint8_t base;
      } u_button_r3;
      u_button_r3.real = this->button_r3;
      *(outbuffer + offset + 0) = (u_button_r3.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->button_r3);
      union {
        bool real;
        uint8_t base;
      } u_button_share;
      u_button_share.real = this->button_share;
      *(outbuffer + offset + 0) = (u_button_share.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->button_share);
      union {
        bool real;
        uint8_t base;
      } u_button_options;
      u_button_options.real = this->button_options;
      *(outbuffer + offset + 0) = (u_button_options.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->button_options);
      union {
        bool real;
        uint8_t base;
      } u_button_trackpad;
      u_button_trackpad.real = this->button_trackpad;
      *(outbuffer + offset + 0) = (u_button_trackpad.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->button_trackpad);
      union {
        bool real;
        uint8_t base;
      } u_button_ps;
      u_button_ps.real = this->button_ps;
      *(outbuffer + offset + 0) = (u_button_ps.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->button_ps);
      union {
        int16_t real;
        uint16_t base;
      } u_lin_acc_x;
      u_lin_acc_x.real = this->lin_acc_x;
      *(outbuffer + offset + 0) = (u_lin_acc_x.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_lin_acc_x.base >> (8 * 1)) & 0xFF;
      offset += sizeof(this->lin_acc_x);
      union {
        int16_t real;
        uint16_t base;
      } u_lin_acc_y;
      u_lin_acc_y.real = this->lin_acc_y;
      *(outbuffer + offset + 0) = (u_lin_acc_y.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_lin_acc_y.base >> (8 * 1)) & 0xFF;
      offset += sizeof(this->lin_acc_y);
      union {
        int16_t real;
        uint16_t base;
      } u_lin_acc_z;
      u_lin_acc_z.real = this->lin_acc_z;
      *(outbuffer + offset + 0) = (u_lin_acc_z.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_lin_acc_z.base >> (8 * 1)) & 0xFF;
      offset += sizeof(this->lin_acc_z);
      union {
        int16_t real;
        uint16_t base;
      } u_ang_vel_x;
      u_ang_vel_x.real = this->ang_vel_x;
      *(outbuffer + offset + 0) = (u_ang_vel_x.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_ang_vel_x.base >> (8 * 1)) & 0xFF;
      offset += sizeof(this->ang_vel_x);
      union {
        int16_t real;
        uint16_t base;
      } u_ang_vel_y;
      u_ang_vel_y.real = this->ang_vel_y;
      *(outbuffer + offset + 0) = (u_ang_vel_y.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_ang_vel_y.base >> (8 * 1)) & 0xFF;
      offset += sizeof(this->ang_vel_y);
      union {
        int16_t real;
        uint16_t base;
      } u_ang_vel_z;
      u_ang_vel_z.real = this->ang_vel_z;
      *(outbuffer + offset + 0) = (u_ang_vel_z.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_ang_vel_z.base >> (8 * 1)) & 0xFF;
      offset += sizeof(this->ang_vel_z);
      *(outbuffer + offset + 0) = (this->trackpad_touch0_id >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->trackpad_touch0_id >> (8 * 1)) & 0xFF;
      offset += sizeof(this->trackpad_touch0_id);
      *(outbuffer + offset + 0) = (this->trackpad_touch0_active >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->trackpad_touch0_active >> (8 * 1)) & 0xFF;
      offset += sizeof(this->trackpad_touch0_active);
      *(outbuffer + offset + 0) = (this->trackpad_touch0_x >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->trackpad_touch0_x >> (8 * 1)) & 0xFF;
      offset += sizeof(this->trackpad_touch0_x);
      *(outbuffer + offset + 0) = (this->trackpad_touch0_y >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->trackpad_touch0_y >> (8 * 1)) & 0xFF;
      offset += sizeof(this->trackpad_touch0_y);
      *(outbuffer + offset + 0) = (this->trackpad_touch1_id >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->trackpad_touch1_id >> (8 * 1)) & 0xFF;
      offset += sizeof(this->trackpad_touch1_id);
      *(outbuffer + offset + 0) = (this->trackpad_touch1_active >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->trackpad_touch1_active >> (8 * 1)) & 0xFF;
      offset += sizeof(this->trackpad_touch1_active);
      *(outbuffer + offset + 0) = (this->trackpad_touch1_x >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->trackpad_touch1_x >> (8 * 1)) & 0xFF;
      offset += sizeof(this->trackpad_touch1_x);
      *(outbuffer + offset + 0) = (this->trackpad_touch1_y >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->trackpad_touch1_y >> (8 * 1)) & 0xFF;
      offset += sizeof(this->trackpad_touch1_y);
      *(outbuffer + offset + 0) = (this->timestamp >> (8 * 0)) & 0xFF;
      offset += sizeof(this->timestamp);
      *(outbuffer + offset + 0) = (this->battery >> (8 * 0)) & 0xFF;
      offset += sizeof(this->battery);
      union {
        bool real;
        uint8_t base;
      } u_plug_usb;
      u_plug_usb.real = this->plug_usb;
      *(outbuffer + offset + 0) = (u_plug_usb.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->plug_usb);
      union {
        bool real;
        uint8_t base;
      } u_plug_audio;
      u_plug_audio.real = this->plug_audio;
      *(outbuffer + offset + 0) = (u_plug_audio.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->plug_audio);
      union {
        bool real;
        uint8_t base;
      } u_plug_mic;
      u_plug_mic.real = this->plug_mic;
      *(outbuffer + offset + 0) = (u_plug_mic.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->plug_mic);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += this->header.deserialize(inbuffer + offset);
      this->left_analog_x =  ((uint8_t) (*(inbuffer + offset)));
      offset += sizeof(this->left_analog_x);
      this->left_analog_y =  ((uint8_t) (*(inbuffer + offset)));
      offset += sizeof(this->left_analog_y);
      this->right_analog_x =  ((uint8_t) (*(inbuffer + offset)));
      offset += sizeof(this->right_analog_x);
      this->right_analog_y =  ((uint8_t) (*(inbuffer + offset)));
      offset += sizeof(this->right_analog_y);
      this->l2_analog =  ((uint8_t) (*(inbuffer + offset)));
      offset += sizeof(this->l2_analog);
      this->r2_analog =  ((uint8_t) (*(inbuffer + offset)));
      offset += sizeof(this->r2_analog);
      union {
        bool real;
        uint8_t base;
      } u_dpad_up;
      u_dpad_up.base = 0;
      u_dpad_up.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->dpad_up = u_dpad_up.real;
      offset += sizeof(this->dpad_up);
      union {
        bool real;
        uint8_t base;
      } u_dpad_down;
      u_dpad_down.base = 0;
      u_dpad_down.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->dpad_down = u_dpad_down.real;
      offset += sizeof(this->dpad_down);
      union {
        bool real;
        uint8_t base;
      } u_dpad_left;
      u_dpad_left.base = 0;
      u_dpad_left.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->dpad_left = u_dpad_left.real;
      offset += sizeof(this->dpad_left);
      union {
        bool real;
        uint8_t base;
      } u_dpad_right;
      u_dpad_right.base = 0;
      u_dpad_right.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->dpad_right = u_dpad_right.real;
      offset += sizeof(this->dpad_right);
      union {
        bool real;
        uint8_t base;
      } u_button_cross;
      u_button_cross.base = 0;
      u_button_cross.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->button_cross = u_button_cross.real;
      offset += sizeof(this->button_cross);
      union {
        bool real;
        uint8_t base;
      } u_button_circle;
      u_button_circle.base = 0;
      u_button_circle.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->button_circle = u_button_circle.real;
      offset += sizeof(this->button_circle);
      union {
        bool real;
        uint8_t base;
      } u_button_square;
      u_button_square.base = 0;
      u_button_square.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->button_square = u_button_square.real;
      offset += sizeof(this->button_square);
      union {
        bool real;
        uint8_t base;
      } u_button_triangle;
      u_button_triangle.base = 0;
      u_button_triangle.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->button_triangle = u_button_triangle.real;
      offset += sizeof(this->button_triangle);
      union {
        bool real;
        uint8_t base;
      } u_button_l1;
      u_button_l1.base = 0;
      u_button_l1.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->button_l1 = u_button_l1.real;
      offset += sizeof(this->button_l1);
      union {
        bool real;
        uint8_t base;
      } u_button_l2;
      u_button_l2.base = 0;
      u_button_l2.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->button_l2 = u_button_l2.real;
      offset += sizeof(this->button_l2);
      union {
        bool real;
        uint8_t base;
      } u_button_l3;
      u_button_l3.base = 0;
      u_button_l3.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->button_l3 = u_button_l3.real;
      offset += sizeof(this->button_l3);
      union {
        bool real;
        uint8_t base;
      } u_button_r1;
      u_button_r1.base = 0;
      u_button_r1.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->button_r1 = u_button_r1.real;
      offset += sizeof(this->button_r1);
      union {
        bool real;
        uint8_t base;
      } u_button_r2;
      u_button_r2.base = 0;
      u_button_r2.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->button_r2 = u_button_r2.real;
      offset += sizeof(this->button_r2);
      union {
        bool real;
        uint8_t base;
      } u_button_r3;
      u_button_r3.base = 0;
      u_button_r3.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->button_r3 = u_button_r3.real;
      offset += sizeof(this->button_r3);
      union {
        bool real;
        uint8_t base;
      } u_button_share;
      u_button_share.base = 0;
      u_button_share.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->button_share = u_button_share.real;
      offset += sizeof(this->button_share);
      union {
        bool real;
        uint8_t base;
      } u_button_options;
      u_button_options.base = 0;
      u_button_options.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->button_options = u_button_options.real;
      offset += sizeof(this->button_options);
      union {
        bool real;
        uint8_t base;
      } u_button_trackpad;
      u_button_trackpad.base = 0;
      u_button_trackpad.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->button_trackpad = u_button_trackpad.real;
      offset += sizeof(this->button_trackpad);
      union {
        bool real;
        uint8_t base;
      } u_button_ps;
      u_button_ps.base = 0;
      u_button_ps.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->button_ps = u_button_ps.real;
      offset += sizeof(this->button_ps);
      union {
        int16_t real;
        uint16_t base;
      } u_lin_acc_x;
      u_lin_acc_x.base = 0;
      u_lin_acc_x.base |= ((uint16_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_lin_acc_x.base |= ((uint16_t) (*(inbuffer + offset + 1))) << (8 * 1);
      this->lin_acc_x = u_lin_acc_x.real;
      offset += sizeof(this->lin_acc_x);
      union {
        int16_t real;
        uint16_t base;
      } u_lin_acc_y;
      u_lin_acc_y.base = 0;
      u_lin_acc_y.base |= ((uint16_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_lin_acc_y.base |= ((uint16_t) (*(inbuffer + offset + 1))) << (8 * 1);
      this->lin_acc_y = u_lin_acc_y.real;
      offset += sizeof(this->lin_acc_y);
      union {
        int16_t real;
        uint16_t base;
      } u_lin_acc_z;
      u_lin_acc_z.base = 0;
      u_lin_acc_z.base |= ((uint16_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_lin_acc_z.base |= ((uint16_t) (*(inbuffer + offset + 1))) << (8 * 1);
      this->lin_acc_z = u_lin_acc_z.real;
      offset += sizeof(this->lin_acc_z);
      union {
        int16_t real;
        uint16_t base;
      } u_ang_vel_x;
      u_ang_vel_x.base = 0;
      u_ang_vel_x.base |= ((uint16_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_ang_vel_x.base |= ((uint16_t) (*(inbuffer + offset + 1))) << (8 * 1);
      this->ang_vel_x = u_ang_vel_x.real;
      offset += sizeof(this->ang_vel_x);
      union {
        int16_t real;
        uint16_t base;
      } u_ang_vel_y;
      u_ang_vel_y.base = 0;
      u_ang_vel_y.base |= ((uint16_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_ang_vel_y.base |= ((uint16_t) (*(inbuffer + offset + 1))) << (8 * 1);
      this->ang_vel_y = u_ang_vel_y.real;
      offset += sizeof(this->ang_vel_y);
      union {
        int16_t real;
        uint16_t base;
      } u_ang_vel_z;
      u_ang_vel_z.base = 0;
      u_ang_vel_z.base |= ((uint16_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_ang_vel_z.base |= ((uint16_t) (*(inbuffer + offset + 1))) << (8 * 1);
      this->ang_vel_z = u_ang_vel_z.real;
      offset += sizeof(this->ang_vel_z);
      this->trackpad_touch0_id =  ((uint16_t) (*(inbuffer + offset)));
      this->trackpad_touch0_id |= ((uint16_t) (*(inbuffer + offset + 1))) << (8 * 1);
      offset += sizeof(this->trackpad_touch0_id);
      this->trackpad_touch0_active =  ((uint16_t) (*(inbuffer + offset)));
      this->trackpad_touch0_active |= ((uint16_t) (*(inbuffer + offset + 1))) << (8 * 1);
      offset += sizeof(this->trackpad_touch0_active);
      this->trackpad_touch0_x =  ((uint16_t) (*(inbuffer + offset)));
      this->trackpad_touch0_x |= ((uint16_t) (*(inbuffer + offset + 1))) << (8 * 1);
      offset += sizeof(this->trackpad_touch0_x);
      this->trackpad_touch0_y =  ((uint16_t) (*(inbuffer + offset)));
      this->trackpad_touch0_y |= ((uint16_t) (*(inbuffer + offset + 1))) << (8 * 1);
      offset += sizeof(this->trackpad_touch0_y);
      this->trackpad_touch1_id =  ((uint16_t) (*(inbuffer + offset)));
      this->trackpad_touch1_id |= ((uint16_t) (*(inbuffer + offset + 1))) << (8 * 1);
      offset += sizeof(this->trackpad_touch1_id);
      this->trackpad_touch1_active =  ((uint16_t) (*(inbuffer + offset)));
      this->trackpad_touch1_active |= ((uint16_t) (*(inbuffer + offset + 1))) << (8 * 1);
      offset += sizeof(this->trackpad_touch1_active);
      this->trackpad_touch1_x =  ((uint16_t) (*(inbuffer + offset)));
      this->trackpad_touch1_x |= ((uint16_t) (*(inbuffer + offset + 1))) << (8 * 1);
      offset += sizeof(this->trackpad_touch1_x);
      this->trackpad_touch1_y =  ((uint16_t) (*(inbuffer + offset)));
      this->trackpad_touch1_y |= ((uint16_t) (*(inbuffer + offset + 1))) << (8 * 1);
      offset += sizeof(this->trackpad_touch1_y);
      this->timestamp =  ((uint8_t) (*(inbuffer + offset)));
      offset += sizeof(this->timestamp);
      this->battery =  ((uint8_t) (*(inbuffer + offset)));
      offset += sizeof(this->battery);
      union {
        bool real;
        uint8_t base;
      } u_plug_usb;
      u_plug_usb.base = 0;
      u_plug_usb.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->plug_usb = u_plug_usb.real;
      offset += sizeof(this->plug_usb);
      union {
        bool real;
        uint8_t base;
      } u_plug_audio;
      u_plug_audio.base = 0;
      u_plug_audio.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->plug_audio = u_plug_audio.real;
      offset += sizeof(this->plug_audio);
      union {
        bool real;
        uint8_t base;
      } u_plug_mic;
      u_plug_mic.base = 0;
      u_plug_mic.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->plug_mic = u_plug_mic.real;
      offset += sizeof(this->plug_mic);
     return offset;
    }

    const char * getType(){ return "ds4_driver/Report"; };
    const char * getMD5(){ return "ec2c37165ced5aec5b7a50d72696b7dc"; };

  };

}
#endif
