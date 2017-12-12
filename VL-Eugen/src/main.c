#include "../src/speicherverwaltung.c"
#include "../src/display.c"
#include <ledbar.h>
int main(){
		int* ptr = (int*)cm_malloc(sizeof(int));
		*ptr = 13;
		printf("%d\n", *ptr);
		if(cm_free(ptr)==NULL){
			printf("Free hat nicht geklappt");
		}else{
			printf("Free hat geklappt.");	
		}
		int* ptr2 = (int*)cm_malloc(sizeof(int));
		*ptr2 = 31;
		printf("%d\n", *ptr2);
		return 0;
}
