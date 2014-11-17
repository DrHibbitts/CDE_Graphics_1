function plotLinks(X, r, aSize)
% Plot the results

plot3(X(1,:),X(2,:),X(3,:),'O'); hold on;
plot3(X(1,:),X(2,:),X(3,:),'-','Linewidth',3);
ang = 0:(2*pi/360):2*pi;
x = X(1,1)+r*cos(ang);
y = X(2,1)+r*sin(ang);
plot3(x,y,zeros(size(x)));
plot3(x,zeros(size(x)),y);
plot3(zeros(size(x)),x,y);
axis(aSize); axis equal;
view(2);
hold off;

end

