//
// Created by shivesh on 9/14/19.
//

#ifndef ARS_40X_RADAR_STATE_ROS_HPP
#define ARS_40X_RADAR_STATE_ROS_HPP

#include <ros/ros.h>
#include <std_srvs/SetBool.h>

#include <cstdint>

#include ""
#include "ars_40X/RadarStatus.h"

namespace ars_40X {
class RadarStateROS {
 public:
  RadarStateROS(ros::NodeHandle &nh, ARS_40X_CAN *ars_40X_can);// inputs include handle
  // and class ARS_40X_CAN from <ars_40X/ars_40X_can.hpp>

  ~RadarStateROS();

  void send_radar_state();

 private:
  ros::Publisher radar_state_pub_;// publish radar state

  ARS_40X_CAN *ars_40X_can_;

  radar_state::RadarState *radar_state_;
};
}

#endif //ARS_40X_RADAR_STATE_ROS_HPP
