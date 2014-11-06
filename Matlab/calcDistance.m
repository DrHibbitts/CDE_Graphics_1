function d = calcDistance(target, x, x0, l)
% calcDistance - computes distange between target end position and current
% end position
%
% Input:
%           target - target end position
%           x - current angles (degrees)
%           x0 - base position
%           l - linkage lengths
%
% Output:
%           d - distance

X = forwardK(x, x0, l);
d = norm(target - X(:,end));

end
