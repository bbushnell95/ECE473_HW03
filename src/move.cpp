#include "hw02bushnell/move.h"
#include <math.h>
#include "ros/ros.h"
#include "geometry_msgs/Twist.h"
#include "turtlesim/Pose.h"

/*One issue is the car flips, so I'm guessing speed is too high. Set to be constant and check if withing allowed limit*/
void move(double speed, double theta, int rate, ros::Publisher velocity_publisher, turtlesim::Pose turtle_position){
	geometry_msgs::Twist vel_msg;
	double intialX = turtle_position.x;
	double intialY = turtle_position.y;
	double aSquare = pow(turtle_position.x,2);
	double bSquare = pow(turtle_position.y,2);

	//set intial linear x speed of turtle
	vel_msg.linear.x = checkSpeed(speed); //will set the speed of the car
	vel_msg.linear.y = 0;
	vel_msg.linear.z = 0;

	//set the angle speed
	vel_msg.angular.x = 0;
	vel_msg.angular.y = 0;
	vel_msg.angular.z = 0;    //intial angle of the tire

	ros::Rate loop_rate(rate);

	//radius r  so we need intital time
	double t0 = ros::Time::now().toSec();
	double t1 = 0.0;
	double r = sqrt(aSquare + bSquare);



	do{
		velocity_publisher.publish(vel_msg);
		t1 = ros::Time::now().toSec();
		aSquare = pow(turtle_position.x,2);
		bSquare = pow(turtle_position.y,2); 
		r = sqrt(aSquare + bSquare);
		vel_msg.angular.z = r * theta;
		//vel_msg.linear.x = r * theta;
		ros::spinOnce();
		loop_rate.sleep();
	}while(ros::ok()); //keep looping until ctrl-c is pressed


}


double checkSpeed(double speed){
	if(speed > 3.0){
		ROS_INFO("Input speed exceeds max speed of 3. Setting Speed to 3");
		return 3.0; //we will set this as the max speeds
	}
	else{
		return speed;
	}
}




