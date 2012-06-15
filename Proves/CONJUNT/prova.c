typedef struct {
	double aresta;
	int centre;
	int perimetre;
} quadrat;

int main(int a, float b){
	int x, y;
	char end;
	
	while(x<100){
		for(y=0; y<x; y++){
			y = 2;
			if (y>=23) {
				if(y>5){
					x = x + 1;
				}else{
					x = x + 2;
				}
				y = 0;
			}
			x = 0;
		}
		end = 't';
	}
	end = 'f';
	
	return x;
}
