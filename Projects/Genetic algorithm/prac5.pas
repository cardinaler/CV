program prac3;
type population=array [1..50] of longint;         //Здесь хранятся первые 10 сгенерированных особей
	 new_population=array [1..50] of integer;	  //Здесь хранятся новые популяции
	 survive=array [1..50] of boolean ;       	  //Здесь отмечаются особи, которые остались после селекции
     strong=array [1..2] of longint ;			  //Здесь пара для скрещивания
     byte_indi=array [1..14] of 0..1;			  //Двоичный код особи
     pair_num=array [1..25] of strong;
var indi:population;		
	iteration_num:integer;						  //Счетчик итераций
	i,j:integer; 									  //Глобальный счетчик
	stop:boolean;								  //Флаг останова				
    y_max,x_max,limit:real; 							  //Лучший результат и предел для останова
    crossings_num,mutations_num:integer;          //Количество скрещиваний, количество мутаций,
    crossover_prob,mutation_prob:real;			  //Вероятность скрещивания, вероятность мутации
    pairs:pair_num; first_byte,step_byte:byte_indi;		//Двумерный массив для хранения 25 пар, выбранных после селекции для скрещивания
    survivors:survive;                            //Выжившие после селекции
    indi_num:integer;							  //Количество особей в популяции
    mutation_counter:integer;
    mode:byte;
function F(a:integer):real;						  //Функция взятая со знаком минус, чтобы минимумы стали максимумам
begin
	F:=(4*a)/16384;
	F:=-(F-2.1)*(F-1.5)*(F-2.4)*(F-0.33)*cos(F)*(1-exp(F-3.5))+25;
	
end;

procedure generation(var a:population); //Генератор начальной популяции из 10 особей
var i:integer;
begin
	
	for i:=1 to 10 do
		a[i]:=random(16384);
	indi_num:=10;
end;

procedure ostanov(a:population);      //Критерий останова **ДОДЕЛАТЬ

begin 
	if y_max>limit then stop:=true;
end;

procedure population_estimate(indi:population); //Оценка популяции, вычисление лучшие результата
var i:integer;
begin
	for i:=1 to indi_num do 
		if F(indi[i])>y_max then
		begin
			y_max:=F(indi[i]);
			x_max:=indi[i];
		end;
	if y_max>limit then stop:=true;
end; 

procedure selection(indi:population; var pair:strong);    //Селекция, выбор двух особей для скрещивания. + отметка выживших особей
var ran,sum,temp:real; count,i:integer;
begin
	
	sum:=0;
	count:=1;
	for i:=1 to indi_num do   //ГЕНИАЛЬНО
		sum:=sum+F(indi[i]);
	repeat
	for count:=1 to 2 do
	begin
		temp:=0;
		ran:=random(628)/100;
		for i:=1 to indi_num do 
		begin
			temp:=temp+F(indi[i]);
			if ran<=(2*3.1415*temp)/sum then
			begin
				//writeln('** ***',ran:0:4, '** ', (2*3.1415*temp)/sum:0:4, '** ', sum:0:4  );
				pair[count]:=indi[i];	 //Первая особь пары
				survivors[i]:=true;      //После селекции под номером i находится выживший
				break;
			end 
			 
		end;
	end;
	until pair[1]<>pair[2];           // Чтобы одна и та же особь не попадалась дважды
end;

procedure transformation_indi_to_byts (pair:strong; var first_byte,step_byte:byte_indi);   
var i:integer;
begin
	for i:=14 downto 1 do 
	begin
		first_byte[i]:=pair[1] mod 2;
		step_byte[i]:=pair[2] mod 2;
		
		pair[1]:=pair[1] div 2;
		pair[2]:=pair[2] div 2;
	end;
end;

procedure crossing(var first_byte,step_byte:byte_indi);    //Скрещивание. В first_byte и step_byte находятся коды потомков  
var temp:byte_indi; ran:byte; i:integer;                                      
begin
	temp:=first_byte;      //temp содержит двоичный код первой особи 
	if (random(100)/100)>crossover_prob then exit;
	for i:=1 to 14 do        //Первая особь берет данные второй
	begin
		ran:=random(2);
		if ran=1 then first_byte[i]:=step_byte[i];
	end;
	
	for i:=1 to 14 do       // Вторая особь берет данные первой 
	begin
		ran:=random(2);
		if ran=1 then step_byte[i]:=temp[i];
	end;
	
end;

procedure mutation(var first_byte:byte_indi);     //Мутация  **добавить зависимость от вероятности
var ran:byte;
begin
	
	if (random(100)/100)>mutation_prob then
	begin
	 mutation_counter:=mutation_counter+1;	
	 exit;
	end;
	ran:=random(14)+1;
	if first_byte[ran]=1 then first_byte[ran]:=0   //Один из 14 битов потомка first_byte заменяется на противоположный
	else first_byte[ran]:=1;
	mutation_counter:=mutation_counter+1;
end;

procedure reset(survivors:survive);
var i:integer;
begin
	for i:=1 to 50 do 
		survivors[i]:=false;
end;


procedure transformation_byts_to_pair(var pairs:strong; first_byte,step_byte:byte_indi); //Трансформирует коды в решения и записывает их в pair[i][1] и pair[i][2]
var step,i:integer;
begin
	step:=1;
	pairs[1]:=0;
	pairs[2]:=0;
	for i:=0 to 13 do
	begin
		pairs[1]:=pairs[1]+step*first_byte[14-i];
		pairs[2]:=pairs[2]+step*step_byte[14-i];
		step:=step*2;
	end;
end;
 
procedure create_population_after_selection(var indi:population);					//Популяция в indi будет перезаписана на популяцию, получившеюся после селекции
var count:integer;
begin
	//indi_num:=0;    //Обнуление количества особей
	count:=1;
	for i:=1 to indi_num do      //Остаются только выжившие
		if survivors[i]=true then 
		begin
			indi[count]:=indi[i];
			count:=count+1;
		end;
	indi_num:=count-1;     //Обновление количество особей в популяции
end;   

procedure create_population_after_crossing(var indi:population; pairs:pair_num);  //Берет потомков из pairs и заменяет особей в основной популяции на них
var i:integer; 
begin
	indi_num:=2*crossings_num;
	
	for i:=1 to crossings_num do                      //Остановился на том, что надо получившихся потомков записать в indi, предусмотреть случай, когда потомков меньше чем особей в indi
	begin
		indi[2*i-1]:=pairs[i][1];
		indi[2*i]:=pairs[i][2];
	end;
end;


procedure data_input;
begin
	writeln('Enter operating mode');
	writeln('1.Debug mode');
	writeln('2.Normal mode');
	read(mode);
	write('Eenter the number of crossings (1<x<25):');
	read(crossings_num);
	writeln;
	write('Enter the crossover probability (0<x<=1):');
	read(crossover_prob);
	writeln;
	write('Enter the number of mutations(<=2x number of crossings): ');
	read(mutations_num);
	writeln;
	write('Enter the mutation probability(0<x<=1): ');
	read(mutation_prob);
	if ((mode<>1) and (mode<>2)) or (crossings_num>=25) or (crossings_num<=1) or (crossover_prob<0) or (crossover_prob>1) or (mutations_num<=0) or (mutations_num>2*crossings_num) or (mutation_prob<=0) or (mutation_prob>1)  then 
	begin
		write('Go out of range. Please try again.');
		stop:=true;
	end;
end;

procedure Normal_mode;
begin
	while stop=false do
	begin
		mutation_counter:=0;
		reset(survivors);
		for i:=1 to crossings_num do
			selection(indi, pairs[i]);                                  // Селекция и запись пары в pair[i][1] pair[i][2]
		create_population_after_selection(indi);
		
		for i:=1 to crossings_num do
		begin
			transformation_indi_to_byts(pairs[i],first_byte,step_byte); //Перевод данных особей из pair[1] в двоичный код, который записывается в first_byte и step_byte
			crossing(first_byte,step_byte);				                //Скрещивание решений из pair[i], first_byte будет содержать код первого потомка. step_byte, будет содержать код второго потомка
			if mutation_counter<mutations_num then mutation(first_byte);             //Это мутация
			if mutation_counter<mutations_num then mutation(step_byte);              //Это мутация
			transformation_byts_to_pair(pairs[i],first_byte,step_byte);
		end;
		create_population_after_crossing(indi,pairs);
		population_estimate(indi);
		iteration_num:=iteration_num+1;
		
	end;
end;


procedure Debug_mode;
begin
	while stop=false do
	begin
		mutation_counter:=0;
		reset(survivors);     //Отметка всех выживших = false
		writeln;
		writeln('Start population');
		for i:=1 to indi_num do
			write(indi[i], ' ');
		
		writeln;
		
		
		for i:=1 to crossings_num do
			selection(indi, pairs[i]);                 // Селекция и запись пары в pair[i][1] pair[i][2]
		
		create_population_after_selection(indi);        //Перезаписывание популяции в indi
		writeln;
		writeln('*POPULATIONS AFTER SELECTION**');	
		for i:=1 to indi_num do
		begin
			write(indi[i], ' ');
	
		end;
		writeln;
		writeln;	
		writeln('**PAIRS FOR CROSSING**');
		for i:=1 to crossings_num do	
		begin
			writeln(pairs[i][1],' ' , pairs[i][2]);
			transformation_indi_to_byts(pairs[i],first_byte,step_byte);
			for j:=1 to 14 do 
				write(first_byte[j],' ' );
			writeln;
			for j:=1 to 14 do 
				write(step_byte[j],' ' );
			writeln;
		end;	
		writeln;	
		writeln('AFTER CROSSING');	
		for i:=1 to crossings_num do
		begin
			transformation_indi_to_byts(pairs[i],first_byte,step_byte);  //Перевод данных особей из pair[1] в двоичный код, который записывается в first_byte и step_byte
			
			crossing(first_byte,step_byte);	   //Скрещивание решений из pair[i], first_byte будет содержать код первого потомка. step_byte, будет содержать код второго потомка
			transformation_byts_to_pair(pairs[i],first_byte,step_byte);
			//write(pairs[i][1], ' ' ,pairs[i][2]);
			transformation_indi_to_byts(pairs[i],first_byte,step_byte);
			for j:=1 to 14 do 
				write(first_byte[j],' ' );
			writeln;
			for j:=1 to 14 do 
				write(step_byte[j],' ' );
			writeln;
			writeln;
		end;
		writeln;
		writeln('AFTER MUTATIONS');
		for i:=1 to crossings_num do	
		begin
			transformation_indi_to_byts(pairs[i],first_byte,step_byte);
			if mutation_counter<mutations_num then mutation(first_byte);             //Это мутация
			if mutation_counter<mutations_num then mutation(step_byte);              //Это мутация
			transformation_byts_to_pair(pairs[i],first_byte,step_byte);
			//write(pairs[i][1], ' ' ,pairs[i][2]);
			transformation_indi_to_byts(pairs[i],first_byte,step_byte);
			for j:=1 to 14 do 
				write(first_byte[j],' ' );
			writeln;
			for j:=1 to 14 do 
				write(step_byte[j],' ' );
			writeln;
			writeln;
			writeln;
		end;
		create_population_after_crossing(indi,pairs);
		writeln;
		writeln('POPULATIONS AFTER ITTERATION');
		for i:=1 to indi_num do
			write(indi[i], ' ');
		writeln;
		
		population_estimate(indi);   //Оценка популяции с поиском максимума
		writeln;
		writeln;
		iteration_num:=iteration_num+1;
		writeln('**Results after iteration** y_max=', (y_max-25):0:3, ' limit=' , (limit-25):0:3, ' x_max=', (4*x_max/16384):0:4, ' iteration_num ' , iteration_num);
		
	end
end;

begin
	randomize();		   
	limit:=F(13107);       //Когда достигнется это значение-произойдет выход из цикла
	stop:=false;
	y_max:=0;
	iteration_num:=0;     
	data_input;           //Ввод данных
	generation (indi);    //Генерация 10 особей
	if (mode=1) then Debug_mode
	else 
	begin
		Normal_mode;
		writeln;
		writeln('**Results after iterations** y_max=', (y_max-25):0:3, ' limit=' , (limit-25):0:3, ' x_max=', (4*x_max/16384):0:4, ' iteration_num ' , iteration_num); 
	end;
end.
	// При селекции сгенерировать random(628)/100, и потом смотрим куда попало 
