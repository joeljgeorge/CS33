#include <stdio.h>
#include <limits.h>

int saturating_add(int x, int y)
{
	int sum = x + y;//sum of x + y
	int sum_sign = sum >> 31;//smearing sum
	int x_sign = x >> 31;//smearing sign of x
	int y_sign = y >> 31;//smearing sign of y
	int same_sign = x_sign ^ sum_sign;//returns 0000 if sum_sign and x_sign are equal, returns 1111 if not
	int value = x_sign ^ 0x7FFFFFFF;//if sign of x is negative, sets r_value to T_MIN; if sign is positive, sets r_value to T_MAX 
	int r_value = (same_sign & (value)) | (~same_sign & sum);//if same_sign is 1111 (two signs are different), then r_value will equal value; otherwise, r_value will equal 0

	return (((x_sign ^ y_sign) & sum) | (~(x_sign ^ y_sign) & r_value));//checks if signs are the same; if they are, returns sum; otherwise, returns r_value

}

// int main(void){//remove this
// 	int x = INT_MAX;
// 	int y = -1;

// 	if(saturating_add(x, y) == INT_MAX){
// 		printf("worked!");
// 	}
// 	else if(saturating_add(x, y) == INT_MIN){
// 		printf("worked negative!");
// 	}
// 	else{
// 		printf("failed...");
// 	}
// 	return 0;
// }