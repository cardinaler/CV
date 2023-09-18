program debug;

type FP=function(a:real):real;

function F1(x:real):real;
begin
	F1:=exp(x*ln(2));
end;

function G1(x:real):real;
begin
	G1:=2
end;

function F2(x:real):real;
begin
	F2:=x*x*x-8;
end;

function G0(x:real):real;
begin
	G0:=0
end;

function F3(x:real):real;
begin
	F3:=(-(x-1)/3)-8;
end;

function F4(x:real):real;
begin
	F4:=x*x;
end;

function F5(x:real):real;
begin
	F5:=x;
end;

procedure root(f,g:FP;eps1,a,b:real);

var c:real;
begin
	{if((f(a)-g(a))*(f(b)-g(b))>0) then 
	begin
		write('no solve');
		exit;
	end;}
	
	c:=(a+b)/2;
	while  abs(a-b)>=eps1 do
	begin
		if((f(c)-g(c))*(f(a)-g(a))<=0) then b:=c 
		else a:=c;
		c:=(a+b)/2
	end;
	writeln('When eps=', eps1:0:4 , ' we get the solution ', c:0:10)
	
end;



procedure integral(f:FP;eps1,a,b:real);
var i,n:integer; I1,I2,h:real; 
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
	until (1/3)*abs(I1-I2)<eps1 ;
	writeln('When eps=', eps1:0:4 , ' we get the solution ', I2:0:10,'.  Number of splits:',n );
	
end;


BEGIN
	///////2^x=2
	writeln('For equation 2^x=2 on the segment [0;4] with solution x=1  we get:');
	root(@F1,@G1, 0.1, 0,4);
	root(@F1,@G1, 0.01, 0,4);
	root(@F1,@G1, 0.001, 0,4);
	root(@F1,@G1, 0.0001, 0,4);
	//////////
	
	writeln;
	
	///////x^3-8=0
	writeln('For equation x^3-8=0 on the segment [-1;3] with solution x=2 we get:');
	root(@F2,@G0, 0.1, -1,3);
	root(@F2,@G0, 0.01, -1,3);
	root(@F2,@G0, 0.001, -1,3);
	root(@F2,@G0, 0.0001, -1,3);
	//////////
	
	writeln;
	
	///////(-(x-1)/3)-8=0
	writeln('For equation -(x-1)/3)-8=0 on the segment [-27;-22] with solution x=-23 we get:');
	root(@F3,@G0, 0.1, -27,-22);
	root(@F3,@G0, 0.01, -27,-22);
	root(@F3,@G0, 0.001, -27,-22);
	root(@F3,@G0, 0.0001, -27,-22);
	//////////
	
	writeln;
	writeln;
	
	///////x^2
	writeln('For a definite integral with a correct answer: 7/3=2.(3) of a function y=x^2 on a segment [1;2] , we get ');
	integral(@F4, 0.1, 1, 2);
	integral(@F4, 0.01, 1, 2);
	integral(@F4, 0.001, 1, 2);
	integral(@F4, 0.0001, 1, 2);
	////////
	
	writeln;
	
	///////x^3-8
	writeln('For a definite integral with a correct answer: -7.75 of a function y=x^3-8 on a segment [0;1] , we get ');
	integral(@F2, 0.1, 0, 1);
	integral(@F2, 0.01, 0, 1);
	integral(@F2, 0.001, 0, 1);
	integral(@F2, 0.0001, 0, 1);
	
	writeln;
	
	///////x^3-8
	writeln('For a definite integral with a correct answer: 8 of a function y=x on a segment [3;5] , we get ');
	integral(@F5, 0.1, 3, 5);
	integral(@F5, 0.01, 3, 5);
	integral(@F5, 0.001, 3, 5);
	integral(@F5, 0.0001, 3, 5);
	
END.

