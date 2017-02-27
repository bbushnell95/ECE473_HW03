%Name: Brett Bushnell
%Assignment: HW02
%File: plotRosBag.m
%Description: This matlab script is made to plot the x and y position of
%the catcar over time, as well as it's cmd_vel

bagfile = rosbag('remap_turtle_rosbag.bag');

odomBag = select(bagfile, 'Topic', '/azcar_sim/odom');

odom = timeseries(odomBag, 'Pose.Pose.Position.X', 'Pose.Pose.Position.Y');

cmd_vel_safeBag = select(bagfile,'Topic','/azcar_sim/cmd_vel');

cmd_vel_safe = timeseries(cmd_vel_safeBag,'Linear.X');


%find where something interesting happens
deltadiffs = diff(odom.Data(:,2));
vindices = find(deltadiffs);
length(vindices);

interestingTime = odom.Time(vindices(1));

odomTmp = odom.Time > interestingTime;

odomIndex = find(odomTmp);

%NOW PLOT IT ALLg
figure(1)
plot(odom.Time(odomIndex(1):end),odom.Data(odomIndex(1):end,1),...
odom.Time(odomIndex(1):end),odom.Data(odomIndex(1):end,2));
%cmd_vel_safe.Time(vindices(1):end),...
%cmd_vel_safe.Time(vindices(1):end));
legend({'X position','Y position'});
title('X and Y Position Over Time: Brett Bushnell ECE473');
xlabel('Time');
ylabel('Magnitude');

figure(2)
plot(cmd_vel_safe.Time(vindices(1):end),cmd_vel_safe.Data(vindices(1):end,1));
    %cmd_vel_safe.Time(vindices(1):end));
legend('Commmand Velocity');
title('Command Velocity: Brett Bushnell ECE473');
xlabel('Time');
ylabel('Velocity');
