function [ movOut, xT ] = animateSolution( x_0, x_1, a, aSize )
d = x_1 - x_0;
dLen = length(d);
xT = [];
for i = 1:dLen
    tMax = a(i,2)/a(i,1);
    if d(i) < 0
        acc = -a(i,1);
    else
        acc = a(i,1);
    end
    xAccMax = calcPos(0,acc,0,tMax);
    vMax = acc*tMax;
    if size(xT,2) < 1
        xT(:,1) = zeros(dLen,1);
    end
    if abs(d(i)) < abs(2*xAccMax)
        tMid = sqrt(d(i)/acc);
        xMid = calcPos(0,acc,0,tMid);
        uMid = acc*tMid;
        tTotal = ceil(2*tMid);
        tCeil = max(tTotal, size(xT,2)-1);
        for t = 1:tCeil
            if size(xT,2) < t+1
                xT(:,t+1) = xT(:,t);
            end
            if t >= tTotal
                xT(i,t+1) = d(i);
            else
                if t < tMid
                    xT(i,t+1) = calcPos(0,acc,0,t);
                else
                    xT(i,t+1) = calcPos(xMid,-acc,uMid,t-tMid);
                end
            end
        end
    else
        dLin = d(i) - 2*xAccMax;
        tLin = dLin / vMax;
        tFirst = tMax;
        xFirst = calcPos(0,acc,0,tFirst);
        tSecond = tFirst + tLin;
        xSecond = xFirst + dLin;
        tTotal = ceil(tSecond + tFirst);
        tCeil = max(tTotal, size(xT,2)-1);
        for t = 1:tCeil
            if size(xT,2) < t+1
                xT(:,t+1) = xT(:,t);
            end
            if t >= tTotal
                xT(i,t+1) = d(i);
            else
                if t < tFirst
                    xT(i,t+1) = calcPos(0,acc,0,t);
                elseif t < tSecond
                    xT(i,t+1) = xFirst + vMax*(t-tFirst);
                else
                    xT(i,t+1) = calcPos(xSecond,-acc,vMax,(t-tSecond));
                end
            end
        end
    end
end
tSize = size(xT,2);
for i = 1:tSize
    xT(:,i) = x_0 + xT(:,i);
end
movOut = recordMovie(xT,aSize);
end

function [sOut] = calcPos(sIn, a, u, t)
sOut = sIn + 0.5 * a * t^2 + u*t;
end

function [movOut] = recordMovie(xT, aSize)
P = evalin('base','P');
h=figure('visible','off');
loops = size(xT,2);
F(loops) = struct('cdata',[],'colormap',[]);
eFX = [];
for j = 1:loops
    FX = forwardKin(xT(:,j));
    eFX(j,:) = FX(end,:);
    plot(FX(:,1),FX(:,2),'-');
    hold on;
    plot(P(1),P(2),'xr');
    plot(eFX(:,1),eFX(:,2),'g')
    axis(aSize);
    drawnow
    hold off;
    F(j) = getframe;
end
assignin('base','eFX',eFX);
close(h);
movOut = F;
end

