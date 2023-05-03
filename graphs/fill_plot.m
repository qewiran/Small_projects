clf;
t=0:pi/144:6*pi;
y1=exp(-0.1.*t).*sin(t);
y2=-exp(-0.1.*t).*sin(t);

figure(1);
title ('$e^{-0.1t} \cdot \sin (t)$', 'Interpreter', 'latex');
hold on;

plot(t,y1,'Color','black', 'LineWidth', 3);
plot(t,y2,'Color','black', 'LineWidth', 3);
patch([t fliplr(t)], [y1 fliplr(y2)], 'blue');

prop = gca;
prop.XTick = 0:2*pi:6*pi;
prop.XTickLabel ={'$0$','$2{\pi}$','$4\pi$','$6\pi$'};
prop.TickLabelInterpreter='latex';
prop.FontSize = 18;
prop.XLim = [0 6*pi];

