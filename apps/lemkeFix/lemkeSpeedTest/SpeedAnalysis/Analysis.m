load('time.mat')

loglog(SpeedTest_Lemke(:,1),'--rs','LineWidth',2,...
'MarkerEdgeColor','k',...
'MarkerFaceColor','g',...
'MarkerSize',10)
hold on
loglog(SpeedTest_Lemke(:,3),'--gs','LineWidth',2,...
'MarkerEdgeColor','k',...
'MarkerFaceColor','b',...
'MarkerSize',10)
loglog((exp(1.6688*log(1:9)-8.7847)))
xlabel('log(num of ct)')
ylabel('log(time)')
title('Lemke time --- log(time) = 1.6688*log(num of ct)-8.7847')
legend('Lemke only time','Overall time','Best linear fit')


%%

loglog(SpeedTest_LP(:,1),'--rs','LineWidth',2,...
'MarkerEdgeColor','k',...
'MarkerFaceColor','g',...
'MarkerSize',10)
hold on
loglog(SpeedTest_LP(:,3),'--gs','LineWidth',2,...
'MarkerEdgeColor','k',...
'MarkerFaceColor','b',...
'MarkerSize',10)
plot(0.1228913*1e-3*[1:9]+0.29986*1e-3)
xlabel('log(num of ct)')
ylabel('log(time)')
title('LP time --- log(time) = 0.1228913*1e-3*(num of ct)+0.29986*1e-3')
legend('LP only time','Overall time','Best linear fit')
