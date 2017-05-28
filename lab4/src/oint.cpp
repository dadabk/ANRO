#include <ros/ros.h>
#include "lab4/oint_control_srv.h"
#include <geometry_msgs/PoseStamped.h>
#include <nav_msgs/Path.h>
#include <kdl/frames.hpp>
#include <iostream>

#define LOOP_RATE 10

double x, y, z, r, p, yw, old_r, old_p, old_yw, old_x, old_y, old_z;
double q_x, q_y, q_z, q_w;
unsigned int sequence = 0;
ros::Publisher publisher;
ros::Publisher path_publisher;

bool interpolation(lab4::oint_control_srv::Request  &req, lab4::oint_control_srv::Response &res)
{
	if (req.time <=0 || req.type != 'l') {
		res.status = "Zle parametry";
		return true;
	}
	
	ros::Rate loop_rate(LOOP_RATE); 
  	x = req.x;
	y = req.y;
	z = req.z;
	r = req.roll;
	p = req.pitch;
	yw = req.yaw;

	KDL::Rotation rot;

	if (req.type == 'l') {
		int steps = (int)(req.time*10); //np 20
		double dx = (x-old_x)/((double)steps);
		double dy = (y-old_y)/((double)steps);
		double dz = (z-old_z)/((double)steps);
		double dp = (p-old_p)/((double)steps);
		double dr = (r-old_r)/((double)steps);
		double dyw = (yw-old_yw)/((double)steps);		
		geometry_msgs::PoseStamped pose_stamped;
		nav_msgs::Path path;
	
		for (int i=0; i<steps; i++) {

			path.header.frame_id = "map";
			path.header.stamp = ros::Time::now();
			path.header.seq = sequence;
			pose_stamped.header.stamp = ros::Time::now();
			pose_stamped.header.frame_id = "map";
			pose_stamped.header.seq = sequence++;

			pose_stamped.pose.position.x = old_x + dx;
			pose_stamped.pose.position.y = old_y + dy;
			pose_stamped.pose.position.z = old_z + dz;

			rot = KDL::Rotation::RPY( old_r+dr, old_p+dp, old_yw+dyw);
			rot.GetQuaternion(q_x, q_y, q_z, q_w);
			pose_stamped.pose.orientation.x = q_x;
			pose_stamped.pose.orientation.y = q_y;
			pose_stamped.pose.orientation.z = q_z;
			pose_stamped.pose.orientation.w = q_w;

			old_x += dx;
			old_y += dy;
			old_z += dz;
			old_r += dr;
			old_p += dp;
			old_yw += dyw;

			path.poses.push_back(pose_stamped);
			publisher.publish(pose_stamped);
			path_publisher.publish(path);
			loop_rate.sleep();
		}
		res.status = "sukces";
		return true;
	}
}

int main(int argc, char **argv)
{
  	old_x = old_y = old_z = old_r = old_p = old_yw = 0;

  	ros::init(argc, argv, "oint_server");
  	ros::NodeHandle node;
  
  
  	publisher = node.advertise<geometry_msgs::PoseStamped>("pose",1);
	path_publisher = node.advertise<nav_msgs::Path>("path",1);

	geometry_msgs::PoseStamped pose_stamped;
	pose_stamped.header.stamp = ros::Time::now();
	pose_stamped.header.frame_id = "map";
	pose_stamped.header.seq = sequence++;
	pose_stamped.pose.position.x = 0;
	pose_stamped.pose.position.y = 0;
	pose_stamped.pose.position.z = 0;
	publisher.publish(pose_stamped);

	ros::ServiceServer service = node.advertiseService("oint_control_srv", interpolation);
  ros::spin();
  return 0;
}
