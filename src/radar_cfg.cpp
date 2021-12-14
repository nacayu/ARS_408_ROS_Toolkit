//
// Created by shivesh on 9/14/19.
//modified by naca on 11/11/2021

#include <ars_40X/radar_cfg.hpp>

namespace ars_40X {
//new added
namespace radar_filter_cfg{
  RadarFilterCfg::RadarFilterCfg(){
  //new added
  radar_filter_cfg_msg.data.FilterCfg_Min_Lifetime1 = 0;
  radar_filter_cfg_msg.data.FilterCfg_Min_Lifetime2 = 5;
  radar_filter_cfg_msg.data.FilterCfg_Max_Lifetime1 = 0;
  radar_filter_cfg_msg.data.FilterCfg_Max_Lifetime2 = 10;
  radar_filter_cfg_msg.data.FilterCfg_Type = 0;
  radar_filter_cfg_msg.data.FilterCfg_Index = 6;//life time模式
  radar_filter_cfg_msg.data.FilterCfg_Valid = 1;
  radar_filter_cfg_msg.data.FilterCfg_Active = 1;
  }
  RadarFilterCfg::~RadarFilterCfg(){

  }
  bool RadarFilterCfg::set_filter_min_lifetime(uint64_t min_life_time, bool valid){
    //TODO
    min_life_time /= 2;
    radar_filter_cfg_msg.data.FilterCfg_Min_Lifetime1 = min_life_time >> 8;//转为64位，方便进行数据发送，因为can帧的数据为64位
    radar_filter_cfg_msg.data.FilterCfg_Min_Lifetime2 = min_life_time & 0b11111111;//转为64位，方便进行数据发送，因为can帧的数据为64位
    radar_filter_cfg_msg.data.FilterCfg_Valid = static_cast<uint64_t>(valid);
    return true;
  }
  bool RadarFilterCfg::set_filter_max_lifetime(uint64_t max_life_time, bool valid){
    //TODO
    max_life_time /= 2;
    radar_filter_cfg_msg.data.FilterCfg_Max_Lifetime1 = max_life_time >> 8;//转为64位，方便进行数据发送，因为can帧的数据为64位
    radar_filter_cfg_msg.data.FilterCfg_Max_Lifetime2 = max_life_time & 0b11111111;//转为64位，方便进行数据发送，因为can帧的数据为64位
    radar_filter_cfg_msg.data.FilterCfg_Valid = static_cast<uint64_t>(valid);
    return true;
  }
  radar_filter_cfg *RadarFilterCfg::get_radar_filter_cfg() {
    return &radar_filter_cfg_msg;
  }

}
namespace radar_cfg {
RadarCfg::RadarCfg() {//对雷达设置进行初始定义,应该定义为1才能进行更改
  radar_cfg_msg.data.RadarCfg_MaxDistance_valid = 0;
  radar_cfg_msg.data.RadarCfg_SensorID_valid = 0;
  radar_cfg_msg.data.RadarCfg_RadarPower_valid = 0;
  radar_cfg_msg.data.RadarCfg_OutputType_valid = 0;
  radar_cfg_msg.data.RadarCfg_SendQuality_valid = 0;
  radar_cfg_msg.data.RadarCfg_SendExtInfo_valid = 0;
  radar_cfg_msg.data.RadarCfg_SortIndex_valid = 0;
  radar_cfg_msg.data.RadarCfg_CtrlRelay_valid = 0;
  radar_cfg_msg.data.RadarCfg_StoreInNVM_valid = 0;
  radar_cfg_msg.data.RadarCfg_RCS_Threshold_valid = 0;
}

RadarCfg::~RadarCfg() {//进行析构:无内容
}

//下面对雷达的各项参数进行设定
bool RadarCfg::set_max_distance(uint64_t distance, bool valid) {//由ros_service传入其中值
  if (distance < 90 || distance > 1000) {
    return false;
  }
  distance /= 2;
  //对最大最小距离定义完成后，还要定义valid,使其有效
  radar_cfg_msg.data.RadarCfg_MaxDistance1 = distance >> 2;//为什么右移两位:这里和maxdistance的存储位置有关
  radar_cfg_msg.data.RadarCfg_MaxDistance2 = distance & 0b11; //注意0b是二进制
  radar_cfg_msg.data.RadarCfg_MaxDistance_valid = static_cast<uint64_t>(valid);
  return true;
}

bool RadarCfg::set_sensor_id(int id, bool valid) {
  if (id < 0 || id > 7) {
    return false;
  }
  radar_cfg_msg.data.RadarCfg_SensorID = static_cast<uint64_t>(id);
  radar_cfg_msg.data.RadarCfg_SensorID_valid = static_cast<uint64_t>(valid);
  return true;
}

bool RadarCfg::set_radar_power(int power, bool valid) {
  if (power < 0 || power > 3) {
    return false;
  }
  radar_cfg_msg.data.RadarCfg_RadarPower = static_cast<uint64_t>(power);
  radar_cfg_msg.data.RadarCfg_RadarPower_valid = static_cast<uint64_t>(valid);
  return true;
}

bool RadarCfg::set_output_type(int output_type, bool valid) {
  if (output_type < 0 || output_type > 2) {
    return false;
  }
  radar_cfg_msg.data.RadarCfg_OutputType = static_cast<uint64_t>(output_type);
  radar_cfg_msg.data.RadarCfg_OutputType_valid = static_cast<uint64_t>(valid);
  return true;
}

void RadarCfg::set_send_quality(bool quality, bool valid) {
  radar_cfg_msg.data.RadarCfg_SendQuality = static_cast<uint64_t>(quality);
  radar_cfg_msg.data.RadarCfg_SendQuality_valid = static_cast<uint64_t>(valid);
}

void RadarCfg::set_send_ext_info(bool send_ext, bool valid) {
  radar_cfg_msg.data.RadarCfg_SendExtInfo = static_cast<uint64_t>(send_ext);
  radar_cfg_msg.data.RadarCfg_SendExtInfo_valid = static_cast<uint64_t>(valid);
}

bool RadarCfg::set_sort_index(int sort_index, bool valid) {
  if (sort_index < 0 || sort_index > 2) {
    return false;
  }
  radar_cfg_msg.data.RadarCfg_SortIndex = static_cast<uint64_t>(sort_index);
  radar_cfg_msg.data.RadarCfg_SortIndex_valid = static_cast<uint64_t>(valid);
  return true;
}

void RadarCfg::set_ctrl_relay_cfg(bool ctrl_relay, bool valid) {
  radar_cfg_msg.data.RadarCfg_CtrlRelay = static_cast<uint64_t>(ctrl_relay);
  radar_cfg_msg.data.RadarCfg_CtrlRelay_valid = static_cast<uint64_t>(valid);
}

void RadarCfg::set_store_in_nvm(bool store_in_nvm, bool valid) {
  radar_cfg_msg.data.RadarCfg_StoreInNVM = static_cast<uint64_t>(store_in_nvm);
  radar_cfg_msg.data.RadarCfg_StoreInNVM_valid = static_cast<uint64_t>(valid);
}

bool RadarCfg::set_rcs_threshold(int rcs_threshold, bool valid) {
  if (rcs_threshold != 0 && rcs_threshold != 1) {
    return false;
  }
  radar_cfg_msg.data.RadarCfg_RCS_Threshold = static_cast<uint64_t>(rcs_threshold);
  radar_cfg_msg.data.RadarCfg_RCS_Threshold_valid = static_cast<uint64_t>(valid);
  return true;
}

radar_cfg *RadarCfg::get_radar_cfg() {
  return &radar_cfg_msg;
}
}
}
