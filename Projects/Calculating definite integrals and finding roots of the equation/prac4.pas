program five;
type FP=function(a:real):real;

const eps1=0.001;
const eps2=0.001;
	  eps=0.001;
var a,b,I1,I2,I3,rootA,rootB,rootC,answer:real; n,mode:integer;

function F1(x:real):real;
begin
	F1:=(1.5/(x+1))+3
end;

function F2(x:real):real;
begin
	F2:=2.5*x-9.5
end;

function F3(x:real):real;
begin
	F3:=5/x
end;

function G1(x:real):real;
begin
	G1:=x
end;

function F4(x:real):real;
begin
	F4:=x*x;
end;

function root(f,g:FP;a,b:real):real;
var c:real;
begin
	c:=(a+b)/2;
	while  abs(a-b)>=eps1 do
	begin
		if((f(c)-g(c))*(f(a)-g(a))<=0) then b:=c 
		else a:=c;
		c:=(a+b)/2
	end;
	root:=c;
end;

function integral(f:FP;a,b:real):real;
var i:integer; I1,I2,h:real; 
begin
	n:=2;
	I2:=0;
	h:=(b-a)/n;
	for i:=0 to n-1 do
		I2:=I2+h*f(a+(i+0.5)*h);
	repeat  
	begin
		I1:=I2;
		I2:=0;
		n:=2*n;
		h:=(b-a)/n;
		for i:=0 to n-1 do 
		begin
			I2:=I2+h*f(a+(i+0.5)*h);
		end;	
	end;
	until (1/3)*abs(I1-I2)<eps2; 
	integral:=I2;
	
end;

//procedure debug_root


begin
	writeln('Select operating mode: ');
	writeln('1-Main mode ');
	writeln('2-Debug mode');
	read(mode);
	if (mode<>1) and (mode<>2) then
	begin
		write('Only 1 or 2. Please try again.');
		exit;
	end;
	if mode=1 then
	begin
		write('Functions F1,F2 intersect at a point with an abscissa: x=');
		rootA:=root(@F1,@F2,4,6);
		writeln(rootA:0:10);
		
		write('Functions F1,F3 intersect at a point with an abscissa: x=');
		rootB:=root(@F1,@F3,0.5,2);
		writeln(rootB:0:10);
		
		write('Functions F2,F3 intersect at a point with an abscissa: x=');
		rootC:=root(@F2,@F3,4,6);
		writeln(rootC:0:10);
		
		write('Area BAEO:');
		I1:=integral(@F1, rootB,rootA);
		writeln(I1:0:10);
		
		write('Area BDGC:');
		I2:=integral(@F3, rootB,rootC);
		writeln(I2:0:10);
		
		write('Area CGEA:');
		I3:=integral(@F2, rootC,rootA);
		writeln(I3:0:10);
		
		answer:=I1-I2-I3;
		writeln('Area ABC=(Area BAEO)-(Area BDGC)-(Area CGEA)=',answer:0:10);
		writeln('Correct answer: 5.08777');
		write('Difference: ', abs(answer-5.08777):0:5,'    ');
		write('eps=',eps:0:3);
		
		
	end
	else 
	begin
		writeln('           Equation solution');
		write('Enter the left point of the segment boundary:');
		read(a);
		write('Enter the right point of the segment boundary:');
		read(b);
		rootA:=root(@G1,@F4, a,b);
		write('When eps=', eps1:0:4 , ' we get the solution  ');
		writeln(rootA:0:5);
		
		writeln;
		
		writeln('           Integral calculation');
		write('Enter the left point of the segment boundary:');
		read(a);
		write('Enter the right point of the segment boundary:');
		read(b);
		I1:=integral(@F4,a,b);
		write('When eps=', eps2:0:4 , ' we get ');
		write(I1:0:5,'  Number of partitions:',n);
		
		
	end;


	
end.

