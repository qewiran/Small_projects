clear; clf;
x = [0 0.4 3.2 5.6 7.8 13.37 14.88];
y = [1 2 2.5 11 56 78 79];
plot (x, y, 'ko');

%% полиномы

p4 = polyfit(x, y, 4);
p5 = polyfit(x, y, 5);
p6 = polyfit(x, y, 6);
hold on;
t = [0:0.1:14.88];
f4 = polyval(p4, t);
f5 = polyval(p5, t);
f6 = polyval(p6, t);
pl4 = plot (t, f4);
pl4.Color = "red";
pl4.LineWidth = 2;
pl5 = plot (t, f5);
pl5.Color = "green";
pl5.LineWidth = 2;
pl6 = plot (t, f6);
pl6.Color = "magenta";
pl6.LineWidth = 2;

legend('table data', 'p4', 'p5', 'p6');

hold off;
