X = [0:pi/36:2*pi];
X_ = X+2;
Y = sin(X);
Y_ = -2*cos(X-3.5);

figure(1);
hold on;

plot(X,Y, X_,Y_,[X;X_ ], [Y; Y_], 'Color', [0.5 0.3 0.6]);
plot(X,Y,X_,Y_, 'LineWidth', 3, 'Color', 'black');