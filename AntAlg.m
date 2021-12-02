% муравьиный алгоритм ( на примере задачи коммивояжера )

% -------------------------------------------------------------------------
function [rez1,rez2] = AntAlg(N,T,DIST,RETURNDIST,COSTS,maxCost)

% clearvars -except cities
%clearvars
 
% ------------------------------ИТЕРАЦИИ-----------------------------------

% кол-во итераций ( поколений )
age = 2000;

% кол-во муравьев в поколении
countage = 20;

% кол-во городов
n = N;
%ограничитель
TIME=T;
% ------------------------------ПАРМЕТРЫ-----------------------------------

% альфа - коэффициент запаха, при 0 будем ориентироваться только на
% кратчайший путь 
a = 1; 

% бета - коэффициент расстояния, при 0 будем
% ориентироваться только на оставляемый запах
b = 2;

% коэффициент обновления, глобальное
e = 0.1;

% коэффициент обновления, локальное
p = 0.1;

% количество выпускаемых феромонов 
Q = 1;

% баланс между лучшим городом и как в AS
q = 0.9;

% начальный феромон
 ph = Q/(n*2000);

% -------------------------------ПАМЯТЬ------------------------------------
% матрица расстояний
dist = DIST; 
% матрица обратных расстояний
returndist = RETURNDIST; 
%матица времен муравьев в одном поколении
TIMEant = zeros(1,countage);
TIMEant=TIMEant + TIME;
% матрица маршрута муравьев в одном поколении
ROUTEant = zeros(countage,n);
LENGTHant=zeros(countage,1);
% вектор расстояний муравьев в одном поколении
DISTant = zeros(countage,1); 
RAITant =zeros(countage,1); 
% вектор лучших дистанций на каждой итерации
bestDistVec = zeros(age,1);
% лучший начальный маршрут
bestDIST = -1; 

% оптимальные маршруты
ROUTE = zeros(1,n+1);

% перестановка городов без повторений ( для выхода муравьев )
%RANDperm = randperm(n);

% матрица вероятностей
P = zeros(1,n);

% максимальное значение вероятности
val = zeros(1);

% присваем номер города
getcity = zeros(1);

% индекс максимального значения вероятности
indexP = zeros(1);

% максимальное
minDISTiterration = zeros(1);

% -------------------------------------------------------------------------

% генерация городов (x,y)
costs=COSTS;
% матрица начальных феромонов
tao = ph*(ones(n,n));
tao(logical(eye(size(tao)))) = 0;

% итерации
for iterration = 1:age
    
    TIMEant=zeros(1,countage)+TIME;
    LENGTHant=zeros(countage,1);
    % муравьи ( одно поколение)
    for k = 1:countage 
    % ****************** НАЧАЛЬНОЕ РАСПОЛОЖЕНИЕ МУРАВЬЕВ ******************
    % выбирайте какой нужно
    
    % каждый муравей располагается случайно    
    %  ROUTEant(k,1) = randi([1 n]);
    
    % с каждого города выходит один муравей ( без совпадений ), кол-во
    % городов и кол-во муравьев в поколении должны быть равны
%       ROUTEant(k,1) = RANDperm(k);
    
    % с конкретного города выходят все муравьи в данном случа с 1-ого
       ROUTEant(k,1) = 1;

% тут маршрут первому поколению задаем либо произвольный, либо с каждого
% города разный, либо с одного города все, а следующее поколение выходит по
% концам первых

   %  if iterration == 1
 %     ROUTEant(k,1) = randi([1 n]);
 %       ROUTEant(k,1) = RANDperm(k);
  %    ROUTEant(k,1) = 1;
 %    else
  %     ROUTEant(k,1) = lastROUTEant(k);  
  %   end
    
    % *********************************************************************
    
    % путь каждого муравья, начиная со второго, так как первый выбран
    for s = 2:n  

        % полуаем индекс выбранного города
        ir = ROUTEant(k,s-1);
 
        % вероятность посещения городов ( числитель ) , в числителе у нас
        % следующее: tao^a*(1/S)^b 
        % 1/S -это returndist. 
        
        % поскольку данное значение будет повторяться (кол-во муравьев * на
        % колонию * кол-во городов) раз, то еще один цикл писать не выгодно,
        % скорость работы при таких вычислениях падает. Поэтому написал в 
        % этом моменте векторно. На обычном языке будет так: 
        
         for c = 1:n  
             if(TIMEant(1,k)-dist(ir,c)>=0)
                 P(1,c) = tao(ir,c).^a * returndist(ir,c).^b .* costs(ir) ./ maxCost;  
             else
              P(1,c)=0;
             end
         end

       % P = tao(ir,:).^a .* returndist(ir,:).^b .* costs(ir) ./ maxCost;
        % получили числители (в формуле вероятности перехода к k-ому городу)
        % для n городов, однако в некоторых мы уже побывали, нужно исключить
        % их
        
        % проставляем нули в числитель туда, где уже были, чтобы
        % вероятность перехода была 0, следовательно в сумме знаменателя
        % формулы данный город учитываться не будет    
        P(ROUTEant(k,1:s-1)) =0;
        
        % смотрим в какой город осуществляется переход
        RANDONE = rand;
        if(sum(P)==0)
            break;
        end
        if RANDONE <= q
            [val, getcity] = max(P);
        else
            % получаем вероятности перехода ( сумма строк должна быть = 1 )
            P = P ./ sum(P);
            getcity = find(cumsum(P) >= RANDONE, 1, 'first');
        end
        % присваем s-ый город в путь k-ому муравью
        ROUTEant(k,s) = getcity;
        LENGTHant(k)=LENGTHant(k)+1;
        if( TIMEant(k)<0)
            print("Arr");
        end
        TIMEant(k)=TIMEant(k)-dist(ir,getcity);  
      %  hold on;
       % line(cities(getcity),cities(ir));

    end
        
    % получаем маршрут k-ого муравья
    ROUTE = ROUTEant(k,1:end);
    
    % сброс длины и суммарного рейтинга
   % S = 0;
    RATING=costs(ROUTE(1));
    % вычисляем маршрут k-ого муравья
    for i = 1:n-1
        if(ROUTE(i+1)~=0)
            %S = S + dist(ROUTE(i),ROUTE(i+1));  
            RATING=RATING + costs(ROUTE(i+1));
        else
            break;
        end
       
    end
    
    % путь k-ого муравья, массив дистанций k-ых муравьев age-ого поколения
    %DISTant(k) = S;
    RAITant(k)=RATING;
    % присваевыем лучший маршрут и S     
    if RAITant(k) > bestDIST
        bestDIST = RAITant(k);
        bestROUTE = ROUTEant(k,[1:LENGTHant(k)]); 
        iter = iterration;
        bestLENGTH=LENGTHant(k);
    end
    
    % вектор "последних" городов k-ых муравьев ( выбирается для старта
    % муравьев нового поколения с тех городов, где закончили путь
    % предыдущее поколение)
    
    % lastROUTEant = ROUTEant(1:end,end); 
   
    % локальное обновление феромона, после  каждого муравья
    for tL = 1:LENGTHant(k)-1

        xL = ROUTE(tL);
        yL = ROUTE(tL+1);

        % считаем новый феромон
        tao(xL,yL) = (1-p)*tao(xL,yL) + p*ph;
        tao(yL,xL) = (1-p)*tao(yL,xL) + p*ph;
        
    end   
    
    end
% --------------------------ГЛОБАЛЬНОЕ ОБНОВЛЕНИЕ--------------------------

    % Испаряем феромоны "старого" пути е - коэффициент испарения
    
    tao(tao < 2.500000000000000e-150) = 2.500000000000000e-150;
    
        % для каждого города
        for t = 1:n-1
            
            xG = t;
            yG = t+1;
            
            % считаем новый феромон
            tao(xG,yG) = tao(xG,yG) + e*(Q/bestDIST); 
            tao(yG,xG) = tao(yG,xG) + e*(Q/bestDIST);
            
        end
        
end 
rez1=bestDIST;
rez2=bestROUTE;
end
