#include "hw02bushnell/move.h"
#include "ros/ros.h"
#include "geometry_msgs/Twist.h"
#include "turtlesim/Pose.h"


void move(double speed, double theta, int rate, ros::Publisher velocity_publisher){
	geometry_msgs::Twist vel_msg;

	//set intial linear x speed of turtle
	vel_msg.linear.x = speed;
	vel_msg.linear.y = 0;
	vel_msg.linear.z = 0;

	//set the angle speed
	vel_msg.angular.x = 0;
	vel_msg.angular.y = 0;
	vel_msg.angular.z = theta;

	ros::Rate loop_rate(rate);

	//Distance (r) is speed * time so we need intital time
	double t0 = ros::Time::now().toSec();
	double t1 = 0.0;
	double r = 0.0;

	do{
		velocity_publisher.publish(vel_msg);
		t1 = ros::Time::now().toSec();
		r = (t1 - t0) * speed;
		vel_msg.linear.x = r * theta;
		ros::spinOnce();
		loop_rate.sleep();
	}while(ros::ok()); //keep looping until ctrl-c is pressed


}
