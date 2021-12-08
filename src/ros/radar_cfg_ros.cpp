//
// Created by shivesh on 9/14/19.
//

#include "ars_40X/ros/radar_cfg_ros.hpp"
//这里是设置ros参数的地方,从这里发布
namespace ars_40X {
//new added
// radar_filter_cfg::RadarFilterCfg(ros::NodeHandle &nh, ARS_40X_CAN * ars_40X_can):
//     ars_40X_can_(ars_40X_can){
//       radar_filter_cfg_ = ars_40X_can->get_radar_filter_cfg();//返回的是类的引用而不是指针
//   set_filter_lifetime_service_ = 
//       nh.advertiseService("set_filter_min_lifetime", &RadarCfgROS::set_filter_lifetime, this);
//     }
RadarCfgROS::RadarCfgROS(ros::NodeHandle &nh, ARS_40X_CAN *ars_40X_can) :
    ars_40X_can_(ars_40X_can) {

  radar_cfg_ = ars_40X_can->get_radar_cfg();
  radar_filter_cfg_ = ars_40X_can->get_radar_filter_cfg();//返回的是类的引用而不是指针 new added

  set_max_distance_service_ =
      nh.advertiseService("set_max_distance", &RadarCfgROS::set_max_distance, this);//第二个参数是函数
  set_sensor_id_service_ = nh.advertiseService("set_sensor_id", &RadarCfgROS::set_sensor_id, this);
  set_radar_power_service_ =
      nh.advertiseService("set_radar_power", &RadarCfgROS::set_radar_power, this);
  set_output_type_service_ =
      nh.advertiseService("set_output_type", &RadarCfgROS::set_output_type, this);
  set_send_quality_service_ =
      nh.advertiseService("set_send_quality", &RadarCfgROS::set_send_quality, this);
  set_send_ext_info_service_ =
      nh.advertiseService("set_send_ext_info", &RadarCfgROS::set_send_ext_info, this);
  set_sort_index_service_ =
      nh.advertiseService("set_sort_index", &RadarCfgROS::set_sort_index, this);
  set_ctrl_relay_cfg_service_ =
      nh.advertiseService("set_ctrl_relay_cfg", &RadarCfgROS::set_ctrl_relay_cfg, this);
  set_store_in_nvm_service_ =
      nh.advertiseService("set_store_in_nvm", &RadarCfgROS::set_store_in_nvm, this);
  set_rcs_threshold_service_ =
      nh.advertiseService("set_rcs_threshold", &RadarCfgROS::set_rcs_threshold, this);
  //new added
  set_filter_lifetime_service_ = 
      nh.advertiseService("set_filter_min_lifetime", &RadarCfgROS::set_filter_lifetime, this);
    }

}

RadarCfgROS::~RadarCfgROS() {
}
//new added
bool RadarCfgROS::set_filter_lifetime(
    RadarFilter::Request &req,
    RadarFilter::Response & /*res*/) {
  if (!radar_filter_cfg_->set_filter_min_lifetime(static_cast<uint64_t>(req.FilterLifetime))) {//修改filter的raw_data值
  }
  ars_40X_can_->send_radar_data(can_messages::FilterCfg);//传入带有帧头的数据，即在上一句raw_data值已更新得值
  return true;
}


bool RadarCfgROS::set_max_distance(
    MaxDistance::Request &req,
    MaxDistance::Response & /*res*/) {
  if (!radar_cfg_->set_max_distance(static_cast<uint64_t>(req.max_distance))) {//src文件中,radar_cfg_是之前radar_config.cpp定义的类指针，以此传入其中
    return false;
  }
  ars_40X_can_->send_radar_data(can_messages::RadarCfg);
  return true;
}

bool RadarCfgROS::set_sensor_id(
    SensorID::Request &req,
    SensorID::Response & /*res*/) {
  if (!radar_cfg_->set_sensor_id(req.sensor_id)) {
    return false;
  }
  ars_40X_can_->send_radar_data(can_messages::RadarCfg);
  return true;
}

bool RadarCfgROS::set_radar_power(
    RadarPower::Request &req,
    RadarPower::Response & /*res*/) {
  if (!radar_cfg_->set_radar_power(req.radar_power)) {
    return false;
  }
  ars_40X_can_->send_radar_data(can_messages::RadarCfg);
  return true;
}

bool RadarCfgROS::set_output_type(
    OutputType::Request &req,
    OutputType::Response & /*res*/) {
  if (!radar_cfg_->set_output_type(req.output_type)) {//获取需要更改的信息
    return false;
  }
  ars_40X_can_->send_radar_data(can_messages::RadarCfg);//发送至雷达
  return true;
}

bool RadarCfgROS::set_send_quality(
    std_srvs::SetBool::Request &req,
    std_srvs::SetBool::Response & /*res*/) {
  radar_cfg_->set_send_quality(static_cast<bool>(req.data));
  ars_40X_can_->send_radar_data(can_messages::RadarCfg);
  return true;
}

bool RadarCfgROS::set_send_ext_info(
    std_srvs::SetBool::Request &req,
    std_srvs::SetBool::Response & /*res*/) {
  radar_cfg_->set_send_ext_info(static_cast<bool>(req.data));
  ars_40X_can_->send_radar_data(can_messages::RadarCfg);
  return true;
}

bool RadarCfgROS::set_sort_index(
    SortIndex::Request &req,
    SortIndex::Response & /*res*/) {
  if (!radar_cfg_->set_sort_index(req.sort_index)) {
    return false;
  }
  ars_40X_can_->send_radar_data(can_messages::RadarCfg);
  return true;
}

bool  ::set_ctrl_relay_cfg(
    std_srvs::SetBool::Request &req,
    std_srvs::SetBool::Response & /*res*/) {
  radar_cfg_->set_ctrl_relay_cfg(static_cast<bool>(req.data));
  ars_40X_can_->send_radar_data(can_messages::RadarCfg);
  return true;
}

bool RadarCfgROS::set_store_in_nvm(
    std_srvs::SetBool::Request &req,
    std_srvs::SetBool::Response & /*res*/) {
  radar_cfg_->set_store_in_nvm(static_cast<bool>(req.data));
  ars_40X_can_->send_radar_data(can_messages::RadarCfg);
  return true;
}

bool RadarCfgROS::set_rcs_threshold(
    RCSThreshold::Request &req,
    RCSThreshold::Response & /*res*/) {
  if (!radar_cfg_->set_rcs_threshold(req.rcs_threshold)) {
    return false;
  }
  ars_40X_can_->send_radar_data(can_messages::RadarCfg);
  return true;
}

}
