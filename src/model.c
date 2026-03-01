#include <stdio.h>
#include <stdlib.h>

#include "../include/model.h"

void load_model(model *m, char *file) {
	FILE *model_file = fopen(file, "r");

	m->vcap = 128;
	m->vcount = 1;
	m->fcap = 2;
	m->fcount = 0;
	m->vertices = malloc((m->vcap) * sizeof(vec3));
	m->transformed_vertices = malloc((m->vcap) * sizeof(vec3));
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
				m->vertices = realloc(m->vertices, (m->vcap) * sizeof(vec3));
				m->transformed_vertices = realloc(m->transformed_vertices, (m->vcap) * sizeof(vec3));
				if (m->vertices == NULL || m->transformed_vertices == NULL) {
					fprintf(stderr, "Vertex array reallocation failed.\n");
					exit(1);
				}
			}
			sscanf(buffer, "v %f %f %f", &x, &y, &z);
			(m->vertices)[m->vcount - 1] = (vec3){x, y, z};
			(m->transformed_vertices)[m->vcount - 1] = (vec3){x, y, z};
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

void rotate_transform(model *m, float c, float b, float a) {
	for (int i = 0; i < m->vcount; i++) {
		(m->transformed_vertices)[i] = vrot3((m->vertices)[i], c, b, a);
	}
}

void perspective_transform(model *m) {
	for (int i = 0; i < m->vcount; i++) {
		(m->transformed_vertices)[i] = scale((m->transformed_vertices)[i], 1 / (1 - (m->transformed_vertices)[i].z / 4));
	}
}

void viewport_transform(fbuf *buf, model *m) {
	float x, y, z;
	for (int i = 0; i < m->vcount; i++) {
		x = (m->transformed_vertices)[i].x;
		y = (m->transformed_vertices)[i].y;
		z = (m->transformed_vertices)[i].z;
		(m->transformed_vertices)[i] = (vec3){
			((x + 1) * buf->width) / 2,
			((1 - y) * buf->height) / 2,
			((z + 1) * 255) / 2 + 1.0f
		};
	}
}

void close_model(model *m) {
	free(m->vertices);
	free(m->transformed_vertices);
	for (int i = 0; i < m->fcount; i++) {
		free((m->faces)[i]);
	}
	free(m->faces);
}
