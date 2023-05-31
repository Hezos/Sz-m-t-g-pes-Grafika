#include "model.h"

#include <stdlib.h>

void InitializeModel(Model* model)
{
    model->n_texture_vertices = 0;
    model->n_normals = 0;
    model->n_vertices = 0;
    model->vertices = NULL;
    model->normals = NULL;
    model->n_triangles = NULL;
}

void AllocateModel(Model* model)
{
    model->vertices = (Vertex*)malloc((model->n_vertices + 1) * sizeof(Vertex));
    model->normals = (Vertex*)malloc((model->n_normals + 1) * sizeof(Vertex));
    model->triangles = (Triangle*)malloc(model->n_triangles * sizeof(Triangle));
}

void FreeModel(Model* model)
{
    if (model->vertices != NULL) {
        free(model->vertices);
    }
    if (model->normals != NULL) {
        free(model->normals);
    }
    if (model->triangles != NULL) {
        free(model->triangles);
    }
    InitializeModel(model);
}
