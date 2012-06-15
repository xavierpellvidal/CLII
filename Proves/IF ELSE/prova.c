
float main(int a, int b, float c){
	
	int x, y;
	
	if ((x<a) || (x>b)){
		if (x == 3){
			x = 0;
		} else {
			x = a + 2;
		}
	}else{
		if ((c > b) && (c != a)){
			y = 0;
		} else {
			y = a + 2;
		}
	}
	
	c = y;
	

}
