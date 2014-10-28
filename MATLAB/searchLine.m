clear
c = 0.5;
tau = 0.5;
x(:,1) = [-2;3];
a_0 = 1;
p = -rFuncGrad(x(:,1));
testNorm_old = 1;
epsi = 1e-10;
newtonSteps = 1;
for k = 1:100000
    a = lineSearch(x(:,k),a_0,c,tau,p);
    a_j = a(1,size(a,2));
    testNorm_new = norm(a_j*p);
    if (abs(testNorm_new - testNorm_old)<epsi)
        break
    else
        x(:,k+1) = x(:,k) + a_j*p;
        B = rFuncGrad2(x(:,k+1));
        p2 = rFuncGrad(x(:,k+1));
        p = -B\p2;
        if p'*B*p <= 0
            p = p2;
        else
            newtonSteps = newtonSteps + 1;
        end
        testNorm_old = testNorm_new;
    end
end
i = -2:0.1:2;
j = -3:0.1:3.5;
xSize = size(i,2);
ySize = size(j,2);
z = zeros(xSize,ySize);
for m = 1:xSize
    for n = 1:ySize 
        z(m,n) = rFunc([j(n),i(m)]);
    end
end
figure;
colormap('hsv');
surf(i,j,-1.*z);
view(2);
hold on;
plot(x(1,:),x(2,:));