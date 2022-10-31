#include <ros/ros.h>
#include <tf/transform_broadcaster.h>
#include <turtlesim/Pose.h>

std::string turtle_name;

void poseCallback(const turtlesim::PoseConstPtr& msg)
{
    static tf::TransformBroadcaster br;
    tf::Transform transform;
    /*存储位置信息*/
    transform.setOrigin(tf::Vector3(msg->x,msg->y,0.0));

    tf::Quaternion q;
    /*存储欧拉角信息*/
    q.setRPY(0,0,msg->theta);

    transform.setRotation(q);
    /*发布坐标信息，世界坐标为父坐标，乌龟为子坐标*/
    br.sendTransform(tf::StampedTransform(transform, ros::Time::now(), "world", turtle_name));
}

int main(int argc,char **argv)
{
    /*创建节点*/
    ros::init(argc, argv, "my_tf_broadcaster");
    if (argc != 2){ROS_ERROR("need turtle name as argument"); return -1;};
    /*乌龟名由输入确定，在yaml文件里面的arg里面定义了*/
    turtle_name = argv[1];
    /*创建句柄*/
    ros::NodeHandle node;
    /*创建订阅，poseCallback为回调函数*/
    ros::Subscriber sub = node.subscribe(turtle_name+"/pose", 10, &poseCallback);
    
    ros::spin();
    return 0;
 }

