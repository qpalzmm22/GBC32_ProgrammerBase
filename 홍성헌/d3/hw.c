#include <stdio.h>

int main(void){
    int m=0, n=0, min=0, sum=0;
    scanf("%d", &m);
    scanf("%d", &n);
    if(n>10000 || m>10000 || m>n){
        return 0;
    }
    int notPrime = 0, count = 0;
    for(int i=m; i<=n; i++){
        if(i==1) continue;
        notPrime = 0;
        for(int j=2; j<i; j++){
            if(i%j == 0){
                notPrime = 1;
            }
        }
        if(notPrime == 0){
            count++;
            if(sum == 0){
                min = i;
            }
            sum+=i;
        }
    }
    if(sum == 0){
        printf("-1\n");
    } else {
        printf("%d\n%d\n", sum, min);
    }
    return 0;
}
