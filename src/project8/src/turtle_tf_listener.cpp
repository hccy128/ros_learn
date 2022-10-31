#include <ros/ros.h>
#include <tf/transform_listener.h>
#include <geometry_msgs/Twist.h>
#include <turtlesim/Spawn.h>

int main(int argc, char** argv)
{
    ros::init(argc,argv,"my_tf_listener");
    ros::NodeHandle node;
    /*等待服务启动*/
    ros::service::waitForService("spawn");
    /*添加小乌龟*/
    ros::ServiceClient add_turtle =node.serviceClient<turtlesim::Spawn>("spawn");
    turtlesim::Spawn srv;
    /*发布*/
    add_turtle.call(srv);
    /*注册话题发布者*/
    ros::Publisher turtle_vel =node.advertise<geometry_msgs::Twist>("turtle2/cmd_vel", 10);
    /*创建tf监听*/
     tf::TransformListener listener;
    /*10hz的频率*/
     ros::Rate rate(10.0);

     while(node.ok()){
        tf::StampedTransform transform;
        try{
            listener.waitForTransform("/turtle2", "/turtle1", ros::Time(0), ros::Duration(10.0) );
            /*获取turtle1到turtle2的tf信息，旋转矩阵，相对位置数据*/
            listener.lookupTransform("/turtle2", "/turtle1", ros::Time(0), transform);

        }catch (tf::TransformException ex) {
            ROS_ERROR("%s",ex.what());
        }
        /*定义要发布的数据类型*/
        geometry_msgs::Twist vel_msg;
        /*计算期望角度*/
        /*getOrigin是两者之间的相对位置，算出偏航角度*/
        vel_msg.angular.z = 4.0 * atan2(transform.getOrigin().y(),transform.getOrigin().x());
        /*计算期望前进速度，x方向为乌龟头的朝向*/
        vel_msg.linear.x = 0.5 * sqrt(pow(transform.getOrigin().x(), 2) +pow(transform.getOrigin().y(), 2));
        /*发布控制信息*/
        turtle_vel.publish(vel_msg);
        rate.sleep();
     }
     return 0;
}