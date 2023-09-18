program pacrtic2;
const N=100;
type vector=array [1..N] of integer;
var mas:vector;
	num_mov,num_com,i:integer; flag:boolean; size: integer;
	sort_t,mode:integer;

procedure output_array(a:vector);
var i:integer;
begin
	for i:=1 to size do
		write (a[i], ' ');
	writeln;
end;

procedure insert_binare_sort(var a:vector; length:integer);
var j,k,mid:integer;

procedure Debug_mode;                             //Описание тестового режима
begin
	writeln;
	writeln('Step:', num_mov);
	write('Sequence:'); output_array(a);
	write('Moved elements:'); writeln(j, ' ' ,j+1);
	writeln('Number of movements:',num_mov);
	writeln('Number of comparisons:',num_com);
	writeln
end;

begin num_mov:=0; num_com:=0;

	for k:=2 to length do
	begin
	
		i:=1; j:=k;
		if sort_t=2 then
		begin
			while i<>j do				//Бинарный поиск по возрастанию
			begin
				mid:=(i+j) div 2; num_com:=num_com+1;
				if a[mid]>a[k] then j:=mid
				else i:=mid+1;
			end;
		end
		else
		begin
			while i<>j do				//Бинарный поиск по убыванию
			begin
				mid:=(i+j) div 2;   num_com:=num_com+1;
				if a[mid]>a[k] then j:=mid
				else i:=mid+1;
			end;
		end;
		j:=k;
		while i<>j do              //Перемещение элемента на нужное место 
		begin
			a[j-1]:=a[j]+a[j-1]; 
			a[j]:=a[j-1]-a[j];
			a[j-1]:=a[j-1]-a[j];
			j:=j-1;
			num_mov:=num_mov+1;
			if(mode=2) then Debug_mode;
		end;
	
	end;


end;



procedure selection_sort ( a:vector; length:integer);                //выборочная сортировка
var j,min:integer;

procedure Debug_mode;                             //Описание тестового режима
begin
	writeln;
	writeln('Step:', num_mov);
	write('Sequence:'); output_array(a);
	write('Compared elements:'); writeln(j, ' ' ,min); /// j     min
	writeln('Number of movements:',num_mov);
	writeln('Number of comparisons:',num_com);
	writeln;
	
end;


begin	num_mov:=0; num_com:=0;

	for j:=1 to length do
	begin
		min:=j; flag:=false;
		if sort_t=2 then								//Алгоритм упорядочения по возрастанию, ищет минимальный
		begin	
			for i:=j+1 to length do
			begin 
				num_com:=num_com+1;
				if a[min]<a[i] then begin flag:=true; min:=i; end;
			end;			
		end
		
		else											//Алгоритм упорядочения по убыванию, ищет минимальный
		begin
			for i:=j+1 to length do
			begin 
				num_com:=num_com+1;
				if a[min]>a[i] then begin flag:=true; min:=i; end;
			end;
		end;
		
																
		if(flag=true) then
		begin 	
			num_mov:=num_mov+1;	
			a[min]:=a[min]+a[j];
			a[j]:=a[min]-a[j];
			a[min]:=a[min]-a[j];
			if(mode=2) then Debug_mode;                    //Активация тестового режима
		end;
														
	end;
	if mode=1 then                                        // Release mode
	begin
		write('Final sequence:  '); output_array(a);
		
	end;	
	
end;


procedure input_program_mode (var mode:integer);
begin
	write('Program mode (1-Release, 2-Debug):');
	read(mode);
	if (mode<>1) and (mode<>2) then write ('Wrong program mode input');
end;


procedure input_sort_type(var sort_t:integer);
begin
	write('Sort type (1-increasing sequence, 2-descending sequence):');
	read (sort_t);
	if (sort_t<>1) and (sort_t<>2) then write ('Wrong sort type input');
end;


procedure input_array(var a:vector);
begin
	write('Enter sequence size:');
	read(size);
	if(size>0) and (size<=100)  then
	begin
		write('Enter sequence: ');
		for i:=1 to size do
			read (mas[i]);
	end;
end;



procedure Number_of_movements_and_comparisons;
begin
	writeln('Number of movements:',num_mov);
	writeln('Number of comparisons:',num_com);
end;


procedure Release_mode_select_sort;
begin
	writeln;
	writeln ('Sort method 1:Selection sort');
	write('Source sequence: '); output_array(mas);
	selection_sort(mas,size);
	Number_of_movements_and_comparisons
end;


procedure Release_mode_insert_sort;
begin
	writeln;
	writeln ('Sort method 2:Insert sort');
	write('Source sequence: '); output_array(mas);
	insert_binare_sort (mas,size);
	write('Final sequence:  ');   output_array(mas);
	Number_of_movements_and_comparisons
end;


	
begin														//Начало главного тела
	input_array(mas);
	if(size>0) and (size<=100) then
	begin
		input_sort_type(sort_t);
		if(sort_t=1) or (sort_t=2) then
		begin
			input_program_mode(mode);
			if (mode=1) then
			begin
				Release_mode_select_sort;
				Release_mode_insert_sort
			end
			else 
			begin 	
				writeln; writeln ('Sort method 1:Selection sort'); 
				selection_sort(mas,size); 
				writeln ('Array sorted '); 
				writeln; writeln ('Sort method 2:Insert sort');
				insert_binare_sort(mas, size);
				writeln ('Array sorted ');
		    end;
			
		end;
	end
	else writeln('Going out of size range');
end.
