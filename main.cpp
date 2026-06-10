#include "struct.h"
#include "program.h"

int main() {
    System sys;
    Start(sys);
    while(true){
        if(Login(sys)){
            Systems(sys); 
        } 
        else break;
    }
    return 0;
}