clc
clear
ni = 20;%number of n
X(1)= 1;%initial value
for i = 2:ni
    X(i) = (2*X(i-1)-1);
end
n = 1:10;

plot(n,X(n))
xlabel("n")
ylabel("X")
title("X(n)=2*X(n-1)-1")