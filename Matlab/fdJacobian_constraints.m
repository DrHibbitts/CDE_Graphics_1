function [ J ] = fdJacobian_constraints( fHandle, target, x, x0, l, c )
% Central Difference method for calculating the jacobian

h = 0.001;
y = fHandle(target, x, x0, l, c);
rows = length(y);
cols = length(x);
J = zeros(rows, cols);

for i = 1:rows
    for j = 1:cols
        xPlus = x;
        xPlus(j) = xPlus(j) + h;
        xMinus = x;
        xMinus(j) = xPlus(j) - h;
        Jtemp = (fHandle(target, xPlus, x0, l, c) - ...
            fHandle(target, xMinus, x0, l, c))/(2*h);
        J(i,j) = Jtemp(i);
    end
end

% Normalise columns
for i = 1:cols
    J(:,i) = J(:,i)./norm(J(:,i));
end

end

