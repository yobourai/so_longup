#include <unistd.h>
# include <stdlib.h>
# include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

#include "get_next_line.h"




typedef struct s_ply
{
    char **map;
    int i ;
    int j ;
}t_ply;

int county_line(int fd) 
{
    char buffer[1024] ;
    int nline = 0;
    int nbytes;
    int i=0;

    while ((nbytes = read(fd, buffer, 1)) > 0  )
    {
    
        if(ft_strchr(buffer))
            nline++;
        i++;
    }
    return nline;
}

#include <fcntl.h>
#include <unistd.h>
int ft_error_map(char **str)
{
    int i = 0;
    int j = 0;
    int res = 0;
    int coin = 0;
    int player = 0;
    int zayd = 0;
        while(str[i])
        {
            while(str[i][j])
            {
                if(str[i][j] == 'P')
                    player++;
                if(str[i][j] == 'E')
                    res++;
                if(str[i][j] == 'C')
                    coin++;
                if(str[i][j] != '1' &&str[i][j] != '0' &&str[i][j] != 'C' && str[i][j] != 'P' && str[i][j] != 'E' && str[i][j] != '\n'  )
                            zayd++;
                j++;
            }
            j = 0;
            i++;
        }
        if(res !=1 || coin < 1 || player != 1 || zayd != 0 )
        {
            printf("error inside the map");
            return 1;
        }
        return 0;

}

int ft_error_wall(char *tmp)
{
    int i = 0;
        while(tmp[i])
        {
            if(tmp[i] == '1' || tmp[i] == '\n')
                   i++;
            else
            {
                printf("error in the wall");
                return 1;
            }
        
        }
    return 0;
    
}
int ft_error_frwall(char **ptr)
{
    int i =0;
    while(ptr[i])
    {
        if(ptr[i][0] != '1' && ptr[i][0] != '\n' && ptr[i][0] != '\0')
        {
            printf("error in the first wall");
            return 1;
        }
        i++;
    }
    return 0;
}
int ft_error_scwall(char **ptr)
{
    int i =0;
    int len = ft_strlen(ptr[i]);
    while(ptr[i])
    {
        len = ft_strlen(ptr[i])-1;
        if((ptr[i][len-1] != '1') && ptr[i][len-1] != '\n' && ptr[i][len-1] != '\0')
        {
            printf("error in the second  wall\n");
            return 1;
        }
        i++;
    }
    return 0;
}

int ft_error_line(char **tab)
{
    (void)tab;
    int i = 0;
    int j = ft_strlen(tab[0]) ;
    int len ;

    int k = 0;
    while(tab[k])
        k++;
    while(tab[i])
    {
        len = ft_strlen(tab[i]);
        if(len != j  && i != k-1) 
        {
           
            printf("line error\n");
            return 1;
        }
        len++;
        i++;
    }
    if(len  != j )
    {
        printf("line error in last \n");
        return 1;
    }
    if(len <= k +1)
    {
        printf("map is not rectangular\n");
        return 1;
    }
    return 0;

}

void	ft_error_vmap(char **map, int x , int y)
{

	map[x][y] = '*';

	if ((map[x][y + 1] != '1') && map[x][y + 1] != '*')
		ft_error_vmap(map,x, y+ 1);
	if (map[x][y - 1] != '1' && map[x][y - 1] != '*')
		ft_error_vmap(map, x , y- 1);
	if (map[x - 1][y] != '1' && map[x - 1][y] != '*')
		ft_error_vmap(map, x - 1, y);
	if (map[x + 1][y] != '1' && map[x + 1][y] != '*')
		ft_error_vmap(map,x+ 1, y);
}

void	ft_player(char **map)
{
	int	x=0;
	int	y=0;

	while (map[y][x])
	{
		while (map[y][x])
		{
			if (map[y][x] == 'P')
			{
				ft_error_vmap(map, y, x);
				return ;
			}
			x++;
		}
		x = 0;
		y++;
	}
}

int	ft_error_chmap(char **map)
{
	int	i=0;
	int	j=0;

	i = 0;
	j = 0;
	while (map[i])
	{
		while (map[i][j])
		{
			if (map[i][j] == 'C' || map[i][j] == 'E')
			{
                    printf("map invalid \n");
                    return (1);
            }
			j++;
		}
		j= 0;
		i++;
	}
	return (0);
}

int ft_count_map(char **map)
{
    int i = 0;
    while(map[i])
        i++;
    return i;
}
void parsse_error(char **map)
{
    int line_count = ft_count_map(map);
    char **tmp = malloc( (line_count + 1) * sizeof(char *)       );
    int i;
    i = 0;
    while(map[i])
    {
        tmp[i] = ft_strdup(map[i]);
        i++;
    }
    tmp[i] = NULL;
    // exit(0);
    if(ft_error_map(map) == 1 || ft_error_wall(map[0]) == 1 || ft_error_wall(map[i-1]) == 1 || ft_error_frwall(map) == 1 ||
    ft_error_scwall(map) == 1 || ft_error_line(map) == 1)
    {
        ft_free(map);
        exit(1);
    } 
    ft_player(tmp);
    if(ft_error_chmap(tmp) == 1)
    {
        ft_free(tmp);
        exit(1);
    }
}

char **ft_read_map(char *mp)
{
    int fd = open(mp, O_RDONLY);
    int line_count = county_line(fd);
    close(fd);
    fd = open("txt.txt", O_RDONLY);
    char **map = malloc((line_count + 1) * sizeof(char *));
    int i = 0;
    char *line;
    while ((line = get_next_line(fd)) !=NULL || line_count > i) 
    {
        
        map[i] = line;
        i++;
    }
    map[i] = NULL;
    close(fd);
    return map ;
}

void print_map(char **map)
{
    int j = 0;
    while(map[j])
    {
        printf("%s", map[j]);
        j++;
    }
}

// #include <MLX42/MLX42.h>
#include "MLX42.h"


void ft_hook( mlx_key_data_t keyboard ,void* param)
{
    t_ply *prm = (t_ply*)param;


	if (keyboard.key == MLX_KEY_ESCAPE )
	{
                    printf("gg");
                    exit(0);
    }

	if (keyboard.key ==MLX_KEY_UP) 
    {
        printf("UP\n");
    }        
	if (keyboard.key ==MLX_KEY_DOWN) 
    {
            printf("DOWN\n");
    }
	if (keyboard.key ==MLX_KEY_LEFT)
    {
        printf("LEFT\n");
    }
        
	if (keyboard.key ==MLX_KEY_RIGHT) 
    {  
        printf("RIGHT\n");
    }
}



int game(char **map)
{

    t_ply x ;
    int WIDTH = ft_strlen(map[0])* 50  - 50;
    int HEIGHT = ft_count_map(map) * 50 ;

    mlx_t* mlx;

	// Gotta error check this stuff
	if (!(mlx = mlx_init(WIDTH, HEIGHT, "so_long", false)))
	{
		puts(mlx_strerror(mlx_errno));
        // free map
        return(EXIT_FAILURE);
	}
		// mlx_close_window(mlx);  
    mlx_texture_t* texture = mlx_load_png("./images.png");
    mlx_image_t* wall = mlx_texture_to_image(mlx, texture);
        mlx_delete_texture(texture);
    mlx_texture_t* textureplyr = mlx_load_png("./player.png");
    mlx_image_t* player = mlx_texture_to_image(mlx, textureplyr);
        mlx_delete_texture(textureplyr);
    
    mlx_texture_t* texturecoin = mlx_load_png("./imagesCOIN.png");
    mlx_image_t* coin = mlx_texture_to_image(mlx, texturecoin);
        mlx_delete_texture(texturecoin);
    
    mlx_texture_t* textureexit = mlx_load_png("./exit.png");
    mlx_image_t* exit = mlx_texture_to_image(mlx, textureexit);
        mlx_delete_texture(textureexit);
    
    mlx_texture_t* texturezero = mlx_load_png("./wero.png");
    mlx_image_t* zero = mlx_texture_to_image(mlx, texturezero);
        mlx_delete_texture(texturezero);

	// if (!(image = mlx_new_image(mlx, WIDTH, HEIGHT )))
	// {
    // 	mlx_terminate(mlx);
    //     // free map
	// 	puts(mlx_strerror(mlx_errno));
	// 	return(EXIT_FAILURE);
	// }

    int i = 0;
    int j =0;
    x.map = map;
        while(map[i])
        {
            j= 0;
            while (map[i][j])
            {
                if(map[i][j] == '1')
                {
                    if (mlx_image_to_window(mlx, wall, j*50,i*50 ) == -1)
                    {
                        mlx_close_window(mlx);
                        puts(mlx_strerror(mlx_errno));
                        return(EXIT_FAILURE);
                    }

                }
                if(map[i][j] == '0')
                {
                    if (mlx_image_to_window(mlx, zero, j*50,i*50 ) == -1)
                    {
                        mlx_close_window(mlx);
                        puts(mlx_strerror(mlx_errno));
                        return(EXIT_FAILURE);
                    }

                }
                if(map[i][j] == 'P')
                {
                    x.i = i;
                    x.j = j;
                    if (mlx_image_to_window(mlx, player, j*50,i*50 ) == -1)
                    {
                        mlx_close_window(mlx);
                        puts(mlx_strerror(mlx_errno));
                        return(EXIT_FAILURE);
                    }

                }
                if(map[i][j] == 'C')
                {
                    if (mlx_image_to_window(mlx, coin, j*50,i*50 ) == -1)
                    {
                            mlx_close_window(mlx);
                            puts(mlx_strerror(mlx_errno));
                            return(EXIT_FAILURE);
                    }
                }
                if(map[i][j] == 'E')
                {
                    if (mlx_image_to_window(mlx, exit, j*50,i*50 ) == -1)
                    {
                        mlx_close_window(mlx);
                        puts(mlx_strerror(mlx_errno));
                        return(EXIT_FAILURE);
                    }
                }
                j++;
            }
            i++;
        }
    printf("\nmap\n");
     print_map(x.map);
    printf("\nI = %d\n",x.i);
    printf("J = %d\n",x.j);

	
	mlx_key_hook(mlx, &ft_hook, &x);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}




int main(int ac , char *av[]) 
{

    (void)ac ;
    char **map = ft_read_map(av[1]);  
    parsse_error(map);
     print_map(map);
    game(map);
    ft_free(map);
    // close (fd);
}