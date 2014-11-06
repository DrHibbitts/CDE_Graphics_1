clear all; close all;

x = [5,5,5,5,5]'; % angles
x0 = [0,0,0]'; % initial base position
l = [1,1,1,1,1]'; % joint lengths

% Target
target = [1,1,0]';

alpha = 1;
c = 0.5;
tau = 0.5;
num_iter = 100;
EPSILON = 1e-10;

% [f, gradf, hess] = evalfunc(x);
f = evalF(target, x, x0, l);
J = fdJacobian(@evalF, target, x, x0, l);
% H = 2*(J'*J);
H = J*J';

xstore = NaN(length(x),num_iter);

for i=1:num_iter

fprev = f;
xstore(:,i) = x;

p = -H\J;
% Check hessian is positive definite
if ( p'*H*p <= 0)
    p = -J;
end

% Perform line search and update
alphahat = linesearch(target, x, x0, l, alpha, c, tau, p);
x = x+alphahat*(-H\J);
% [f, J, H] = evalfunc(x);
f = evalF(target, x, x0, l);
J = fdJacobian(@evalF, target, x, x0, l);
% H = 2*(J'*J);
H = J*J';

% Check if converges
if( abs(f - fprev) < EPSILON )
    f
    x
    i
    break;
end

end

% plot(xstore(1,:), xstore(2,:));
