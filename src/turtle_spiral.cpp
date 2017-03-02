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


 
//move the turtle
void move(double speed, double theta, int rate);
void positionCallBack(const turtlesim::PoseConstPtr & currPosition);


int main(int argc, char **argv){
	double theta;
	double speed;
	double rate;


	//Intiate new ROS Node called turtle_spiral

	ros::init(argc, argv, "turtle_spiral");
	ros::NodeHandle n("~");


	//get the parameters from cmd line, else have default settings
	n.param<double>("speed", speed,3.0);
	n.param("theta", theta, 5.0);
	n.param("rate", rate, 100.0);

    /*Edit 2_9_17: Changed "/turtle1/cmd_vel" to just "cmd_vel"*/
	position_subscriber = n.subscribe("/turtle1/pose",100, positionCallBack);
	velocity_publisher = n.advertise<geometry_msgs::Twist>("/turtle1/cmd_vel", 100);


	ROS_INFO("Speed IS: %lf", speed);
	ROS_INFO("Theta is: %lf", theta);
	ROS_INFO("The Rate is: %lf", rate);

	//ROS_INFO("X: %lf", turtle_position.x);
	
	if(position_subscriber){
		move(speed, theta, rate);
	}
	ros::spin();
	
	//ROS_INFO("Stopping Turtle!");
	return 0;

}

//makes the turtle move in a spiral (f = r(theta), where r is the distance from the start)
/*void move(double speed, double theta, int rate){
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
*/

/*One issue is the car flips, so I'm guessing speed is too high. Set to be constant and check if withing allowed limit*/
void move(double speed, double theta, int rate){
	geometry_msgs::Twist vel_msg;
	double intialX = 5.544445;
	double intialY = 5.544445;
	double aSquare = pow(turtle_position.x,2);
	double bSquare = pow(turtle_position.y,2);
	double intialR = sqrt(aSquare + bSquare);
	int flag = 0;
	double newTheta = theta;


	ROS_INFO("IntialX: %lf", intialX);
	ROS_INFO("IntialY: %lf", intialY);

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
		aSquare = pow(turtle_position.x - intialX,2);
		bSquare = pow(turtle_position.y - intialY,2); 
		r = sqrt(aSquare + bSquare);
		newTheta = (r + theta) * 0.5;
		//ROS_INFO("X: %lf", turtle_position.x);
		//ROS_INFO("r: %lf", r);
		vel_msg.angular.z = newTheta;
		
		//vel_msg.linear.x = r * theta;
		ros::spinOnce();
		loop_rate.sleep();
		flag = 1;
	}while(ros::ok()); //keep looping until ctrl-c is pressed


}


void positionCallBack(const turtlesim::PoseConstPtr & currPosition){

	
	turtle_position.x = currPosition->x;
	turtle_position.y = currPosition->y;
	//ROS_INFO("X1: %lf", turtle_position.x);
}

