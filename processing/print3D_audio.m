function print = print3D_audio(audiofile)
%Y is sampled data and Fs is sample rate
[Y, Fs] = audioread(audiofile, 'double');

L = length(Y);
f1 = Fs*(0:(L/2))/L;

nfft = 150;
noverlap=nfft/2;
wnd= hamming(nfft,'periodic');
[S, F, T, P] = spectrogram (Y, wnd, noverlap, nfft, Fs);

mesh(T,F,10*log10(abs(P)));