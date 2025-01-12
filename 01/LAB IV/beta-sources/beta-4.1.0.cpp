#include "../headers/config.h"

/*
    * This program translates an entry in 
    * Arabic numerals into Roman.   
    * Possible translation radius is from 1 to 3999
    */


int main(){
    char rome_digits[] = "IVXLCDM", ans[20];
    int index = 0, input_num;
    
    cin >> input_num;
    
    while (input_num){
        int ch = input_num % 10;
        char tmp[20] = "", sb[1];
        if (ch == 9){
            sb[0] = rome_digits[index]; 
            strncat(tmp, sb, 1);
            sb[0] = rome_digits[index + 2];
            strncat(tmp, sb, 1);
        } else
        if (ch == 4) {
            sb[0] = rome_digits[index]; 
            strncat(tmp, sb, 1);
            sb[0] = rome_digits[index + 1];
            strncat(tmp, sb, 1);
        } else {
            if (ch > 4){
                ch -= 5;
                sb[0] = rome_digits[index + 1];
                strncat(tmp, sb, 1);
            }
            while (ch--){
                sb[0] = rome_digits[index]; 
                strncat(tmp, sb, 1);
            }
        }
        strcat(tmp, ans);
        strcpy(ans, tmp);
        input_num /= 10;
        index += 2;
    }
    
 cout << ans;
 
 return 0;
}