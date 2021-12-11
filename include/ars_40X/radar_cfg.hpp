//
// Created by shivesh on 9/14/19.
//

#ifndef ARS_40X_RADAR_CFG_HPP
#define ARS_40X_RADAR_CFG_HPP

#include <algorithm>
#include <cstdint>

namespace ars_40X {// 这个命名空间内含有ars_40x开发包里面的所有的功能函数
//filter index决定了采用那种滤波模式，如filter_index = 0x1则16位开始的滤波是进行距离滤波
//filter union function
namespace radar_filter_cfg{
  typedef union radar_filter_cfg{
    struct{
      uint64_t Reserved1 : 1;
      uint64_t FilterCfg_Valid : 1;
      uint64_t FilterCfg_Active : 1; 
      uint64_t FilterCfg_Index : 4; 
      uint64_t FilterCfg_Type : 1;
      uint64_t FilterCfg_Min_Lifetime1 : 4;
      uint64_t Reserved2 : 4;
      uint64_t FilterCfg_Min_Lifetime2 : 8;
      uint64_t Filter_Max_Lifetime1 : 4;
      uint64_t Reserved3 : 4;
      uint64_t FilterCfg_Max_Lifetime2 : 8;
    } data = {};
    uint8_t raw_data[5];
  }radar_filter_cfg;

  class RadarFilterCfg{
    public:
    RadarFilterCfg();

    ~RadarFilterCfg();
    //todo
    //bool set_filter_max_lifetime(uint64_t min_life_time, bool valid = true);

    bool set_filter_min_lifetime(uint64_t max_life_time, bool valid = true);

    //bool set_filter_filtercfg_type(uint64_t filter_type, bool valid = true);
    
    radar_filter_cfg *get_radar_filter_cfg();

    private:
    radar_filter_cfg radar_filter_cfg_msg; // this variable will be used for message definition

  };

}



namespace radar_cfg {
typedef union radar_cfg {//所有雷达参数的设置都在这里，其中valid结尾的是表明更改是否有效
  struct {
    //按照位数来赋值
    uint64_t RadarCfg_MaxDistance_valid:1;
    uint64_t RadarCfg_SensorID_valid:1;
    uint64_t RadarCfg_RadarPower_valid:1;
    uint64_t RadarCfg_OutputType_valid:1;
    uint64_t RadarCfg_SendQuality_valid:1;
    uint64_t RadarCfg_SendExtInfo_valid:1;
    uint64_t RadarCfg_SortIndex_valid:1;
    uint64_t RadarCfg_StoreInNVM_valid:1;
    uint64_t RadarCfg_MaxDistance1:8;//设置最大最小距离
    uint64_t Reserved:6;
    uint64_t RadarCfg_MaxDistance2:2;
    uint64_t Reserved2:8;
    uint64_t RadarCfg_SensorID:3;
    uint64_t RadarCfg_OutputType:2;
    uint64_t RadarCfg_RadarPower:3;
    uint64_t RadarCfg_CtrlRelay_valid:1;
    uint64_t RadarCfg_CtrlRelay:1;
    uint64_t RadarCfg_SendQuality:1;
    uint64_t RadarCfg_SendExtInfo:1;
    uint64_t RadarCfg_SortIndex:3;
    uint64_t RadarCfg_StoreInNVM:1;//这个设置是否永久保存上次的雷达设置，如果为1则为是
    uint64_t RadarCfg_RCS_Threshold_valid:1;
    uint64_t RadarCfg_RCS_Threshold:3;

    uint64_t Reserved3:4;
    uint64_t Reserved4:8;

  } data = {};// {} is null indicate that radar_cfg data is set to null when initialization

  uint8_t raw_data[8];
} radar_cfg;
/* 
这个union体，初始化为空，后面会根据需要进行初始化
雷达的配置帧格式：8 * 8 bit，也就是每个byte会有八位的功能位，同时每个项目都有一个byte
发送格式为：先发送帧头，告知雷达要发送的内容类型：例如配置信息，然后发送一个8 * 8 bit的数据即可，其中数据要按照雷达的格式要求来发送，
发送的数据不仅要注意位数限制，还要注意真实情况下的限制
*/

class RadarCfg {//all of those function (e.g. set_max_distance()) is used to set radar's 
// status
 public:
  RadarCfg();

  ~RadarCfg();
//在默认下，valid默认设置为true
  bool set_max_distance(uint64_t distance, bool valid = true);

  bool set_sensor_id(int id, bool valid = true);

  bool set_radar_power(int power, bool valid = true);

  bool set_output_type(int output_type, bool valid = true);

  void set_send_quality(bool quality, bool valid = true);

  void set_send_ext_info(bool send_ext, bool valid = true);

  bool set_sort_index(int sort_index, bool valid = true);

  void set_ctrl_relay_cfg(bool ctrl_relay, bool valid = true);

  void set_store_in_nvm(bool store_in_nvm, bool valid = true);

  bool set_rcs_threshold(int rcs_threshold, bool valid = true);


  radar_cfg *get_radar_cfg();

 private:
  radar_cfg radar_cfg_msg; // this variable will be used for message definition
};
}
}

#endif //ARS_40X_RADAR_CFG_HPP
