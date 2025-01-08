#ifndef GRAPH_H
#define GRAPH_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <GL/glew.h>
#include <GL/glut.h>
#include <GL/freeglut.h>
#include <math.h>
#include "common_def.h"
#include "char_string.h"
#include "draw.h"
typedef struct graph graph;
graph *p_graph = NULL;
#define MODULE_NAME graph
#define MODULE_STRUCT graph_struct.h
#define MODULE_INIT graph_init.h
#define MODULE_INIT_VAR graph_init_var.h
#include "module.h"
FUNCTION_INLINE void FUNC(draw)();
FUNCTION_INLINE int FUNC(render_buffer)(T *p)
{
	int is_set = 0;
	GLenum status = 0;
	size_t width = p_graph->width * 4;
	size_t height = p_graph->height * 4;
	if (p)
	{
		status = glewInit();
		if (status == GLEW_OK)
		{
			printf("glew OK\n");
			printf("GLEW version: %s\n",
					glewGetString(GLEW_VERSION));
		}
		if (GLEW_ARB_framebuffer_object)
		{
			printf("GLEW_ARB_framebuffer_object supported\n");
		}
		glGenFramebuffers(1,
				&p->fbo_id);
		glBindFramebuffer(GL_FRAMEBUFFER,
				p->fbo_id);
		glGenRenderbuffers(1,
				&p->rb_id);
		glBindRenderbuffer(GL_RENDERBUFFER,
				p->rb_id);
		glRenderbufferStorage(GL_RENDERBUFFER,
				GL_RGB,
				width,
				height);
		glFramebufferRenderbuffer(GL_FRAMEBUFFER,
				GL_COLOR_ATTACHMENT0,
				GL_RENDERBUFFER,
				p->rb_id);
		status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
		printf("FramebufferStatus: %d\n",
				status);
		if (status == GL_FRAMEBUFFER_COMPLETE)
		{
			printf("OK\n");
			is_set = 1;
		}
	}
	return is_set;
}
FUNCTION_INLINE int FUNC(set_projection)(T *p)
{
	int is_set = 0;
	double x0 = 0;
	double x1 = 0;
	double y0 = 0;
	double y1 = 0;
	double dx = 0;
	double dy = 0;
	if (p)
	{
		dx = p->width / p->scale / 2 / p->x_scale;
		x0 = p->dx - dx;
		x1 = p->dx + dx;
		dy = p->height / p->scale / 2 / p->y_scale;
		y0 = p->dy - dy;
		y1 = p->dy + dy;
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(x0,
				x1,
				y0,
				y1,
				-1,
				1); 
		glMatrixMode(GL_MODELVIEW);
	}
	return is_set;
}
FUNCTION_INLINE void FUNC(key)(unsigned char key,
		int x,
		int y)
{
	if (key == 'q')
	{
		glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_CONTINUE_EXECUTION);
		glutLeaveMainLoop();
	}
	else if (key == '4')
	{
		p_graph->dx -= p_graph->dx_step;
		FUNC(set_projection)(p_graph);
	}
	else if (key == '6')
	{
		p_graph->dx += p_graph->dx_step;
		FUNC(set_projection)(p_graph);
	}
	else if (key == '2')
	{
		p_graph->dy -= p_graph->dy_step;
		FUNC(set_projection)(p_graph);
	}
	else if (key == '8')
	{
		p_graph->dy += p_graph->dy_step;
		FUNC(set_projection)(p_graph);
	}
	else if (key == '-')
	{
		p_graph->x_scale /= p_graph->x_scale_step;
		p_graph->y_scale /= p_graph->y_scale_step;
		p_graph->z_scale /= p_graph->z_scale_step;
		FUNC(set_projection)(p_graph);
	}
	else if (key == '+')
	{
		p_graph->x_scale *= p_graph->x_scale_step;
		p_graph->y_scale *= p_graph->y_scale_step;
		p_graph->z_scale *= p_graph->z_scale_step;
		FUNC(set_projection)(p_graph);
	}
	else if (key == '5')
	{
		p_graph->dx = p_graph->width / p_graph->scale / 2;
		p_graph->dy = p_graph->height / p_graph->scale / 2;
		p_graph->x_scale = 1;
		p_graph->y_scale = 1;
		FUNC(set_projection)(p_graph);
	}
	else
	{
		printf("%x\n",
				key);
	}
	glutPostRedisplay();
}
FUNCTION_INLINE void FUNC(draw)()
{
	draw *draw = NULL;
	if (p_graph)
	{
		draw = p_graph->draw;
		if (draw)
		{
			draw_run(draw);
		}
	}
}
FUNCTION_INLINE void FUNC(draw_framebuffer)()
{
	draw *draw = NULL;
	char *buf = NULL;
	FILE *f = 0;
	size_t buf_size = 0;
	size_t width = p_graph->width * 4;
	size_t height = p_graph->height * 4;
	short tga_head[] = {0, 2, 0, 0, 0, 0, width, height, 24};
	if (p_graph)
	{
		draw = p_graph->draw;
		if (draw)
		{
			glBindFramebuffer(GL_FRAMEBUFFER,
					p_graph->fbo_id);
			glClearColor(0, 0, 0, 0);
			glClear(GL_COLOR_BUFFER_BIT);
			glShadeModel(GL_FLAT);
			draw_run(draw);
			glFlush();
			buf_size = width * height * 3;
			buf = malloc(buf_size);
			if (buf)
			{
				glReadPixels(0, 0,
						width, height,
						GL_RGB,
						GL_UNSIGNED_BYTE,
						buf);
				f = fopen("/home/ask/download/test.tga", "w");
				if (f)
				{
					fwrite(&tga_head,
							sizeof(tga_head),
							1,
							f);
					fwrite(buf,
							1,
							buf_size,
							f);
					fclose(f);
				}
			}
			glBindFramebuffer(GL_FRAMEBUFFER,
					0);
		}
	}
}
FUNCTION_INLINE void FUNC(display)()
{
	glClearColor(0, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT);
	glShadeModel(GL_FLAT);
	FUNC(draw)();
	glFlush();
}
FUNCTION_INLINE int FUNC(print)(T *p)
{
	int is_set = 0;
	if (p)
	{
		printf("OpenGL version: %s\n",
				glGetString(GL_VERSION));
	}
	return is_set;
}
FUNCTION_INLINE int FUNC(start)(T *p,
		int argc,
		char *argv[])
{
	int is_set = 0;
	if (p)
	{
		/* init glut */
		glutInit(&argc, argv);
		/* set display mode */
		glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
		/* set window size */
		glutInitWindowSize(p->width,
				p->height);
		/* create window */
		glutCreateWindow(p->window_name->buf);
		FUNC(render_buffer)(p);
		FUNC(print)(p);
		glutDisplayFunc(FUNC(display));
		glutKeyboardFunc(FUNC(key));
		glViewport(0,
				0,
				p->width * 4,
				p->height * 4);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(0,
				p->width / p->scale,
				0,
				p->height / p->scale,
				-1,
				1); 
		glMatrixMode(GL_MODELVIEW);
		FUNC(draw_framebuffer)();
		glViewport(0,
				0,
				p->width / p->scale,
				p->height / p->scale);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(0,
				p->width / p->scale,
				0,
				p->height / p->scale,
				-1,
				1); 
		glMatrixMode(GL_MODELVIEW);
		glutMainLoop();
	}
	return is_set;
}
#include "module_undef.h"
#endif	/* GRAPH_H */
