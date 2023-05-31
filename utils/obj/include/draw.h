#ifndef OBJ_DRAW_H
#define OBJ_DRAW_H

#include "model.h"

/**
 * Draw the model.
 */
void draw_model(const Model* model, float xOffset, float yOffset, float zOffset);

/**
 * Draw the triangles of the model.
 */
void draw_triangles(const Model* model, float xOffset, float yOffset, float zOffset);

#endif /* OBJ_DRAW_H */
