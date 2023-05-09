#include "ros/ros.h"
#include "tf2_ros/static_transform_broadcaster.h"
#include "geometry_msgs/TransformStamped.h"
#include "tf2/LinearMath/Quaternion.h"
/*
    发布两个坐标系之间的相对关系
    1.包含头文件
    2.初始化
    3.创建发布对象
    4.组织消息
    5.发布数据
    6.spin();

*/

int main(int argc, char *argv[]){
    ros::init(argc,argv,"static_pub");
    ros::NodeHandle nh;
    tf2_ros::StaticTransformBroadcaster pub;
    geometry_msgs::TransformStamped tfs;
    tfs.header.stamp = ros::Time::now();
    tfs.header.frame_id = "base_link";  // 相对坐标系关系中被参考的那个
    tfs.child_frame_id = "laser";
    tfs.transform.translation.x = 0.2;
    tfs.transform.translation.y = 0;
    tfs.transform.translation.z = 0.5;
    
    // 四元数需要参考欧拉角转化
    tf2::Quaternion qtn;    // 创建四元数对象
    // 在该对象设置欧垃角，以获取四元数
    qtn.setRPY(0,0,0);  // (radien)
    tfs.transform.rotation.x = qtn.getX();
    tfs.transform.rotation.y = qtn.getY();
    tfs.transform.rotation.z = qtn.getZ();
    tfs.transform.rotation.w = qtn.getW();

    pub.sendTransform(tfs);
    ros::spin();
    return 0;
}