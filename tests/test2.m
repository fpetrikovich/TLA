start
number x=0;
number y=1;
number z;
number succ=5;
number loop=0;
string space=" ";
string enter="\n";
string fib = "Fibonacci series: ";
print(fib);
calculate{
	z=x+y;
	print(z);
	print(space);
	x=y;
	y=z;
	loop++;
} while (loop<=succ);
print(enter);
end 
