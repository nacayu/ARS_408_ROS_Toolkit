//
// Created by shivesh on 9/13/19.
//

#include "ars_40X/ros/ars_40X_ros.hpp"

namespace ars_40X {
ARS_40X_ROS::ARS_40X_ROS(ros::NodeHandle &nh) :
//初始化一系列变量，对hpp初始化的各个类进行参数传入，传入的是ARS_40X_ROS的类指针this以及ros句柄nh_
//这个地方定义全局的类变量，这些类都是继承自前面的各个类
    nh_(nh),
    cluster_list_ros_(nh_, this),
    motion_input_signals_ros_(nh_, this),
    object_list_ros_(nh_, this),
    radar_cfg_ros_(nh_, this),//这里进行雷达配置的初始化工作
    radar_state_ros_(nh_, this) 
{
  ros::NodeHandle private_nh("~");
  std::string frame_id;
  private_nh.param<std::string>("frame_id", frame_id, std::string("radar"));//名字为frame_id的参数值赋给中间的frame_id变量，没有参数时默认为"radar"字符串
  cluster_list_ros_.set_frame_id(frame_id);
  object_list_ros_.set_frame_id(frame_id);
}

ARS_40X_ROS::~ARS_40X_ROS() {
}

void ARS_40X_ROS::receive_data() {
  while (ros::ok()) {
    receive_radar_data();
  }
}
//这里的send不是向雷达发送，而是发布topic公布出来
void ARS_40X_ROS::send_cluster_0_status() {
  cluster_list_ros_.send_cluster_0_status();
}

void ARS_40X_ROS::send_cluster_1_general() {
  cluster_list_ros_.send_cluster_1_general();
}

void ARS_40X_ROS::send_cluster_2_quality() {
  cluster_list_ros_.send_cluster_2_quality();
}

void ARS_40X_ROS::send_object_0_status() {
  object_list_ros_.send_object_0_status();
}

void ARS_40X_ROS::send_object_1_general() {
  object_list_ros_.send_object_1_general();
}

void ARS_40X_ROS::send_object_2_quality() {
  object_list_ros_.send_object_2_quality();
}

void ARS_40X_ROS::send_object_3_extended() {
  object_list_ros_.send_object_3_extended();
}

void ARS_40X_ROS::send_radar_state() {
  radar_state_ros_.send_radar_state();
}

void ARS_40X_ROS::run() {
  receive_data_thread_ = std::thread(std::bind(&ARS_40X_ROS::receive_data, this));
  receive_data_thread_.detach();//将线程与调用的线程分离，获取数据的子任务独立执行
}
}

int main(int argc, char **argv) {
  ros::init(argc, argv, "ars_40X_ros");
  ros::NodeHandle nh;
  ars_40X::ARS_40X_ROS ars_40X_ros_(nh);
  ars_40X_ros_.run();
  ROS_INFO("start");
  ros::spin();//卡在这里，receive_data的线程一直执行
}
