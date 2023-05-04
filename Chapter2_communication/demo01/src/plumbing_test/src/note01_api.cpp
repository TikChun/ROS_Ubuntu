/*
    This is not a functioning code, won;t be compiled
    Just for documentation on some roscpp api
*/
#include "ros/ros.h"
#include "std_msgs/String.h"

void cb(const ros::TimerEvent& event){
    ROS_INFO("-------------");
    ROS_INFO("Calledd in %.2f",event.current_real.toSec()); //  event发生的时间
}

int main(int argc, char *argv[])
{
    ros::init(argc,argv,"note");
    // void     初始化 ROS 节点
    //  参数：
    //      1. argc:    参数个数
    //      2. argv:    参数数组
    //      3. name:    为节点命名，需保证唯一性
    //      4. option:  启动选项
    //  使用：
    //      argc，argv  若按照特定格式，则ROS可以加以使用. Ex: 设置全局，重命名节点......
    //      option      节点名词需要唯一性 -> 同一个节点不能重复启动（之前启动的会被关闭）
    //                  若需要一个节点多次启动： ros::init_options::AnonymousName                    

    ros::NodeHandle nh;

    ros::Publisher pub = nh.advertise<std_msgs::String>("NoteBook",10);
    // 作用：   创建发布者对象
    // 模板：   被发布的消息的类型
    // 参数：   
    //          1. 话题名称
    //          2. 队列长度
    //          3. latch(optional)：    if true: 保存发布方的最后一条消息，并且当新的订阅对象连接到发布方时，将这则消息发给订阅者
    //                                  例子：发布静态地图：设置latch为true，且发布方只发送一次信息；每当订阅者连接时，将地图发送给订阅者(只发送一次)【效率up】
    std_msgs::String msg;
    ros::Rate rate(10); //10hz
    int count = 0; //index
    
    //  时间相关
    //  需要NodeHandle
    ros::Time current_time = ros::Time::now();  //  获取当前时间: 参考系: 1970/1/1 00:00:00 UTC
    double sec_time = current_time.toSec();     //  距1970年的时间，以秒为单位

    ros::Time t1(20,30);                        //  设置时间，据1970年20 sec, 30 nsec
    ros::Time t2(20.30);                        //  same as above

    ros::Duration du(4.5);                      //  持续时间，时长4.5秒
    du.sleep();                                 //  休眠4.5秒

    //  时间的运算
    ros::Time begin = ros::Time::now();         //  开始时刻
    ros::Duration du1(5);                       //  持续时间
    ros::Time stop = begin + du1;               //  计算结束时刻 = 开始时刻 + 持续时间

    //  定时器
    ros::Timer timer = nh.createTimer(ros::Duration(1),cb);
    /*
        ros::Timer createTimer(ros::Duration period,            //  时间间隔
                            const ros::TimerCallback &callback, //  回调函数，封装业务
                            bool oneshot = false，              //  是否一次性
                            bool autostart = true)              //  自动启动
        //  oneshot:    只执行一次
        //  autostart:  在timer.start();                        //  当设置为false时需要手动启动
    */
    //  ros::spin();    //  定时器启动后需要回旋
    while(ros::ok())
    {
        //  如果计数器>=50, 关闭节点
        if(count >= 50)
        {
            ros::shutdown();    //  关闭节点
        }

        //  日志
        ROS_DEBUG("debug msg"); //  不会打印在终端
        ROS_INFO("normal info");//  白色
        ROS_WARN("warning");    //  黄色
        ROS_ERROR("error");     //  红色
        ROS_FATAL("fatal");     //  红色

        count ++;
        std::stringstream ss;
        ss << "hello --->" <<count;
        msg.data = ss.str();


        pub.publish(msg);
        ROS_INFO("publish info: %s", ss.str().c_str());
        rate.sleep();
        ros::spinOnce();    // 一轮call back之后继续执行下面的code
        //ros::spin();      // 在call back中无限循环
        
    }

    return 0;
}