function [] = plotOut( X,FX,P,aSize )
%% Plot the Results
figure;
subplot(1,2,1);
plot(X(:,1),X(:,2),'x');
hold on;
plot(X(:,1),X(:,2),'-');
plot(P(1),P(2),'xr');
axis(aSize);
subplot(1,2,2);
plot(FX(:,1),FX(:,2),'x');
hold on;
plot(FX(:,1),FX(:,2),'-');
plot(P(1),P(2),'xr');
axis(aSize);

end

