#include "ros/ros.h"
#include "lab4/oint_control_srv.h"
#include <iostream>

int main(int argc, char **argv)
{
  ros::init(argc, argv, "oint_client");
  ros::NodeHandle n;
  ros::ServiceClient client = n.serviceClient<lab4::oint_control_srv>("oint_control_srv");
  while(ros::ok())
  {
    lab4::oint_control_srv srv;
    float x, y, z, roll, pitch, yaw, time;
    char type;
    ROS_INFO(" X Y Z ROLL PITCH YAW CZAS TYP[l/w]");
    std::cin >> x >> y >> z >> roll >> pitch >> yaw >> time >> type;
    srv.request.x = x;
    srv.request.y = y;
    srv.request.z = z;
    srv.request.roll = roll;
    srv.request.pitch = pitch;
    srv.request.yaw = yaw;
    srv.request.time = time;
    srv.request.type = type;
    if(client.call(srv)){
      ROS_INFO("Status: %s", srv.response.status.c_str());
    }else{
      ROS_ERROR("Nie powiodlo sie.");
    }
    ros::spinOnce();
  }
  return 0;
}
