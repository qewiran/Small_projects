clear; clf;

T = tiledlayout(2,3,'TileSpacing','compact','Padding','Compact');

% сердечко %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
heart = nexttile;

t = [-2*pi:pi/72:2*pi];

Y = 13*cos(t)-5*cos(2*t)-2*cos(3*t)-cos(4*t);
X = 16*sin(t).^3;


%plot(X,Y,'LineWidth',2);
h = fill(X,Y,X);
h.LineWidth = 2;
h.EdgeColor = 'black';

axis equal;
ax = gca;

ax.XLim= [-20 20];
ax.YLim= [-20 15];

ax.XTick=[-20:10:20];
ax.YTick = [-20:5:15];

ax.XTickLabel=[];
ax.YTickLabel=[];

ax.XLabel.String = '$x=16\sin^3(t)$';
ax.XLabel.Interpreter = 'latex';
ax.FontSize = 12;
ax.YLabel.String = '$13\cos(t)-5\cos(2t)-2\cos(3t)-\cos(4t)$';
ax.YLabel.Interpreter='latex';
colormap(heart, summer(10));

% пирог %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
pie_diagram = nexttile;

data1 = 0.07* ones(5,1);
data2 = 0.13* ones(5,1);
data = zeros(10,1);

data(1:2:end) = data1(1:end);
data(2:2:end) = data2(1:end);

explode = mod(data,0.07);

pie(data,explode);
colormap(pie_diagram, hot(10));

% гиперболический параболоид %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
hyp_par = nexttile;

syms y x z t;


fs =fsurf(2*x^2-3*y^2,'EdgeColor','none');
hold on;
fplot3(t,sym(-2.5),2*t^2-sym(3*(2.5)^2),'LineWidth', 2, 'Color', 'black');
fplot3(sym(0),t,-3*t^2,'LineWidth', 2, 'Color', 'black');

ax = gca;
ax.DataAspectRatio=[1 1 15];
ax.XLabel.String = 'x';
ax.YLabel.String = 'y';
ax.ZLabel.String = 'z';
colormap(hyp_par,spring);

hold off;

% bar матрицы %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
matrix = nexttile;

A = (diag([1:8])*ones(8))'-(diag([1:8])*ones(8));

bar3(abs(mod((triu(A)+triu(A)'),2))+1);
colormap(matrix, parula);

% заполнение гармонической функции %%%%%%%%%%%%%%%%%%%%%

filled = nexttile;

t=0:pi/144:6*pi;
y1=exp(-0.1.*t).*sin(t);
y2=-exp(-0.1.*t).*sin(t);

title ('$e^{-0.1t} \cdot \sin (t)$', 'Interpreter', 'latex');
hold on;

plot(t,y1,'Color','black', 'LineWidth', 3);
plot(t,y2,'Color','black', 'LineWidth', 3);
patch([t fliplr(t)], [y1 fliplr(y2)], [t fliplr(t)], 'FaceColor', 'Interp');

prop = gca;
prop.YTick = [-1:0.5:1];
prop.XTick = 0:2*pi:6*pi;
prop.XTickLabel ={'$0$','$2{\pi}$','$4\pi$','$6\pi$'};
prop.TickLabelInterpreter='latex';
prop.FontSize = 18;
prop.XLim = [0 6*pi];
prop.XGrid = 'on';
prop.YGrid = 'on';

hold off;


% линии уровня %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% 
contours = nexttile;

syms y x z(x,y);

fc = fcontour(2*x^2+4*y^2, [-10 10 -10 10]);
title ('Линии уровня');
fc.LevelList = [0:7:140];
fc.LineWidth = 1.3;

ax = gca;
ax.XLim=[-5 5];
ax.YLim=[-5 5];
ax.DataAspectRatio = [1 1 1];
colorbar;
colormap (contours,winter);




