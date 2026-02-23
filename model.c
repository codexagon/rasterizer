#include <stdio.h>
#include <stdlib.h>

#include "model.h"

void load_model(model *m, char *file, int w, int h) {
	FILE *model_file = fopen(file, "r");

	m->vcap = 128;
	m->vcount = 1;
	m->fcap = 2;
	m->fcount = 0;
	m->vertices = malloc((m->vcap) * sizeof(vertex));
	m->faces = malloc((m->fcap) * sizeof(int *));
	for (int i = 0; i < m->fcap; i++) {
		(m->faces)[i] = malloc(3 * sizeof(int));
	}

	char buffer[256];
	float x, y;

	while (fgets(buffer, sizeof(buffer), model_file) != NULL) {
		if (buffer[0] == 'v') {
			if (m->vcount >= m->vcap) {
				m->vcap <<= 1;
				m->vertices = realloc(m->vertices, (m->vcap) * sizeof(vertex));
				if (m->vertices == NULL) {
					fprintf(stderr, "Vertex array reallocation failed.\n");
					exit(1);
				}
			}
			sscanf(buffer, "v %f %f %*f", &x, &y);
			(m->vertices)[m->vcount - 1] = (vertex){(int)((x + 1) * w) >> 1, (int)((1 - y) * h) >> 1};
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

void render_model(fbuf *buf, model *m) {
	color rc;

	for (int i = 0; i < m->fcount; i++) {
		rc.r = rand() % (255 - 0 + 1) + 0;
		rc.g = rand() % (255 - 0 + 1) + 0;
		rc.b = rand() % (255 - 0 + 1) + 0;
		vertex v1 = m->vertices[m->faces[i][0] - 1];
		vertex v2 = m->vertices[m->faces[i][1] - 1];
		vertex v3 = m->vertices[m->faces[i][2] - 1];

		int facing_towards = ((v3.x - v1.x) * (v2.y - v1.y)) - ((v2.x - v1.x) * (v3.y - v1.y));
		if (facing_towards < 0) {
			continue;
		}
		draw_triangle(buf, v1, v2, v3, rc);
	}
	render(buf);
}

void close_model(model *m) {
	free(m->vertices);
	for (int i = 0; i < m->fcount; i++) {
		free((m->faces)[i]);
	}
	free(m->faces);
}
