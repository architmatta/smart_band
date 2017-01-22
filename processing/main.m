%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% This is the main file to run the whole process
%This file is meant to process the data and find features
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

%% Initialization
clear ; close all; clc

%% ==================== Part 1: Plot the data ====================

audiofile = '..\data\vehicle040.wav';

fprintf('Plotting the data....\n');
[time, dom_freq, amp] = print3D_audio(audiofile);

fprintf('Program paused. Press enter to continue.\n');
pause;

fprintf('Plotting the dominant frequency....\n');
scatter(dom_freq, amp);

fprintf('Program paused. Press enter to continue.\n');
pause;

%% ======================= Part 2: Chosing peaks =======================
