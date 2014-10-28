x = -2:0.1:2;
y = -1:0.1:3;
xSize = size(x,2);
ySize = size(y,2);
z = zeros(xSize,ySize);
for i = 1:xSize
    for j = 1:ySize 
        z(i,j) = rFunc([x(i),y(j)]);
    end
end
figure;
colormap('hsv');
surf(x,y,z);
%%%
