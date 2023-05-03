data1 = 0.07* ones(5,1);
data2 = 0.13* ones(5,1);
data = zeros(10,1);

data(1:2:end) = data1(1:end);
data(2:2:end) = data2(1:end);

explode = mod(data,0.07);

pie(data,explode);