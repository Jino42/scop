#ifndef C_RBO_H
# define C_RBO_H

typedef struct		s_rbo
{
	unsigned int	framebuffer;
	unsigned int	texture_color_buffer;
	unsigned int	rbo;
}					t_rbo;

t_rbo			*rbo_construct(unsigned int width, unsigned int height);
void			*rbo_destruct(t_rbo **rbo);

#endif
