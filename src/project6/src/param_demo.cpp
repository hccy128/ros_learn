#include <ros/ros.h>
int main(int argc, char **argv){

ros::init(argc, argv, "param_node");
ros::NodeHandle nh;

    //ros::param::set()
ros::param::set("/turtlesim/background_r",100);
ros::param::set("/turtlesim/background_g",255);
ros::param::set("/turtlesim/background_b",45);
ros::param::set("test_param1",11);
ros::param::set("test_param2",12);

    //ros::NodeHandle::getParam()
    /*
    nh.setParam("/turtlesim/background_r",255);
    nh.setParam("/turtlesim/background_g",255);
    nh.setParam("/turtlesim/background_b",255);
    */

    return 0;
}
