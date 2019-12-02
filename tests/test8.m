start
string a = "Succesfully chained function calls!\n";
string b = "Failed to chain function calls\n";

function func1(number n) {
	return n + n;
};

function func2(number m) {
	return m * m;
};

number chain1 = func1(func2(10));
number chain2 = func2(func1(10));

if ( (chain1 == 200) && (chain2 == 400)) {
	print(a);
} else {
	print(b);
}
end