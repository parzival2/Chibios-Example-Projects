#include "ch.h"
#include "hal.h"
#include "usbcfg.h"

#include "LedControl/ledControl.h"

#include "ros_lib/ros.h"
#include "std_msgs/String.h"
#include "std_msgs/UInt16.h"
#include "geometry_msgs/Vector3.h"


void led_red_cb(const std_msgs::UInt16& led_green_msg);
void led_blue_cb(const std_msgs::UInt16& led_green_msg);
void led_green_cb(const std_msgs::UInt16& led_green_msg);
void led_orange_cb(const std_msgs::UInt16& led_green_msg);


ros::NodeHandle ros_node;

ros::Subscriber<std_msgs::UInt16> led_red_sub("led/red", &led_red_cb);
ros::Subscriber<std_msgs::UInt16> led_blue_sub("led/blue", &led_blue_cb);
ros::Subscriber<std_msgs::UInt16> led_green_sub("led/green", &led_green_cb);
ros::Subscriber<std_msgs::UInt16> led_orange_sub("led/orange", &led_orange_cb);

/*
 * Callbacks
 */
void led_red_cb(const std_msgs::UInt16& led_msg)
{
    led_set(LED_RED, led_msg.data);
}

void led_blue_cb(const std_msgs::UInt16& led_msg)
{
    led_set(LED_BLUE, led_msg.data);
}

void led_green_cb(const std_msgs::UInt16& led_msg)
{
    led_set(LED_GREEN, led_msg.data);
}

void led_orange_cb(const std_msgs::UInt16& led_msg)
{
    led_set(LED_ORANGE, led_msg.data);
}

/*
 * Application entry point.
 */
int main(void)
{
    halInit();
    chSysInit();

    /*
     * Initializes a serial-over-USB CDC driver.
     */
    sduObjectInit(&SDU1);
    sduStart(&SDU1, &serusbcfg);

    /*
     * Activates the USB driver and then the USB bus pull-up on D+.
     * Note, a delay is inserted in order to not have to disconnect the cable
     * after a reset.
     */
    usbDisconnectBus(serusbcfg.usbp);
    chThdSleepMilliseconds(1000);
    usbStart(serusbcfg.usbp, &usbcfg);
    usbConnectBus(serusbcfg.usbp);

    /* ROS setup */
    ros_node.initNode();

    /* ROS subscribers */
    ros_node.subscribe(led_red_sub);
    ros_node.subscribe(led_blue_sub);
    ros_node.subscribe(led_green_sub);
    ros_node.subscribe(led_orange_sub);

    /* Setup Discovery board demo */
    led_init();

    while (true) {
        ros_node.spinOnce();
        chThdSleepMilliseconds(100);
    }
}
