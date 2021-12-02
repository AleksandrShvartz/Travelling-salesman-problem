%% График зависимости времени от количества городов
figure;
x = 3 : 1 : 500;
hold on;
grid on;
fid = fopen("C:\Users\faizr\source\repos\TravelingSalesmanProblem\TravelingSalesmanProblem\workingHoursFromSize.txt", 'r');
poly = fscanf(fid, "%g");
plot(x, poly / 1000);

%% График 
figure;
hold on;
grid on;
fid = fopen("C:\Users\faizr\source\repos\TravelingSalesmanProblem\TravelingSalesmanProblem\solutionAccuracy.txt", 'r');
poly = fscanf(fid, "%g");
plot(x, poly / 10);