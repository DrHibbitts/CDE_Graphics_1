function [ F ] = evalF_constraints( target, x, x0, l, c )
% evalF - evaluates function with constraints

[X] = forwardK(x, x0, l);

tip = X(:,end);

F = target - tip;

for i = 1:length(c)
    F = F + 1/abs(abs(x(i))-c(i));
end

end