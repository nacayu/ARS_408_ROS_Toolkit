//
// Created by shivesh on 9/13/19.
//all of data are received from this .cpp file
//

#include "ars_40X/ars_40X_can.hpp"

namespace ars_40X {
ARS_40X_CAN::ARS_40X_CAN() :
    can_("can0") {
}

ARS_40X_CAN::ARS_40X_CAN(std::string port) :
    can_(port.c_str()) {
}

ARS_40X_CAN::~ARS_40X_CAN() {
}

bool ARS_40X_CAN::receive_radar_data() {
  uint32_t frame_id;//每次通信时，can的数据都封装成帧
  uint8_t dlc;//数据的长度
  uint8_t data[8] = {0};//单次data是八个byte长度
  bool read_status = can_.read(&frame_id, &dlc, data);//传入的是指针变量，通过指针，read函数中会将读取到的数据进行赋值， 将frame_id、dlc等进行赋值
  if (!read_status) {
    return false;
  }
  // frame id indicates the type data we need e.g. radar state
  switch (frame_id) { //fram_id其实就是消息的头的种类，这个头是经过socket_can返回的，socket_can的can_.read()负责读取数据并进行解析
    case RadarState:memcpy(radar_state_.get_radar_state()->raw_data, data, dlc);
      send_radar_state();//主要进行ros的更新
      break;

    case Cluster_0_Status:memcpy(cluster_0_status_.get_cluster_0_status()->raw_data, data, dlc);//cluster_0_status不同于cluster_0_status_是一个类：包含各类状态已所含的状态，是返回的raw_data，其他同理
      send_cluster_0_status();
      break;

    case Cluster_1_General:memcpy(cluster_1_general_.get_cluster_1_general()->raw_data, data, dlc);
      send_cluster_1_general();
      break;

    case Cluster_2_Quality:memcpy(cluster_2_quality_.get_cluster_2_quality()->raw_data, data, dlc);
      send_cluster_2_quality();
      break;

    case Object_0_Status:memcpy(object_0_status_.get_object_0_status()->raw_data, data, dlc);
      send_object_0_status();
      break;

    case Object_1_General:memcpy(object_1_general_.get_object_1_general()->raw_data, data, dlc);
      send_object_1_general();
      break;

    case Object_2_Quality:memcpy(object_2_quality_.get_object_2_quality()->raw_data, data, dlc);
      send_object_2_quality();
      break;

    case Object_3_Extended:memcpy(object_3_extended_.get_object_3_extended()->raw_data, data, dlc);
      send_object_3_extended();
      break;

    default: {
#if DEBUG
      printf("Unidentified Message: %d\n", frame_id);
#endif
      break;
    }
  }
  return true;
}
// send message to radar with frame_id
bool ARS_40X_CAN::send_radar_data(uint32_t frame_id) {
  switch (frame_id) {
    case RadarCfg://要修改雷达的滤波器信息，就要从这里入手
      can_.write(frame_id, 8, radar_cfg_.get_radar_cfg()->raw_data);//这里的数字8的意思是：数据长度
      break;
    case SpeedInformation:
      can_.write(frame_id,
                 2,
                 speed_information_.get_speed_information()->raw_data);
      break;
    case YawRateInformation:
      can_.write(frame_id,
                 2,
                 yaw_rate_information_.get_yaw_rate_information()->raw_data);
      break;
      //TODO这里要加滤波器
    case FilterCfg:
    can_.write(
      frame_id,
      5,
      radar_filter_cfg_.get_radar_filter_cfg()->raw_data
    );
    break;




  
#if DEBUG
      default: printf("Frame ID not supported\n");
#endif
  }
  return true;
}
//followings return the information that read from above functions e.g.receive_radar_data
//这里返回的是类，而不是msg格式的信息，因为这些类中不仅包含msg消息，还包含这些消息对应的方法
cluster_list::Cluster_0_Status *ARS_40X_CAN::get_cluster_0_status() {
  return &cluster_0_status_;
}

cluster_list::Cluster_1_General *ARS_40X_CAN::get_cluster_1_general() {
  return &cluster_1_general_;
}

cluster_list::Cluster_2_Quality *ARS_40X_CAN::get_cluster_2_quality() {
  return &cluster_2_quality_;
}

motion_input_signals::SpeedInformation *ARS_40X_CAN::get_speed_information() {
  return &speed_information_;
}

motion_input_signals::YawRateInformation *ARS_40X_CAN::get_yaw_rate_information() {
  return &yaw_rate_information_;
}

object_list::Object_0_Status *ARS_40X_CAN::get_object_0_status() {
  return &object_0_status_;
}

object_list::Object_1_General *ARS_40X_CAN::get_object_1_general() {
  return &object_1_general_;
}

object_list::Object_2_Quality *ARS_40X_CAN::get_object_2_quality() {
  return &object_2_quality_;
}

object_list::Object_3_Extended *ARS_40X_CAN::get_object_3_extended() {
  return &object_3_extended_;
}

radar_state::RadarState *ARS_40X_CAN::get_radar_state() {
  return &radar_state_;
}

radar_cfg::RadarCfg *ARS_40X_CAN::get_radar_cfg() {
  return &radar_cfg_;
}
//new added
radar_filter_cfg::RadarFilterCfg *ARS_40X_CAN::get_radar_filter_cfg() {
  return &radar_filter_cfg_;
}
}
