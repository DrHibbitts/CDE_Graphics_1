clear; close all;
    % Initialise
    step = 0.051; % step size
    x = [0,0]'%,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5]'; % angles
    x0 = [0,0,0]'; % initial base position
    l = [0.5,1.5]'%,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1]'; % joint lengths
    c = [180,30]'; % constraint angles
    w = [1,1]%,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1]; % weights
    r = sum(l); % max radius
    aSize = [x0(1)-r x0(1)+r x0(2)-r x0(2)+r]; % axis size
while(1)
    
    % Compute position with initial angles
    X = forwardK(x, x0, l);
    figure(1); plotLinks(X, r, aSize); hold on;
    
    % Scaling matrix
    k = 1; % proportionality constant
    K = zeros(length(x));
    for i = 1:length(x)
        K(i,i) = 1/(k*l(i)*w(i));
    end
    
    % Target
    [a,b] = ginput(1);
    target = [a,b,0]';
    figure(1); plot(target(1),target(2),'r*');
    
    % Re-Target if out of range
    targetVec = target - x0;
    targetDist = norm(targetVec);
    if targetDist > r
        targetVec = targetVec * ((r*0.99)/targetDist);
    end
    target = x0 + targetVec;
    figure(1); plot(target(1),target(2),'k*');
    
    % Tip
    tip = X(:,end);
    
    % Store tip position
    i = 1;
    tipStore = [];
    tipStore(1,:) = tip;
    
    %% Inverse K
    
    while(1)
%         J = calcJacobian(target, X(:,2:end)); % compute Jacobian
%         J = -fdJacobian(@evalF, target, x, x0, l);
        J = -fdJacobian_constraints(@evalF_constraints, target, x, x0, l, c);
%         Jplus = pinv(J); % pseudo inverse
        Jplus = J'; % transpose also works surprisingly well!
        dE = target - tip;
%         err = norm((eye(size(Jplus*J)) - Jplus*J)*dE)
        dTheta = ( K*Jplus*dE )*180/pi; % degrees
%         alpha = dot(dE, J*J'*dE) / dot(J*J'*dE, J*J'*dE);
        x = x + step*dTheta; % update angles
        X = forwardK(x, x0, l);
        tip = X(:,end);
        i = i + 1;
        tipStore(i,:) = tip;
        figure(1); plotLinks(X, r, aSize); hold on;
        plot(target(1),target(2),'r*');
        plot(tipStore(:,1),tipStore(:,2),'g');
        hold off;
        if norm(target - tip) < 0.1
            disp('Finished!');
            break
        end
    end
end