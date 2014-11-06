function [ F ] = evalF( target, x, x0, l )
% evalF - evaluates function

[X] = forwardK(x, x0, l);

tip = X(:,end);

F = target - tip;

end

