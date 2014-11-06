function [ J ] = calcJacobian( E, P )
% calcJacobian - computes Jacobian given desired end position and current
% joint positions
%
% Input:
%           E - target end position
%           P - current joint positions (excluding base)
%
% Output:
%           J - Jacobian matrix

n = size(P,2); % number of joints
Z = [0,0,1]'; % z axis out of screen
J = zeros(3,n); 

for i = 1:n    
    J(:,i) = cross(Z, (E - P(:,i)));
end

end

