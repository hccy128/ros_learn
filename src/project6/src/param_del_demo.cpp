#include <ros/ros.h>

int main(int argc, char **argv){
    ros::init(argc, argv, "param_del_node");
    ros::NodeHandle nh;

    bool iflag=ros::param::del("test_param1");
    if(iflag){
        ROS_INFO("Delete test_param1 success!");
    }

    bool iflag2=nh.deleteParam("test_param2");
    if(iflag2){
        ROS_INFO("Delete test_param2 success!");
    }
    return 0;
}