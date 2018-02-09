#include "Entity/Entity.h"
#include "Entity/EntityArrow.h"
#include "Entity/EntityXPOrb.h"
#include "Entity/EntityLivingBase.h"
#include "Entity/EntityItem.h"
#include "Entity/EntityLiving.h"
#include "Entity/EntityPlayer.h"

namespace MINE_CRAFT
{

RTTI_IMPLEMENT_BASE(MC_Entity, ENTITY_CLASS_ENTITY)
RTTI_IMPLEMENT(EntityArrow, ENTITY_CLASS_ARROW, MC_Entity)
RTTI_IMPLEMENT(EntityItem, ENTITY_CLASS_ITEM, MC_Entity)
RTTI_IMPLEMENT(EntityXPOrb, ENTITY_CLASS_XPORB, MC_Entity)
RTTI_IMPLEMENT(EntityLivingBase, ENTITY_CLASS_LIVING_BASE, MC_Entity)
RTTI_IMPLEMENT(EntityLiving, ENTITY_CLASS_LIVING, EntityLivingBase)
RTTI_IMPLEMENT(EntityPlayer, ENTITY_CLASS_PLAYER, EntityLivingBase)

}