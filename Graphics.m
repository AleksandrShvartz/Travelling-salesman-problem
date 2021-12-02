times= zeros(1,97);
rezes=zeros(1,97);
iis=zeros(1,97);
for k=3:100
    n=k;
    % матрица расстояний
dist = zeros(n,n); 
% матрица обратных расстояний
returndist = zeros(n,n);
% генерация городов (x,y)
cities = rand(n,2)*100;
costs=rand(n)*10;
sumOfDist=0;
maxCost=-1;
% создаем матрицу расстояний и матрицу обратных расстояний
for i = 1:n
    
    for j = 1:n
        
        % dist ( расстояния )
        dist(i,j) = sqrt((cities(i,1) - cities(j,1))^2 + ...
           (cities(i,2) - cities(j,2))^2);
        sumOfDist=sumOfDist+dist(i,j);
            % nn ( обратные расстояния )
            if i ~= j
            returndist(i,j) = 1/sqrt((cities(i,1) - cities(j,1))^2 + ...
                (cities(i,2) - cities(j,2))^2); 
            end
            
    end
   costs(i)=costs(i)*costs(i);
   if maxCost<costs(i)
       maxCost=costs(i);
   end    
end
    tic
    rezes(k-2)=AntAlg(k,inf,dist,returndist,costs,maxCost);
    iis(k-2)=k;
    times(k-2)=toc*1e6;
end
plot(iis,times);



