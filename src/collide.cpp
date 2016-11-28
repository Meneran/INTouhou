#include "collide.hpp"
#include <vector>
#include <cstddef>
#include "hitbox.hpp"
#include "life.hpp"
#include "target.hpp"
#include "world.hpp"
#include "component.hpp"

Collide::Collide() {
}

/**
 * Manage the collision between bullets and ships
 * Each bullet have a target: if there is a collision
 * between a bullet and a bullet's target, the target
 * lose 1 life and the bullet is removed
 */
void Collide::run(World &world) {
  for (size_t i = 0; i < world.getBitset(TARGET).size(); ++i) {
    if (world.getBitset(TARGET)[i]) {
      if (world.getTarget(i).getTarget() == ENEMY) {
        for (size_t j = 0; j < world.getBitset(HITBOX).size(); ++j) {
          if (world.getEntityType(j) == ENEMYSHIP) {
            auto posBullet = world.getPosition(i);
            auto posShip = world.getPosition(j);

            auto hBullet = world.getHitbox(i);
            auto hEnemy = world.getHitbox(j);

            hBullet.setPosition(posBullet);
            hEnemy.setPosition(posShip);

            sf::FloatRect r1(hEnemy.x(), hEnemy.y(),
                             hEnemy.w(), hEnemy.h());
            sf::FloatRect r2(hBullet.x(), hBullet.y(),
                             hBullet.w(), hBullet.h());

            if (r1.intersects(r2)) {
              world.removeEntity(i);
              world.getLife(j).decreaseLife();
              world.modifyScore(500);

              if (world.getLife(j).getLife() < 1)
               world.removeEntity(j);
            }
          }
        }
      }
     if (world.getTarget(i).getTarget() == PLAYER) {
       for (size_t j = 0; j < world.getBitset(HITBOX).size(); ++j) {
         if (world.getEntityType(j) == PLAYERSHIP) {
           auto posBullet = world.getPosition(i);
           auto posShip = world.getPosition(j);

           auto hBullet = world.getHitbox(i);
           auto hPlayer = world.getHitbox(j);

           hBullet.setPosition(posBullet);
           hPlayer.setPosition(posShip);

           sf::FloatRect r1(hPlayer.x(), hPlayer.y(), hPlayer.w(), hPlayer.h());
           sf::FloatRect r2(hBullet.x(), hBullet.y(), hBullet.w(), hBullet.h());

           if (r1.intersects(r2)) {
             world.removeEntity(i);
             world.getLife(j).decreaseLife();
             world.modifyScore(-1000);

             if (world.getLife(j).getLife() < 1)
              world.removeEntity(j);
            }
          }
        }
      }
    }
  }
}
