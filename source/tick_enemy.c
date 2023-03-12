static bool	tick_enemy_base(t_object *enmy, void *param);

void	tick_enemy_easy(t_object *enmy, void *param)
{
	t_game	*game;

	game = param;
	if (!tick_enemy_base(enmy, param))
		return ;
	if (!enemy_move(enmy, game))
		enmy->dir = dir_invert(enmy->dir);
}

void	tick_enemy_hard(t_object *enmy, void *param)
{
	tick_enemy_base(enmy, param);
}

static bool	tick_enemy_base(t_object *enmy, void *param)
{
	t_game		*game;
	t_object	**other;

	tick_default(enmy, param);
	game = param;
	return (tick_move(enmy, game));
}
