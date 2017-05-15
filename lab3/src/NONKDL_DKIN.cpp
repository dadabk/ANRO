#include <ros/ros.h>
#include <geometry_msgs/PoseStamped.h>
#include <sensor_msgs/JointState.h>
#include <math.h>
#include <stdlib.h>
#include <string>

ros::Publisher publisher;
ros::Subscriber subscriber;
double c1, c2, s1, s2;
double d3 = 1;

void something(const sensor_msgs::JointState & msg)
{
	geometry_msgs::PoseStamped poseStamped;
	geometry_msgs::Point point;

	poseStamped.header.frame_id="base_link";
	poseStamped.header.stamp = ros::Time::now();

	c1 = cos(msg.position[0]);
	c2 = cos(msg.position[1]);
        s1 = sin(msg.position[0]);
	s2 = sin(msg.position[1]);

    	point.x = 2*c1 + c1*c2 - s1*s2;
    	point.y = 2*s1 + c1*s2 + c2*s1;
	point.z = d3; 

	poseStamped.pose.position = point;

	poseStamped.pose.orientation.x=0;
	poseStamped.pose.orientation.y=0;
	poseStamped.pose.orientation.z=0;
	poseStamped.pose.orientation.w=-1;
	publisher.publish(poseStamped);
}

int main(int argc, char** argv)
{
	ros::init(argc,argv,"NONKDL_DKIN");
   	ros::NodeHandle node;
	

	publisher = node.advertise<geometry_msgs::PoseStamped>("poseStamped_nonkdl",1);
	subscriber = node.subscribe("joint_states",1,something);
	ros::spin();
}
