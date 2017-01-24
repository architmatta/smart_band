%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% This is the main file to run the whole process
%This file is meant to process the data and find features
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

%% Initialization
clear ; close all; clc

%% ==========Part 1: Plot the data and choose peaks============

audiofile = '..\data\vehicle040.wav';

fprintf('Plotting the data....\n');
[time, max_freq, amp] = print3D_audio(audiofile);

fprintf('Program paused. Press enter to continue.\n');
pause;

fprintf('Plotting the dominant frequency....\n');
scatter(max_freq, amp);

fprintf('Program paused. Press enter to continue.\n');
pause;

%% =================== Part 2:   ===================
% sum the amp over frequency to remove repitition
amp = amp';
time = time';
mat = [max_freq, amp];
[freq,~,ind] = unique(mat(:,1));
freq_amp = [freq, abs(accumarray(ind,mat(:,2)))];

fprintf('Plotting the dominant frequency and its A value....\n');
freq_amp = sortrows(freq_amp, -2);
scatter(freq_amp(:, 1), abs(freq_amp(:, 2)));

%% ================= Part 3: Features  =============




