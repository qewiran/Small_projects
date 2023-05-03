clear; clf;
syms y x z t;

fsurf(2*x^2-3*y^2,'EdgeColor','none');

colormap spring;
hold on;

fplot3(t,sym(-2.5),2*t^2-sym(3*(2.5)^2),'LineWidth', 2, 'Color', 'black');
fplot3(sym(0),t,-3*t^2,'LineWidth', 2, 'Color', 'black');

xlabel('x');
ylabel('y');
zlabel('z');

