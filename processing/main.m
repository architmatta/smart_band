%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% This is the main file to run the whole process
%This file is meant to process the data and find features
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

%% Initialization
clear ; close all; clc

%% ==================== Part 1: Plot the data ====================

audiofile = '..\data\vehicle040.wav';

print3D_audio(audiofile);
fprintf('Plotting the data....\n');

fprintf('Program paused. Press enter to continue.\n');
pause;
    