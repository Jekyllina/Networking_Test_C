#include "bomberman.h"

int32_t move_on_level(level_t *level, movable_t *movable, const float delta_x, const float delta_y)
{
    float new_x = movable->x + delta_x;
    float new_y = movable->y + delta_y;

    if(new_x < 0)
        new_x = 0;
    else if(new_x + movable->width >= level->cols * level->cell_size)
        new_x = (level->cols * level->cell_size) - movable->width;

    if(new_y < 0)
        new_y = 0;
    else if(new_y + movable->height >= level->rows * level->cell_size)
        new_y = (level->rows * level->cell_size) - movable->height;

    int32_t cell = -1;

    //moving right
    if(new_x > movable->x)
    {
        uint32_t cellX = (new_x + movable->width - 1) / level->cell_size;  //check the cell where i'm moving on
        uint32_t cellY = (movable->y + movable->height - 1) / level->cell_size;  //check on the feets if i can move

        cell = level_cell(level, cellX, cellY);

        if(cell && BLOCK_MASK_UNWALKABLE)
        {
            movable->x = cellX * level->cell_size - movable->width;
        }
        else
        {
            cellY = movable->y / level->cell_size;  //check on the neck if i can move

            cell = level_cell(level, cellX, cellY);

            if(cell && BLOCK_MASK_UNWALKABLE)
            {
                movable->x = cellX * level->cell_size - movable->width;
            }
            else
            {
                movable->x = new_x;
            }
        }
    }    
    else if(new_x < movable->x)  //moving left
    {
        uint32_t cellX = new_x / level->cell_size;  //check the cell where i'm moving on
        uint32_t cellY = (movable->y + movable->height - 1) / level->cell_size;  //check on the feets if i can move

        cell = level_cell(level, cellX, cellY);

        if(cell && BLOCK_MASK_UNWALKABLE)
        {
            movable->x = cellX * level->cell_size + level->cell_size;
        }
        else
        {
            cellY = movable->y / level->cell_size;  //check on the neck if i can move

            cell = level_cell(level, cellX, cellY);

            if(cell && BLOCK_MASK_UNWALKABLE)
            {
                movable->x = cellX * level->cell_size + level->cell_size;
            }
            else
            {
                movable->x = new_x;
            }
        }
    }
    else if(new_y < movable->y)  //moving up
    {
        uint32_t cellX = movable->x / level->cell_size;  //check left up
        uint32_t cellY = new_y / level->cell_size;  

        cell = level_cell(level, cellX, cellY);

        if(cell && BLOCK_MASK_UNWALKABLE)
        {
            movable->y = cellY * level->cell_size + level->cell_size;            
        }
        else
        {
            cellX = (movable->x + movable->width - 1) / level->cell_size;  //check right up

            cell = level_cell(level, cellX, cellY);

            if(cell && BLOCK_MASK_UNWALKABLE)
            {
                movable->y = cellY * level->cell_size + level->cell_size; 
            }
            else
            {
                movable->y = new_y;
            }
        }
    }
    else if(new_y > movable->y)  //moving down
    {      
        uint32_t cellX = movable->x / level->cell_size;  //check left down 
        uint32_t cellY = (movable->y + movable->height) / level->cell_size;  

        cell = level_cell(level, cellX, cellY);

        if(cell && BLOCK_MASK_UNWALKABLE)
        {
            movable->y = (cellY * level->cell_size) - movable->height;            
        }
        else
        {
            cellX = (movable->x + movable->width - 1) / level->cell_size;  //check right down

            cell = level_cell(level, cellX, cellY);

            if(cell && BLOCK_MASK_UNWALKABLE)
            {
                movable->y = (cellY * level->cell_size) - movable->height; 
            }
            else
            {
                movable->y = new_y;
            }
        }
    }
    
    return cell;
}