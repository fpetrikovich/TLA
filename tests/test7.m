start
string a = "Function defined and called succesfully!\n";
string b = "Error in function calling\n";

function func1(number n) {
	return n * n;	
};

if (func1(10) == 100) {
	print(a);
} else {
	print(b);
}
end