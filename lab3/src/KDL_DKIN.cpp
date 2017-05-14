#include <kdl_parser/kdl_parser.hpp>
#include <ros/ros.h>
#include <geometry_msgs/PoseStamped.h>
#include <sensor_msgs/JointState.h>
#include <kdl/kdl.hpp>
#include <kdl/chain.hpp>
#include <kdl/chainfksolver.hpp>
#include <kdl/chainfksolverpos_recursive.hpp>
#include <math.h>
#include <stdlib.h>
#include <string>

KDL::Tree my_tree;
ros::Publisher publisher;
ros::Subscriber subscriber;
KDL::Chain chain;


void something(const sensor_msgs::JointState & msg)
{
	geometry_msgs::PoseStamped poseStamped;
	geometry_msgs::Point point;

	KDL::Frame frame;
	KDL::ChainFkSolverPos_recursive rec_solver = KDL::ChainFkSolverPos_recursive(chain);
	KDL::JntArray joints(chain.getNrOfJoints());

	joints(0) = msg.position[0];
    	joints(1) = msg.position[1];
    	joints(2) = msg.position[2];

    	rec_solver.JntToCart(joints, frame);
	poseStamped.header.frame_id="base_link";
	poseStamped.header.stamp = ros::Time::now();

	point.x = frame.p.data[0];
	point.x = frame.p.data[1];
	point.x = frame.p.data[2];

	poseStamped.pose.position = point;
	
	double x, y, z, w;
	frame.M.GetQuaternion(x, y, z, w);

	poseStamped.pose.orientation.x=x;
	poseStamped.pose.orientation.y=y;
	poseStamped.pose.orientation.z=z;
	poseStamped.pose.orientation.w=w;
	publisher.publish(poseStamped);
}

int main(int argc, char** argv)
{
	ros::init(argc,argv,"KDL_DKIN");
   	ros::NodeHandle node;
  	std::string robot_desc_string, dummy;
   	node.param("robot_description", robot_desc_string, dummy);
   	if (!kdl_parser::treeFromString(robot_desc_string, my_tree))
	{
      		ROS_ERROR("Failed to construct kdl tree");
      	return false;
   	}
	my_tree.getChain("base_link", "third_link", chain);
	

	publisher = node.advertise<geometry_msgs::PoseStamped>("poseStamped_kdl",1);
	subscriber = node.subscribe("joint_states",1,something);
	ros::spin();
}
