function FFT = myFFT1(filename1)
[Y1, Fs1] = audioread(filename1);

L1 = length(Y1);
f1 = Fs1*(0:(L1/2))/L1;

X = fft(Y1);
P2 = abs(X/L1);
P1 = P2(1:((L1/2)+1));
P1(2:end-1) = 2*P1(2:end-1);

data = 'testdata.xlsx';
A = {'frequency', 'amplitude'; f1', P1};
sheet = 1;
xlRange = 'E1';
xlswrite(data,A,sheet,xlRange);

plot(f1, P1)