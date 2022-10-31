#include <ros/ros.h>

int main(int argc, char **argv){
ros::init(argc, argv, "param_get_node");
ros::NodeHandle nh;

int parameter1, parameter2, parameter3, parameter4;

bool  iflag1=ros::param::get("/turtlesim/background_b",parameter1);

bool ifget2 = nh.getParam("/turtlesim/background_g", parameter2);

bool ifget3 = nh.param("/turtlesim/background_r", parameter3,999);

bool ifget4 = nh.param("color", parameter4,999);

ROS_INFO("param:%d,%d,%d,%d",parameter1,parameter2,parameter3,parameter4);

return 0;

}