%% Set up and solve the equation
clear
% Set the initial angles
x = [45;0;45];
% Set the Acceleration
Acc = [10,15;10,15;10,15];
% Set the Axis Size
aSize = [-3 3 -3 3];
% Calculate the position with the initial angles
X = forwardKin(x);
% Set the target point
figure;
plot(X(:,1),X(:,2),'x');
hold on;
plot(X(:,1),X(:,2),'-');
axis(aSize);
[mX,mY] = ginput(1);
P = [mX;mY];
% Solve the equation to get the angles
F = fsolve(@evalF,x);
[mov,xT] = animateSolution(x,F,Acc,aSize);
% Calculate the positions for those angles
FX = forwardKin(F);
movie(mov,3);