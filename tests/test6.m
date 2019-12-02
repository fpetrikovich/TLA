start
string ifString = "In if block\n";
string elifString = "In elif block\n";
string elseString = "In else block\n";

number n = 1;
number l = 2;

if (n == 1) {
	print(ifString);
}

if (l == 0) {
	print(ifString);
} 
elif (l > n) {
	print(elifString);
}

if ( l <= n) {
	print(ifString);
}
else {
	print(elseString);
}

end