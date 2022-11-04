#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <stdint.h>
#include "dl.hpp"
#include "util.hpp"

#define EM_PLAYER 0
#define COUNTOF_EM 1

/**
 * struct box - Box
 * @tl: Top-left of box
 * @br: Bottom-right of box
 */
struct box {
	v2 tl;
	v2 br;
};

/**
 * struct anim - An animation 
 * @dt: The time between sprites 
 * @start: First sprite in animation 
 * @end: Last sprite in animation 
 * 
 * Animation iterates through each sprite.
 * The sprites in animation will be consecutive.
 */
struct anim {
	float dt;
	uint8_t start;
	uint8_t end;
};

/**
 * struct entity_meta - Includes constant info for entity 
 * @mask: Collision mask
 * @def_anim: Default animation 
 */
struct entity_meta {
	box mask;
	const anim *def_anim;
};

/**
 * @node: Used to point to next entity
 * @meta: Pointer to common entites of this type
 * @v2i: Spawn position
 *
 * @pos: Current position in tiles
 * @vel: Current velocity in tiles per second
 * @offset: cached absolute position of collision mask 
 * @mask: collison mask 
 *
 * @anim_time: Time till next animation frame
 * @cur_anim: Animation
 */
struct entity {
	/*misc*/
	dl_head node;
	const entity_meta *meta;
	v2i spawn;

	/*physics*/
	v2 pos;
	v2 vel;
	v2 offset;

	/*animation*/
	const anim *cur_anim;
	float anim_time;
	uint8_t sprite;	
};

/** 
 * g_dt - Frame delta in seconds
 * g_entites - Linked list of entities
 * g_entity_metas - Metadata of all entity
 * g_key_down - states for key down presses
 */
extern float g_dt;
extern dl_head g_entities;
extern const entity_meta g_entity_metas[COUNTOF_EM];
extern int g_key_down[256];

/**
 * create_entity() - Creates an entity
 * @tx: Spawn x-pos
 * @ty: Spawn y-pos
 *
 * Return: The entity
 */
entity *create_entity(int tx, int ty);

/**
 * start_entities() - Setup entity system
 * This is a temporary function that will be deleted once we are able
 * to create entities throught the editor.
*/
void start_entities(void);

/**
 * update_entities - Updates entities 
 */
void update_entities(void);

/**
 * end_entities - End entity system 
*/
void end_entities(void);

/**
 * destroy_entity() - Destroys an entity
 * @e: Entity to be destroyed
 */
void destroy_entity(entity *e);

/**
 * clear_entities() - Destroy all entities
 */
void clear_entities(void);

#endif
