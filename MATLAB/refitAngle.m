function [ xOut ] = refitAngle( xIn )
% Takes a vector of angles and returns the same 
% angles expressed in the range -180 to 180
xOut = mod(xIn,360);
xSize = length(xIn);
for i = 1:xSize
    if xOut(i)>=180 
        xOut(i) = xOut(i)-360;
    end
end
end

