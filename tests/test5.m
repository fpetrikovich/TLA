start
string a="Logical and relational operation test success!\n";
string b="Error in logical and relational operation!\n";
number val1=1;
number val2=0;
if (val1==1 && val2==1){
	print(b);
} 
else{
	print(a);
}
if (val1==1 && val2==0){
	print(a);
}
else{
	print(b);
}
if (val1==1 || val2==1){
	print(a);
}
else{
	print(b);
}

end 