# Overview
This package is an extension of HW01. It incorporates launch files, as well as remaps parameters to have the turtle spiral work with the catcar.

## Limitations
Although succesful in having the car move, it doe's not follow the same spiral path that the turtle did. 

## Goals
The goal of this package is to meet the requirements set forth in the HW02 pdf for ECE473: Software Engineering Concepts at the University of Arizona

#Installation
To install, place this package into the catkin workspace that also has the azcar_sim package in it. Then in command prompt, change directories to the workspace. i.e. $cd nameOfDirectory
Then, run catkin_make to build the packages. i.e. $catkin_make
This will build the packages and then you are ready to go. 

## Tutorial
To run the turtleSpiral.launch follow these instructions.
	1. Follow the Installation instructions in this README.md
	2. Run the commmand $source devel/setup.bash (This ensures that the machine knows where your built files are)
	3. Type in the Command line $roslaunch hw02bushnell turtleSpiral.launch
	4. To stop the launch, click on the command prompt that has the launch file running, and press ctrl+c
	
	NOTE1: The rosbag file is named "turtleSpiral.bag". It will be located inside the package directory (i.e hw02bushnell)
	NOTE2: It is the same procedure to run parts 2 and 3, just change the name of the launch file to either remap_turtle.launch or part3.launch
	NOTE3: The rosbag file for part 2 is named "remap_turtle.bag" and is located inside the package directory
	
	
## Conclusions from Part 3
After creating my own world, I ran the az_car sim on it. However, it did not run into any of my obstacles.
This could be due to the fact that the car had spawn into the word inbetween two obstacles, so when it moved forward, it had nothing to hit.

#About
hw02bushnell is a fullfillment of HW02 for ECE473. There are three launch files in the launch folder, turtleSpiral.launch, remap_turtle.launch, and part3.launch.
These can be run using roslaunch.

#Video
https://youtu.be/V2LrLvq2f4s

#License
The BSD License

Redistribution and use in source and binary forms, with or without modification, are permitted 
provided that the following conditions are met:

* Redistributions of source code must retain the above copyright notice, this list of conditions 
  and the following disclaimer.
* Redistributions in binary form must reproduce the above copyright notice, this list of 
  conditions and the following disclaimer in the documentation and/or other materials provided 
  with the distribution.

# Authors
Brett Bushnell <bbushnell@email.arizona.edu



