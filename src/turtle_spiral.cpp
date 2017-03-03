/*
 *	Name: Brett Bushnell
 *	NetID: bbushnell@email.arizona.edu
 *	Status: UnderGraduate
 *	File: hw01-video-url.txt
 *	Description: Link to video demonstration of hw01
 */



#include "ros/ros.h"
#include "geometry_msgs/Twist.h"
#include "turtlesim/Pose.h"
#include "hw02bushnell/move.h"


ros::Publisher velocity_publisher;
ros::Subscriber position_subscriber;
turtlesim::Pose turtle_position;
int flag = 0;


//move the turtle
void move(double speed, double theta, int rate);
void positionCallBack(const turtlesim::Pose::ConstPtr & currPosition);

int main(int argc, char **argv){
	double theta;
	double speed;
	double rate;
	


	//Intiate new ROS Node called turtle_spiral

	ros::init(argc, argv, "turtle_spiral");
	ros::NodeHandle n("~");

	n.param<double>("speed", speed,1.0);
	n.param("theta", theta, 5.0);
	n.param("rate", rate, 100.0);
	ros::Rate loop_rate(rate);

	velocity_publisher = n.advertise<geometry_msgs::Twist>("/turtle1/cmd_vel", 100);
	position_subscriber = n.subscribe("/turtle1/pose",10, positionCallBack);
	usleep(200000);
	usleep(200000);
	usleep(200000);
	usleep(200000);
	usleep(2000000);
	usleep(1300000);
	//usleep(200000);
	//usleep(2000000);
	//ros::spinOnce();

	//get the parameters from cmd line, else have default settings


	ROS_INFO("Speed IS: %lf", speed);
	ROS_INFO("Theta is: %lf", theta);
	ROS_INFO("The Rate is: %lf", rate);

	//usleep(2000000);
	
	move(speed, theta, rate);

	ros::spin();

		
	//ROS_INFO("Stopping Turtle!");
	return 0;

}

//makes the turtle move in a spiral (f = r(theta), where r is the distance from the start)
void move(double speed, double theta, int rate){
	geometry_msgs::Twist vel_msg;
	int initialFlag = 0;
	//ros::Rate loop_rate(rate);
	
	ros::spinOnce();

	double initialX = turtle_position.x;
	double initialY = turtle_position.y;
	//ROS_INFO("INTIALX: %lf", initialX);

	//set intial linear x speed of turtle
	vel_msg.linear.x = checkSpeed(speed);;
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
		ROS_INFO("X: %lf", turtle_position.x);
		velocity_publisher.publish(vel_msg);
		t1 = ros::Time::now().toSec();
		r = calculateR(turtle_position.x, turtle_position.y, initialX, initialY);
		vel_msg.angular.z = (r - turtle_position.theta) / 0.1;
		//vel_msg.linear.x = checkSpeed((r * theta) * 0.01);
		ros::spinOnce();
		loop_rate.sleep();
	}while(ros::ok()); //keep looping until ctrl-c is pressed


}

void positionCallBack(const turtlesim::Pose::ConstPtr & currPosition){

	turtle_position.x = currPosition->x;
	turtle_position.y = currPosition->y;
	turtle_position.theta = currPosition->theta;
}
