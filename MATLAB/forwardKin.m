function [ X ] = forwardKin( x )
% Computes the forward kinematics for a vector x
% Takes a vector of angles in degrees, returns the
% Cartesian co-ordinates of all the points in the linkage
% Assumes all links are of length 1 for simplicity
X = zeros(length(x),2);
X(1,:) = [0,0];
for i = 1:length(x)
    j = i + 1;
    theta = (x(i) * pi) / 180; % Degrees to Radians
    X(j,1) = X(i,1) + cos(theta);
    X(j,2) = X(i,2) + sin(theta);
end
end

