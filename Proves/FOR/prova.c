int main(int a, float b){
	int x;
	
	for(x = 0; x < b; x++){
		a = a * b + 2;
		b = a/2;
	}
	
	return x;
}
