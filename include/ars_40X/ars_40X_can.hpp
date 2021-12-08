//
// Created by shivesh on 9/13/19.
//

#ifndef ARS_40X_ARS_40X_HPP
#define ARS_40X_ARS_40X_HPP

#include <socket_can/socket_can.hpp>// a lib that is used to communicate with can

#include "ars_40X/cluster_list.hpp"
#include "ars_40X/motion_input_signals.hpp"
#include "ars_40X/object_list.hpp"
#include "ars_40X/radar_cfg.hpp"
#include "ars_40X/radar_state.hpp"

#include <cstdint>
#include <string>
#include <iostream>

namespace ars_40X {
//intitialize the status of radar
// we commenly think can_id is 0x00, so radarcfg is 0x201， 这里的变量都是关键数据
typedef enum can_messages {
  RadarCfg = 0x200,
  RadarState = 0x201,
  FilterCfg = 0x202,
  FilterState_Header = 0x203,
  FilterState_Cfg = 0x204,
  CollDetCfg = 0x400,
  CollDetRegionCfg = 0x401,
  CollDetState = 0x408,
  CollDetRegionState = 0x402,
  SpeedInformation = 0x300,
  YawRateInformation = 0x301,
  Cluster_0_Status = 0x600,//三个分别请求的是：状态，
  Cluster_1_General = 0x701,
  Cluster_2_Quality = 0x702,
  Object_0_Status = 0x60A,
  Object_1_General = 0x60B,
  Object_2_Quality = 0x60C,
  Object_3_Extended = 0x60D,
  Object_4_Warning = 0x60E,
  VersionID = 0x700,
  CollDetRelayCtrl = 0x8,
} can_messages;

class ARS_40X_CAN {// ars_40x_can not only define the status, but also defines the 
//format of radar communication
// anything after the '*' is a class that is indicated by a pointer
 public:
  ARS_40X_CAN();

  ARS_40X_CAN(std::string port);

  ~ARS_40X_CAN();

  virtual bool receive_radar_data();// receive data from can，根据帧头来判断是哪一类数据

  virtual bool send_radar_data(uint32_t frame_id); //send data to can



  //get detection in cluster mode，这些方法是不能重载的
  cluster_list::Cluster_0_Status *get_cluster_0_status();//这里函数返回cluster_0_status_

  cluster_list::Cluster_1_General *get_cluster_1_general();

  cluster_list::Cluster_2_Quality *get_cluster_2_quality();
  //get speed and yaw
  motion_input_signals::SpeedInformation *get_speed_information();

  motion_input_signals::YawRateInformation *get_yaw_rate_information();
  //get detection in object mode
  object_list::Object_0_Status *get_object_0_status();//类定义的函数，返回的是类,这个用于ros调用并返回类

  object_list::Object_1_General *get_object_1_general();

  object_list::Object_2_Quality *get_object_2_quality();

  object_list::Object_3_Extended *get_object_3_extended();
  //get radar state and configuration
  radar_state::RadarState *get_radar_state();

  radar_cfg::RadarCfg *get_radar_cfg();

  //new added
  radar_filter_cfg::RadarFilterCfg *get_radar_filter_cfg();




  virtual void send_cluster_0_status() {};

  virtual void send_cluster_1_general() {};

  virtual void send_cluster_2_quality() {};

  virtual void send_object_0_status() {};

  virtual void send_object_1_general() {};

  virtual void send_object_2_quality() {};

  virtual void send_object_3_extended() {};

  virtual void send_radar_state() {};
//这里为什么返回的是类，而前面返回的是类指针呢？？？？
/*

*/
 private:// private variable only used in ars_40x_can class
  socket_can::SocketCAN can_; // socket_can lib
  //all of followings are structure
  cluster_list::Cluster_0_Status cluster_0_status_;

  cluster_list::Cluster_1_General cluster_1_general_;

  cluster_list::Cluster_2_Quality cluster_2_quality_;

  motion_input_signals::SpeedInformation speed_information_;

  motion_input_signals::YawRateInformation yaw_rate_information_;

  object_list::Object_0_Status object_0_status_;

  object_list::Object_1_General object_1_general_;

  object_list::Object_2_Quality object_2_quality_;

  object_list::Object_3_Extended object_3_extended_;

  radar_state::RadarState radar_state_;

  radar_cfg::RadarCfg radar_cfg_;

  //new added
  radar_filter_cfg::RadarFilterCfg radar_filter_cfg_;
};
}

#endif //ARS_40X_ARS_40X_HPP
