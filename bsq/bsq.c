#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

typedef struct {
    int y, x, size;
} square;

int min3(int a, int b, int c)
{
    if (a <= b && a <= c) return a;
    if (b <= a && b <= c) return b;
    return c;
}

int ft_strlen(char *str)
{
    int i = 0;
    while (str[i]) i++;
    return i;
}

int main(int ac, char **av)
{
    FILE *f = ac > 1 ? fopen(av[1], "r") : stdin;
    if (!f)
        return (fprintf(stderr, "file error\n"), 1);

    int height = 0, width = 0;
    char empty = 0, obs = 0, full = 0;
    if (fscanf(f, "%d%c%c%c\n", &height, &empty, &obs, &full) != 4)
        return (fprintf(stderr, "map error\n"), 1);
    if (empty == obs || empty == full || obs == full)
        return (fprintf(stderr, "map error\n"), 1);
    
    char **map = calloc(height, sizeof(char *));
    if (!map) return (fprintf(stderr, "malloc error\n"), 1);
    for (int i = 0; i < height; i++) {
        char *line = NULL;
        size_t len = 0;
        if (getline(&line, &len, f) < 0)
            return (fprintf(stderr, "map error\n"), 1);
        int l = ft_strlen(line);
        if (l > 0 && line[l - 1] == '\n')
            line[--l] = '\0';
        if (!width) 
            width = l;
        else if (l != width)
            return (fprintf(stderr, "map error\n"), 1);
        map[i] = line;
    }
    if (f != stdin) fclose(f);

    int **db = calloc(height + 1, sizeof(int *));
    for (int i = 0; i <= height; i++)
        db[i] = calloc(width + 1, sizeof(int));
    
    square sq = {0,0,0};
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (map[i][j] == empty) {
                db[i+1][j+1] = 1 + min3(db[i][j+1], db[i+1][j], db[i][j]);
                if (sq.size < db[i+1][j+1])
                    sq = (square){i, j, db[i+1][j+1]};
            } else if (map[i][j] != obs) {
                return (fprintf(stderr, "map error\n"), 1);
            }
        }
    }
    for (int i = sq.y - sq.size + 1; i <= sq.y; i++) {
        for (int j = sq.x - sq.size + 1; j <= sq.x; j++)
            map[i][j] = full;
    }
    for (int i = 0; i < height; i++) {
        fprintf(stdout, "%s\n", map[i]);
        free(map[i]);
    }
    free(map);
    for (int i = 0; i <= height; i++)
        free(db[i]);
    free(db);
    return 0;
}
