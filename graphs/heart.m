t = [-2*pi:pi/72:2*pi];

Y = 13*cos(t)-5*cos(2*t)-2*cos(3*t)-cos(4*t);
X = 16*sin(t).^3;

figure(1);
%plot(X,Y,'LineWidth',2);
h = fill(X,Y,X);
h.LineWidth = 2;
h.EdgeColor = 'black';

axis equal;
ax = gca;

ax.XLim= [-20 20];
ax.Ylim= [-20 15];

xlabel('$$x=16\sin^3(t)$$','Interpreter', 'LaTeX', 'Fontsize', 14 );
ylabel ('$$13\cos(t)-5\cos(2t)-2\cos(3t)-\cos(4t)$$', 'Interpreter', 'LaTeX', 'Fontsize', 14);

xticks([-20:10:20]);
yticks([-20:5:15]);

xticklabels([]);
yticklabels([]);