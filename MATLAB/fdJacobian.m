function [ J ] = fdJacobian( fHandle, x )
% Central Difference method for calculating the jacobian
h = 0.01;
y = fHandle(x);
yLen = length(y);
xLen = length(x);
J = zeros(yLen, xLen);
for i = 1:yLen
    for j = 1:xLen
        xPlus = x;
        xPlus(j) = xPlus(j) + h;
        xMinus = x;
        xMinus(j) = xPlus(j) - h;
        Jtemp = (fHandle(xPlus)-fHandle(xMinus))/(2*h);
        J(i,j) = Jtemp(i);
    end
end
end

