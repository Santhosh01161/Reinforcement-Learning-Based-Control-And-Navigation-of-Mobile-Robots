%% Reinforcement Learning (RL) parameters
Ts = 0.025; % Agent sample time
Tf = 20;    % Simulation end time
        
% Scaling factor for RL action [-1 1]
max_speed = 1; % rad/sec

x0 = 0;
y0 = 0;
theta0 = 0;

waypoint = [0.7,0.7];