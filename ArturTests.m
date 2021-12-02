filename='C:\Users\Vladimir_Shvartc\Downloads\tests3.txt';
fid = fopen(filename);
 count= fscanf(fid, '%*s\n%d\n', 1);
 times=zeros(1,count);
 error=zeros(1,count);
 iis=zeros(1,count);
for k=1:count
 clearvars -except k fid count times error iis
n=fscanf(fid,'%*s\n%d\n',1);
iis(k)=n;
time=fscanf(fid,'%*s %*s\n%d\n',1);
costs=zeros(1,n);
maxCost=-1;
fscanf(fid,'%*s\n',1);
costs=fscanf(fid,'%d',[1 n]);
for i = 1:n
     
   if maxCost<costs(i)
       maxCost=costs(i);
   end    
end
fscanf(fid,'\n%*s\n',1);
dist = zeros(n,n); 
for i = 1:n
    for j=1:n
    dist(i,j)=fscanf(fid,'%d',1);  
    end
end
returndist =1./dist;
fscanf(fid,'\n%*s ',1)
fscanf(fid,'%*s\n',1)
maxRaiting=fscanf(fid,'%d\n',1); 
arturRoad=zeros(1,n);
fscanf(fid,'%*s\n',1)
for i = 1:n
    arturRoad(i)=fscanf(fid,'%d',1)+1;  
end
tic
[a,route]=AntAlg(n,time,dist,returndist,costs,maxCost);
times(k)=toc*1e6;
error(k)=(maxRaiting-a)/maxRaiting;
if(error(k)<0)
    disp(a);
    disp(route);
    disp(maxRaiting);
    disp(arturRoad);
end
if(a~=maxRaiting)
fprintf('raiting is equal to %s but ants go %s\n',num2str(maxRaiting),num2str(a));
else
 fprintf('Test number %s is ok\n',num2str(k));   
end
end
fclose(fid);
figure;
plot(iis,times./1e6);
grid on;
figure;
plot(iis,error);
grid on;
