%% Set up and solve the equation
% Set the initial angles
x = [45;0;45];
% Set the target point
P = [2;1.5];
% Calculate the position with the initial angles
X = forwardKin(x);
% Solve the equation to get the angles
F = fsolve(@evalF,x);
% Calculate the positions for those angles
FX = forwardKin(F);
%% Plot the Results
figure;
subplot(1,2,1);
plot(X(:,1),X(:,2),'x');
hold on;
plot(X(:,1),X(:,2),'-');
plot(P(1),P(2),'xr');
axis([0 3 0 3]);
subplot(1,2,2);
plot(FX(:,1),FX(:,2),'x');
hold on;
plot(FX(:,1),FX(:,2),'-');
plot(P(1),P(2),'xr');
axis([0 3 0 3]);