#include <stdio.h>
int main(int argc, char const *argv[]) {
    int N,users[100][100],conn,i;
    printf("Enter the no. of users: \n");
    scanf("%d\n",&N );
    printf("Enter the no. of connections: \n");
    scanf("%d\n",&conn );
    int t1,t2;
    for(i=0;i<conn;i++){
        printf("Enter the start node and end node in the connection %d: \n",i+1);
        scanf("%d %d\n", &t1,&t2);
        int x=0;
        while(users[t1-1][x]!='\0') x++;
        users[t1-1][x]=t2;
        x=0;
        while(users[t2-1][x]!='\0') x++;
        users[t2-1][x]=t1;
    }
    //Remove duplicate entries
    int a;
    for(a=0;a<N;a++){
        if(users[a][0]!='\0') {
            int x=0;
            while(users[a][x]!='\0') 
            x++;
            int i,j,k;
            for (i = 0; i < x; i++) {
                for (j = i + 1; j < x;) {
                    if (users[a][j] == users[a][i]) {
                        for (k = j; k < x; k++) {
                            users[a][k] = users[a][k + 1];
                        }
                        x--;
                    } else
                    j++;
                }
            }
        }
    }
    //Output
    printf("The friend list of all users. \n");
    for(i=0;i<N;i++){
        printf("%d->",i+1);
        if(users[i][0]=='\0')
            printf("%d\n",0);
        else{
            int x=0;
            while(users[i][x]!='\0'){
            printf("%d ",users[i][x]);
            x++;
            }
        printf("\n");
        }
    }

    return 0;
}
