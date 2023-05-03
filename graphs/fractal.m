clf;
prompt = 'введите глубину рекурсии:';
n = input(prompt)
figure(1);
t = [0:pi / 36:pi];
p = plot(cos(t), sin(t));
hold on;
axis equal;
ax = gca;
funCircle(1, 0, n);
