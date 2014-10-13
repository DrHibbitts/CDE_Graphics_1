function [ F ] = evalF( x )
% Calculates F(x) - P for a given value of x
% F(x) is the position of the end point with angles given by x
% P is the target point evaluated in the base workspace
% Assumes all links are of length 1 for simplicity
F = zeros(2,1);
P = evalin('base','P');
for i = 1:length(x)
    theta = (x(i) * pi) / 180;
    F(1) = F(1) + cos(theta);
    F(2) = F(2) + sin(theta);
end
F = F - P;
end

