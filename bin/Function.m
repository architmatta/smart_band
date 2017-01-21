function myFFT1(filename)
[Y1, Fs1] = audioread(filename);

L1 = length(Y1);
f1 = Fs1*(0:(L1/2))/L1;
t=[1/Fs:1/Fs:length(Y)/Fs];

X = fft(Y1);
P2 = abs(X/L1);
P1 = P2(1:((L1/2)+1));
P1(2:end-1) = 2*P1(2:end-1);

plot(f1, P1)
[pks,locs] = findpeaks(P1,f1);
