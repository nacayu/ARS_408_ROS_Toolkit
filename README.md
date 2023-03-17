# ARS_40X_Toolkit
Our Toolkit is built based on [socket_can](https://github.com/Project-MANAS/socket_can) and you should install it first.
## Install(Installation in Chinese)
[CSDN](https://blog.csdn.net/weixin_43253464/article/details/121208924?spm=1001.2014.3001.5501)

And We refer to [ars408X technical manual](https://download.csdn.net/download/weixin_43253464/57895869?spm=1001.2014.3001.5501) to develop this repo.

## Get started

```bash
roslaunch ars_40X ars_40X.launch visualize:=true obstacle_array:=true
```

- **visualize** *(default:"true")* : Launches RViz to display the clusters/obstacles as markers.
- **obstacle_array** *(default:"false")* : Launches ars_40X_obstacle_array node which publishes obstacles as geometry_msgs/Polygon

## Publications

|Message|Type|Description|Message Box|
|---|---|---|---|
|/radar_status|ars_40X/RadarStatus|Describe the radar configuration|0x201|
|/ars_40X/clusters|ars_40X/ClusterList|Raw clusters data from radar|0x600, 0x701|
|/ars_40X/objects|ars_40X/ObjectList|Raw objects data from radar|0x60A, 0x60B, 0x60C, 0x60D|
|/visualize_clusters|visualization_msgs/MarkerArray|Clusters markers for RViz visualization| - |
|/visualize_objects|visualization_msgs/MarkerArray|Object markers for RViz visualization| - |

## Subscription

|Message|Type|Description|Message Box|
|---|---|---|---|
|/odom|nav_msgs/Odometry|Velocity and accleration information|0x300, 0x301|

## Services
|Services|
|---|
|/set_ctrl_relay_cfg|
|/set_max_distance|
|/set_output_type|
|/set_radar_power|
|/set_rcs_threshold|
|/set_send_ext_info|
|/set_send_quality|
|/set_sensor_id|
|/set_sort_index|
|/set_store_in_nvm|
|/set_filter|

