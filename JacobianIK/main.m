clear; close all;
while(1)
    % Initialise
    x = [5,5,5,5,5]'; % angles
    v = [0,0,0,0,0]'; % angular velocities
    a = [0,0,0,0,0]'; % angular accelerations
    x0 = [0,0,0]'; % initial base position
    l = [1,1,1,1,1]'; % joint lengths
    r = sum(l); % max radius
    aSize = [x0(1)-r x0(1)+r x0(2)-r x0(2)+r]; % axis size
    
    % Compute position with initial angles
    X = forwardK(x, x0, l);
    figure(1); plotLinks(X, r, aSize); hold on;
    
    % Target
    [a,b] = ginput(1);
    target = [a,b,0]';
    figure(1); plot(target(1),target(2),'r*');
    
    % Re-Target
    targetVec = target - x0;
    targetDist = norm(targetVec);
    if targetDist > r
        targetVec = targetVec * ((r*0.99)/targetDist);
    end
    target = x0 + targetVec;
    figure(1); plot(target(1),target(2),'k*');
    
    % Tip
    tip = X(:,end);
    
    i = 1;
    tipStore = [];
    tipStore(1,:) = tip;
    
    %% Inverse K
    alpha = 0.01; % step size
    while(1)
        figure(1);
        J = calcJacobian(target, X(:,2:end)); % compute Jacobian
%         Jplus = pinv(J); % pseudo inverse
        Jplus = J'; % transpose also works surprisingly well!
        dE = target - tip;
%         err = norm((eye(size(Jplus*J)) - Jplus*J)*dE)
        dTheta = ( Jplus*dE )*180/pi; % degrees
        x = x + alpha*dTheta; % update angles
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