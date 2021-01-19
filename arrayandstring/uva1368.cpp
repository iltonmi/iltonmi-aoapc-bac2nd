#include <iostream>
#include <cstring>

const int M = 60, N = 1000;
char a[M][N];
char res[N];
int m, n;
char dna[4] = {'A', 'C', 'G', 'T'};

int index(char ch) {
    for(int i = 0; i < 4; i++)
        if(ch == dna[i]) return i;
    return -1; 
}

int main() {
    int T; scanf("%d", &T);
    while(T--) {
        scanf("%d%d", &m, &n);
        int map[4];
        for(int i = 0; i < m; i++) scanf("%s", a[i]);
        memset(res, 0, sizeof res);
        int dist = 0;
        for(int j = 0; j < n; j++) {
            memset(map, 0, sizeof map);
            for(int i = 0; i < m; i++) {
                map[index(a[i][j])]++;
            }
            int maxi = 0;
            for(int i = 0; i < 4; i++)
                if(map[i] > map[maxi]) maxi = i;
            res[j] = dna[maxi];
            dist += m -map[maxi];
        }
        printf("%s\n%d\n", res, dist);
    }    
    return 0;
}
