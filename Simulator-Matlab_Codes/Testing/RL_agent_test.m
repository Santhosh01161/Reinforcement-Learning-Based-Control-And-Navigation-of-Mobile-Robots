clc
clear
close all

%%
load('RomiDDPG-2.mat')

parameters

actor = getActor(agent);
learned_params = actor.getLearnableParameters();
w3 = learned_params{1,5};
w2 = learned_params{1,3};
w1 = learned_params{1,1};
b1 = learned_params{1,2};
b2 = learned_params{1,4};
b3 = learned_params{1,6};

%% Network Test

inp = [-0.0104, -0.0237, 0.953, 0, 0, 0, 0, 0];
h1 = w1 * inp' + b1;
h1 = h1 .* (h1 > 0);
h2 = w2 * h1 + b2;
h2 = h2 .* (h2 > 0);
vel = tanh(w3 * h2 + b3);

act = getAction(agent,{inp});
