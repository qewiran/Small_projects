f = @(x) 5/2.*cos(2.*x).*exp(2/3.*x) + 4.*sin(7/2.*x).*exp(-3.*x)+3.*x;
% g = @(x) cos(x).*sin(x);
p = @(x) (x-1/10)^(-1/5);
n = 3;
a_b = [0.1 2.3];
I = 3.578861536040539915439859609644293194417;
X = linspace (a_b(1),a_b(2),3);
plot_arg = linspace(a_b(1),a_b(2));
half1 = linspace(a_b(1), ( a_b(2)-a_b(1) )/2);
half2 = linspace(( a_b(2)-a_b(1) )/2, a_b(2));
hold on;
plot(plot_arg,f(plot_arg), "--");

% Ньютон-Котс метод:

% 1) простая ИКФ по трем узлам
 J_3nNC = dot(arrayfun(f,X), IQF(a_b,n, "NC"))

% % 2) составная ИКФ по шести узлам 

segment1 =linspace(a_b(1),(a_b(1)+a_b(2))/2, 3); 
LagrangePoly1 = Lagrange(segment1, f(segment1));
plot(half1, f(half1), "LineWidth",2);

segment2 =linspace((a_b(1)+a_b(2))/2, a_b(2),3); 
LagrangePoly2 = Lagrange(segment2, f(segment2));
plot(half2, f(half2),"LineWidth", 2);

J_NC = CIQF(f, a_b, 3, 3, "NC")


% % 3) выбор оптимального числа узлов
k_opt = optCount(f,a_b,[2 3 5], "NC", I)

% % Гаусс метод:

% % 1) простая ИКФ по трем узлам

% % 2) составная ИКФ по шести узлам 
% J_G = CIQF(f, a_b, 2, 3, "G")

% 3) выбор оптимального числа узлов
% k_opt = optCount(f, a_b,[2 3 5], "G", I)

