program practicum_3;
type list=^elem;
	elem = record sym:char; next:list end;
type chain=^T;
	T=record number:integer; link:chain; letter:list end;

var q:list; correct_input:boolean; r:chain; i,let_num:integer;
	storage:array [1..6] of chain;
	
function comparison_of_words (w1:list; w2:list ):byte;   //0 если w1=w2 1 если w1>w2 2 если w1<w2
begin
	comparison_of_words:=0;
	while w1<>nil do
	begin
		if ord(w1^.sym)>ord(w2^.sym) then
		begin
			comparison_of_words:=1;
			break
		end
		else if ord(w1^.sym)<ord(w2^.sym) then
		begin
			comparison_of_words:=2;
			break
		end;
		w1:=w1^.next;
		w2:=w2^.next;
	end;
end;

procedure correct_list(s:list);
var count:integer; var p:boolean;
begin
	p:=true;
	if s= nil then 
	begin
		correct_input:=false;
		write('Void input.');
	end
	else
	begin
		count:=0;
		while s<>nil do 
		begin
			if s^.sym=',' then 
			begin
				count:=0;
				if p=true then 
				begin
					writeln('Extra commas.');
					correct_input:=false;
					exit
				end
				else p:=true;
			end 
			else
			begin
				p:=false;
				count:=count+1;
				if (count>6)  then 
				begin
					writeln ('Exceeded the number of letters in a word. ');
					correct_input:=false;
					exit;
				end;
			end;
			if (s^.next=nil) and (s^.sym=',') then
			begin	 
				writeln('Extra commas.');
				correct_input:=false;
				exit;
			end;
			s:=s^.next;
			
		end;
	end
end;

procedure Build_list(var w:list);
var c:char; 
begin
	read(c);                                   ///Буду создавать список потока слов
	if c<>'.' then
	begin
		new(w);
		w^.sym:=c;		
		if (c<>',') and not ((c>='A') and (c<='Z')) then	
		begin
			writeln ('Big latin letters only. ');
			correct_input:=false;
			exit;
		end;
		Build_list(w^.next)
	end
	else w:=nil;
end; 

procedure search_word(var w,s:list);  // s- основное слова, w- образуемое
var q:list;
begin
	q:=s;
	w:=s;
	while (q^.next<> nil) and (q^.next^.sym<>',') do
	begin
		q:=q^.next;
	end;  
	if (q^.next=nil) then 
	begin
		s:=nil;
	end
	else if (q^.next^.sym=',') then 
	begin
		s:=q^.next^.next;
		dispose(q^.next);
		q^.next:=nil;
	end;
end;

procedure output_word(w:list);
begin
	if w<>nil then 
	begin
		write(w^.sym);
		output_word(w^.next)
	end
	else writeln
	
end;
procedure output_storage(el:chain);
begin
	while el<>nil do 
	begin
		while el^.number<>0 do
		begin
			el^.number:=el^.number-1;
			output_word(el^.letter);
		end;
		el:=el^.link;
	end
end;

procedure letter_number(s:list; var i:integer);
begin
	i:=0;
	while s<>nil do 
	begin
		i:=i+1;
		s:=s^.next
	end;
end;

procedure clean_list(var v:list);
begin
	if v=nil then
	else 
	begin
		clean_list(v^.next);
		dispose(v);
		v:=nil;
	end;
	 
end;

procedure past_sort(var p,s:chain); // p- вставляемый элемент в алфавитном порядке в непустой список s
var temp:chain; o:integer; done:boolean;
begin
	temp:=s;
	done:=false;
	o:=comparison_of_words(p^.letter,s^.letter); //    | 0 p=s | 1 p>s p должен быть ниже  | 2 p<s p должен быть выше |
	if o=2 then 
	begin
		p^.link:=s;
		s:=p;
	end
	else if o=0 then 
	begin
		s^.number:=s^.number+1;
		clean_list(p^.letter);
		dispose(p);
		
	end
	else
	begin
		while done<> true do 
		begin
			p^.link:=temp^.link;
			if p^.link<> nil then
			begin
				o:=comparison_of_words(p^.letter,p^.link^.letter);
				if o=0 then 
				begin
					temp^.link^.number:=temp^.link^.number+1;
					clean_list(p^.letter);
					dispose(p);
					
					done:=true;
				end
				else if o=2 then
				begin
					done:=true;
					temp^.link:=p
			    end;
			end
			else 
			begin
				temp^.link:=p;
				done:=true;
			end;
			temp:=temp^.link;
		end;
	end;
	
end;

procedure clean_storage(var storage:chain);
begin
	if storage=nil then 
	else
	begin
		clean_storage(storage^.link);
		clean_list(storage^.letter);
		dispose(storage);
		storage:=nil;
	end;
end;

begin 
	writeln('Enter a sequence of words from capital Latin letters');
	correct_input:=true;
	Build_list(q);
	correct_list(q);
	if not correct_input then write ('Please, try again.')
	else  
	begin
		for i:=1 to 6 do storage[i]:=nil; // Массив закрыт
		while q<>nil do
		begin
			new(r);
			r^.number:=1;
			search_word(r^.letter,q);
			
			r^.link:=nil;                  //в r^.letter получено слово из последовательности
			
			letter_number(r^.letter, let_num);                 //в let_num количество букв в слове 
			
			if storage[let_num]=nil then storage[let_num]:=r // Если элемент массива пустой, то в нем появляется первое звено, в котором есть слово
			else
			begin
				past_sort(r,storage[let_num]);  //Вставить элемент r в список storage[...] в алфавитном порядке
			end;
		end;
		clean_list(q);
		for i:=1 to 6 do
			output_storage(storage[i]);
		for i:=1 to 6 do
			clean_storage(storage[i]);
	end
	
end.
