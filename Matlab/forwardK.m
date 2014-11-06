function [X] = forwardK(x, x0, l)
% Computes the forward kinematics
%
% Input:
%           x - nx1 vector of angles (degrees)
%           x0 - 3x1 vector defining base position
%           l - nx1 vector of linkage lengths
%
% Output:
%           X - 3x(n+1) joint coordinates

theta = cumsum(x,1).*pi/180;
X = zeros(3,length(x)+1);
X(:,1) = x0; % base position

for i = 1:length(x)
    j = i + 1;
    X(1,j) = X(1,i) + l(i)*cos(theta(i));
    X(2,j) = X(2,i) + l(i)*sin(theta(i));
end

end

