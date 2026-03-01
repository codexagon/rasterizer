#include <stdio.h>
#include <stdlib.h>

#include "../include/model.h"

void load_model(model *m, char *file) {
	FILE *model_file = fopen(file, "r");

	m->vcap = 128;
	m->vcount = 1;
	m->fcap = 2;
	m->fcount = 0;
	m->vertices = malloc((m->vcap) * sizeof(vec4));
	m->transformed_vertices = malloc((m->vcap) * sizeof(vec4));
	m->faces = malloc((m->fcap) * sizeof(int *));
	for (int i = 0; i < m->fcap; i++) {
		(m->faces)[i] = malloc(3 * sizeof(int));
	}

	char buffer[256];
	float x, y, z;

	while (fgets(buffer, sizeof(buffer), model_file) != NULL) {
		if (buffer[0] == 'v') {
			if (m->vcount >= m->vcap) {
				m->vcap <<= 1;
				m->vertices = realloc(m->vertices, (m->vcap) * sizeof(vec4));
				m->transformed_vertices = realloc(m->transformed_vertices, (m->vcap) * sizeof(vec4));
				if (m->vertices == NULL || m->transformed_vertices == NULL) {
					fprintf(stderr, "Vertex array reallocation failed.\n");
					exit(1);
				}
			}
			sscanf(buffer, "v %f %f %f", &x, &y, &z);
			(m->vertices)[m->vcount - 1] = (vec4){x, y, z, 1};
			(m->transformed_vertices)[m->vcount - 1] = (vec4){x, y, z, 1};
			(m->vcount)++;
		} else if (buffer[0] == 'f') {
			if (m->fcount >= m->fcap) {
				m->fcap <<= 1;
				m->faces = realloc(m->faces, (m->fcap) * sizeof(int *));
				for (int i = m->fcap / 2; i < m->fcap; i++) {
					(m->faces)[i] = malloc(3 * sizeof(int));
				}
				if (m->faces == NULL) {
					fprintf(stderr, "Faces array reallocation failed.\n");
					exit(1);
				}
			}
			sscanf(buffer, "f %i/%*i/%*i %i/%*i/%*i %i/%*i/%*i", &(m->faces[m->fcount][0]), &(m->faces[m->fcount][1]),
			       &(m->faces[m->fcount][2]));
			(m->fcount)++;
		}
	}

	fclose(model_file);
}

void apply_transforms(model *m, mat4 *matrices, int n, mat4 viewport) {
	mat4 final = {.vals[0] = {1, 0, 0, 0}, .vals[1] = {0, 1, 0, 0}, .vals[2] = {0, 0, 1, 0}, .vals[3] = {0, 0, 0, 1}};
	for (int i = 0; i < n; i++) {
		final = mprod4(final, matrices[i]);
	}

	for (int i = 0; i < m->vcount; i++) {
		vec4 t = transform(m->vertices[i], final);
		t = scale(t, 1 / t.w);
		m->transformed_vertices[i] = transform(t, viewport);
	}
}

mat4 get_rotation_matrix(float c, float b, float a) {
	// c: x axis, b: y axis, a: z axis
	float ar = 0.01745329 * a;
	float br = 0.01745329 * b;
	float cr = 0.01745329 * c;

	mat4 rotx = {.vals[0] = {1, 0, 0, 0},
	             .vals[1] = {0, cos(cr), -sin(cr), 0},
	             .vals[2] = {0, sin(cr), cos(cr), 0},
	             .vals[3] = {0, 0, 0, 1}};
	mat4 roty = {.vals[0] = {cos(br), 0, sin(br), 0},
	             .vals[1] = {0, 1, 0, 0},
	             .vals[2] = {-sin(br), 0, cos(br), 0},
	             .vals[3] = {0, 0, 0, 1}};
	mat4 rotz = {.vals[0] = {cos(ar), -sin(ar), 0, 0},
	             .vals[1] = {sin(ar), cos(ar), 0, 0},
	             .vals[2] = {0, 0, 1, 0},
	             .vals[3] = {0, 0, 0, 1}};

	return mprod4(mprod4(rotx, roty), rotz);
}

mat4 get_scale_matrix(float k) {
	return (mat4){
	    .vals[0] = {k, 0, 0, 0},
	    .vals[1] = {0, k, 0, 0},
	    .vals[2] = {0, 0, k, 0},
	    .vals[3] = {0, 0, 0, 1},
	};
}

mat4 get_perspective_matrix(float fov) {
	return (mat4){
	    .vals[0] = {1, 0, 0, 0},
	    .vals[1] = {0, 1, 0, 0},
	    .vals[2] = {0, 0, 1, 0},
	    .vals[3] = {0, 0, -(1 / fov), 1},
	};
}

mat4 get_viewport_matrix(fbuf *buf) {
	return (mat4){
	    .vals[0] = {(float)buf->width / 2, 0, 0, (float)buf->width / 2},
	    .vals[1] = {0, -(float)buf->height / 2, 0, (float)buf->height / 2},
	    .vals[2] = {0, 0, 255.0 / 2, 255.0 / 2},
	    .vals[3] = {0, 0, 0, 1},
	};
}

void close_model(model *m) {
	free(m->vertices);
	free(m->transformed_vertices);
	for (int i = 0; i < m->fcount; i++) {
		free((m->faces)[i]);
	}
	free(m->faces);
}
