function plotLinks(X, r, aSize)
% Plot the results

plot(X(1,:),X(2,:),'O'); hold on;
plot(X(1,:),X(2,:),'-','Linewidth',3);
ang = 0:(2*pi/360):2*pi;
x = X(1,1)+r*cos(ang);
y = X(2,1)+r*sin(ang);
plot(x,y);
axis(aSize); axis equal;
hold off;

end

