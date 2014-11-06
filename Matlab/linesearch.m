function [ alphahat ] = linesearch( target, x, x0, l, alpha0, c, tau, p )

% [ f, gradf ] = evalfunc( x );
f = evalF(target, x, x0, l);
J = fdJacobian(@evalF, target, x, x0, l);

m = p' * J;
t = -c*m;
alpha = alpha0;

while(  (f-evalF(target, x+alpha*p, x0, l)) < alpha*t )
    alpha = tau*alpha;    
end

alphahat = alpha;

end

