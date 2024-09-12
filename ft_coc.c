#include <unistd.h>
# include <stdlib.h>
# include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

#include "get_next_line.h"


#include "MLX42.h"


typedef struct s_ply
{
    char **map;
    int x ;
    int y ;
    int xexit;
    int yexit;
    mlx_t* mlx;
    mlx_image_t* wall;
    mlx_image_t* zero;
    mlx_image_t* exit;
    mlx_image_t* player;
    mlx_image_t* coin;

}t_ply;

int county_line(char *file) 
{

    int fd = open(file, O_RDONLY);
    if(fd < 0)
    {
        
    }
    char buffer[24];
    int nline = 1;
    int nbytes = 0;
    int i = 0;

    while ((nbytes = read(fd, buffer, 1)) > 0  )
    {

        if(ft_strchr(buffer))
            nline++;
        i++;
    }
    
    close(fd);
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
            ft_putstr("error inside the map");
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
                ft_putstr("error in the wall");
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
            ft_putstr("error in the first wall");
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
            ft_putstr("error in the second  wall\n");
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
           
            ft_putstr("line error\n");
            return 1;
        }
        len++;
        i++;
    }
    if(len  != j )
    {
        ft_putstr("line error in last \n");
        return 1;
    }
    if(len <= k +1)
    {
        ft_putstr("map is not rectangular\n");
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
                    ft_putstr("map invalid \n");
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

void parsse_error(t_ply *kask)
{
    int line_count = ft_count_map(kask->map);
    char **tmp = malloc( (line_count + 1) * sizeof(char *));
    int i;
    i = 0;
    while(kask->map[i])
    {
        tmp[i] = ft_strdup(kask->map[i]);
        i++;
    }
    tmp[i] = NULL;
    if(ft_error_map(kask->map) == 1 || ft_error_wall(kask->map[0]) == 1 || ft_error_wall(kask->map[i-1]) == 1 || ft_error_frwall(kask->map) == 1 ||
    ft_error_scwall(kask->map) == 1 || ft_error_line(kask->map) == 1)
    {
        ft_free(kask->map);
        ft_free(tmp);
        exit(1);
    } 
    ft_player(tmp);
    if(ft_error_chmap(tmp) == 1)
    {
        ft_free(kask->map);
        ft_free(tmp);
        exit(1);
    }
    ft_free(tmp);
}

char **ft_read_map(char *mp)
{



    int line_count = county_line(mp);
    int fd = open(mp, O_RDONLY);
    char **map = malloc((line_count + 1) * sizeof(char *));
    int i = 0;
    char *line;
    while ((line = get_next_line(fd)) != NULL) //to remove 
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
        j++;
    }
    write(1,"\n",1);
}

void ft_graph(t_ply *mpr)
{
        int i = 0;
    int j =0;
    while(mpr->map[i])
    {
        j= 0;
        while (mpr->map[i][j])
        {
            if(mpr->map[i][j] == '1')
            {
                mlx_image_to_window(mpr->mlx, mpr->wall, j*50,i*50 );

            }
            if(mpr->map[i][j] == '0')
            {
                mlx_image_to_window(mpr->mlx, mpr->zero, j*50,i*50 );

            }
            if(mpr->map[i][j] == 'P')
            {
                mlx_image_to_window(mpr->mlx, mpr->player, j*50,i*50 );
            }
            if(mpr->map[i][j] == 'C')
            {
                mlx_image_to_window(mpr->mlx, mpr->coin, j*50,i*50 );
            }
            if(mpr->map[i][j] == 'E')
            {
                mlx_image_to_window(mpr->mlx, mpr->exit, j*50,i*50 ) ;
            }
            j++;
        }
        i++;
    }
}

// #include <MLX42/MLX42.h>
void ft_hook( mlx_key_data_t keyboard ,void* param)
{
    t_ply *prm = (t_ply*)param;
	if (keyboard.key == MLX_KEY_ESCAPE )
	{
                    ft_putstr("game exit");
                    ft_free(prm->map);
                    free(prm);
                    exit(0);
    }

	if (keyboard.key ==MLX_KEY_UP && prm->map[prm->y - 1][prm->x] != '1'  && (keyboard.action == MLX_PRESS || keyboard.action == MLX_REPEAT)) 
    {
        ft_putstr("UP\n");
        prm->map[prm->y - 1][prm->x] = 'P';
        prm->map[prm->y][prm->x] = '0' ;
        prm->y = prm->y - 1;

    }        
	if (keyboard.key ==MLX_KEY_DOWN && prm->map[prm->y + 1][prm->x] != '1' && (keyboard.action == MLX_PRESS || keyboard.action == MLX_REPEAT)) 
    {
            ft_putstr("DOWN\n");
            prm->map[prm->y + 1][prm->x] = 'P';
        prm->map[prm->y][prm->x] = '0' ;
        prm->y = prm->y+1;
    }
	if (keyboard.key ==MLX_KEY_LEFT && prm->map[prm->y][prm->x - 1] != '1'  && (keyboard.action == MLX_PRESS || keyboard.action == MLX_REPEAT))
    {
        ft_putstr("LEFT\n");
        prm->map[prm->y][prm->x-1] = 'P';
        prm->map[prm->y][prm->x] = '0' ;
        prm->x = prm->x - 1;
    }
	if (keyboard.key == MLX_KEY_RIGHT && prm->map[prm->y][prm->x + 1] != '1'  && (keyboard.action == MLX_PRESS || keyboard.action == MLX_REPEAT))
    {
        ft_putstr("RIGHT\n");
        prm->map[prm->y][prm->x+1] = 'P';
        prm->map[prm->y][prm->x] = '0' ;
        prm->x = prm->x + 1;
    }

    ft_graph(prm);
}

void    ft_init(t_ply *info)
{
            int i = 0;
            int j =0;
        while(info->map[i])
        {
            j= 0;
            while (info->map[i][j])
            {
                if(info->map[i][j] == 'E')
                {
                        info->xexit = j;
                        info->yexit = i;
                    
                }
                if(info->map[i][j] == 'P')
                {
                    info->y = i;
                    info->x = j;
                }
                j++;
            }
            i++;
        }
}


int game(t_ply *mpr)
{

    t_ply x ;
    int WIDTH = ft_strlen(mpr->map[0])* 50  ;
    int HEIGHT = ft_count_map(mpr->map) * 50 ;

    mlx_t* mlx;


	// Gotta error check this stuff
	if (!(mlx = mlx_init(WIDTH, HEIGHT, "so_long", false)))
	{
        return(EXIT_FAILURE);
	}
	// mlx_image_t *image = mlx_new_image(mlx, WIDTH, HEIGHT);

    mpr->mlx = mlx;
    // mlx_image_to_window(mpr->mlx, image, 0, 0) ;
    
    mlx_texture_t* texture = mlx_load_png("./images.png");
    mpr->wall = mlx_texture_to_image(mlx, texture);
    mlx_delete_texture(texture);

    mlx_texture_t* texture1 = mlx_load_png("./player.png");
    mpr->player = mlx_texture_to_image(mlx, texture1);
        mlx_delete_texture(texture1);
    
   mlx_texture_t *texture2 = mlx_load_png("./imagesCOIN.png");
    mpr->coin = mlx_texture_to_image(mlx, texture2);
        mlx_delete_texture(texture2);
    
    mlx_texture_t *texture3 = mlx_load_png("./exit.png");
    mpr->exit = mlx_texture_to_image(mlx, texture3);
        mlx_delete_texture(texture3);
    
   mlx_texture_t* texture4 = mlx_load_png("./wero.png");
        mpr->zero = mlx_texture_to_image(mlx, texture4);
        mlx_delete_texture(texture4);

	// if (!(image = mlx_new_image(mlx, WIDTH, HEIGHT )))
	// {
    // 	mlx_terminate(mlx);
    //     // free mpr->map
	// 	puts(mlx_strerror(mlx_errno));
	// 	return(EXIT_FAILURE);
	// }


  
    ft_graph(mpr);

	// mlx_image_to_window(mlx, image, 0, 0);
	mlx_key_hook(mlx, &ft_hook, mpr);
	
    
    mlx_loop(mlx);
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}




int main(int ac , char *av[]) 
{
    if(ac != 2)
    {
        ft_putstr("name of the map !!");
        exit(1);
    }
    int i = 0;
    while(av[1][i])
            i++;
    int j = 0;
        while(av[1][i])
        {
            if(av[1][i] =='r' )
            {
                i--;
                if(av[1][i] =='e')
                    i--;
                if(av[1][i] == 'b')
                    i--;
                if(av[1][i] == '.')
                    i--;
            }
            else
                exit(1);
        }

    
    t_ply *cortab = malloc(sizeof(t_ply));
    
    char **map = ft_read_map(av[1]);
    cortab->map = map;
    ft_init(cortab);
    parsse_error(cortab);


    game(cortab);

    ft_free(map);
    free(cortab);
    // close (fd);
}