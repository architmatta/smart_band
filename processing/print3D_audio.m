function print = print3D_audio(audiofile)
%Y is sampled data and Fs is sample rate
[Y, Fs] = audioread(audiofile, 'double');

L = length(Y);
f1 = Fs*(0:(L/2))/L;

nfft = 150;
noverlap=nfft/2;
wnd= hamming(nfft,'periodic');
[S, F, T, P] = spectrogram (Y, wnd, noverlap, nfft, Fs);
%P is spectral density of signal
E = 10*log10(abs(P));
mesh(T,F,E);

%max of E over F at given T
