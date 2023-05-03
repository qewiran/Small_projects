clf;
syms y x z(x,y);
figure(1);

fc = fcontour(2*x^2+4*y^2, [-10 10 -10 10]);
title ('Линии уровня');
fc.LevelList = [0:7:140];
fc.LineWidth = 1.3;

xlim([-5 5]);
ylim([-5 5]);
colorbar;
colormap winter;