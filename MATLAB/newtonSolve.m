function [ xOut ] = newtonSolve( fHandle, dfHandle, df2Handle, x0 )
% Implements Newtons method for general functions
c = 0.5;
tau = 0.5;
x(:,1) = x0;
a_0 = 1;
p = -dfHandle(x(:,1));
testNorm_old = 1;
epsi = 1e-10;
newtonSteps = 1;
for k = 1:100000
    a = lineSearch(x(:,k),a_0,c,tau,p,fHandle,dfHandle);
    a_j = a(1,size(a,2));
    testNorm_new = norm(a_j*p);
    if (abs(testNorm_new - testNorm_old)<epsi)
        break
    else
        x(:,k+1) = x(:,k) + a_j*p;
        B = df2Handle(x(:,k+1));
        p2 = dfHandle(x(:,k+1));
        p = -B\p2;
        if p'*B*p <= 0
            p = p2;
        else
            newtonSteps = newtonSteps + 1;
        end
        testNorm_old = testNorm_new;
    end
end

end

