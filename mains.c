#include "./include/my.h"
#include <SFML/Graphics.h>
#include <SFML/Audio.h>
#include <SFML/System.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>

int main(int ac, char **av)
{
   sfVideoMode mode = {1920, 1080, 32};
     sfRenderWindow* window;
     sfTexture* texture;
     sfVector2f vector = {800, 460};
     sfVector2f ennemy_ini = {1050, 1150};
     sfVector2f ennemy1_ini = {-1200, 1200};
     sfVector2f ennemy2_ini = {-100, 1600};
     sfVector2f ennemy3_ini = {1100, 1500};
     sfVector2f vector_pos;
     sfVector2i pos;
     sfClock* explosion_animation;
     sfSprite* explosion;
     sfTexture* tex_explosion;
     sfVector2f vector_explosion = {2000, 2000};
     sfVector2f pos_life = {25, 50};
     sfSprite* life;
     sfTexture* tex_life;
     sfClock* samus_animation;
     sfSprite* samus;
     sfTexture* tex_samus;
     sfSprite* lights;
     sfClock* lights_animation;
     sfTexture* tex_lights;
     sfSprite* sprite;
     //ennemy
     sfClock* ennemy_move;
     sfTexture* tex_ennemy;
     sfSprite* ennemy;
     sfClock* ennemy1_move;
     sfTexture* tex_ennemy1;
     sfSprite* ennemy1;
     sfClock* ennemy2_move;
     sfTexture* tex_ennemy2;
     sfSprite* ennemy2;
     sfClock* ennemy3_move;
     sfTexture* tex_ennemy3;
     sfSprite* ennemy3;
     //cursor
     sfTexture* tex_cursor;
     sfSprite* cursor;
     sfClock* cursor_animation;
     sfMusic* music;
     sfMusic* shoot;
     sfMusic* damage;
     sfMusic* die;
     sfEvent event;
     int fd;
     int coco = 1;
     char *text = malloc(sizeof(char) * 3000);
     int speed = 0;
     int ennemy_offset = 0;
     int ennemy1_offset = 0;
     int ennemy2_offset = 0;
     int ennemy3_offset = 0;
     int trigger = 0;	
     int start_explosion = 1;

  if (ac == 2) {
    fd = open("description.txt", O_RDONLY);
    coco = read(fd,text, 3000);
    my_putstr(text);
    if (fd <= 0)
      return (84);
    return (0);
  }

  window = sfRenderWindow_create(mode,"My Prime Hunter", sfClose | sfFullscreen, NULL);
  sfRenderWindow_setFramerateLimit(window, 60);

  lights_animation = sfClock_create();
  ennemy_move = sfClock_create();
  ennemy1_move = sfClock_create();
  ennemy2_move = sfClock_create();
  ennemy3_move = sfClock_create();
  cursor_animation = sfClock_create();
  explosion_animation = sfClock_create();
  samus_animation = sfClock_create();
  
  music = sfMusic_createFromFile("./ressources/music.ogg");
  if (!music)
      return (84);
  sfMusic_setVolume(music, 30);
  sfMusic_play(music);

    texture = sfTexture_createFromFile("./ressources/level.png", NULL);
     if (!texture)
          return (84);
      sprite = sfSprite_create();
      sfSprite_setTexture(sprite, texture, sfTrue);

      tex_cursor = sfTexture_createFromFile("./ressources/cursor.png", NULL);
     if (!tex_cursor)
          return (84);
      cursor = sfSprite_create();
      sfIntRect rect_cursor;
      rect_cursor.top = 0;
      rect_cursor.left = 0;
      rect_cursor.width = 66;
      rect_cursor.height = 70;
      sfSprite_setPosition	(cursor, vector_pos);
      sfSprite_setTexture(cursor, tex_cursor, sfTrue);
      sfSprite_setTextureRect	(cursor, rect_cursor);

       tex_explosion = sfTexture_createFromFile("./ressources/explosion.png", NULL);
     if (!tex_explosion)
          return (84);
      explosion = sfSprite_create();
      sfIntRect rect_explosion;
      rect_explosion.top = 0;
      rect_explosion.left = 600;
      rect_explosion.width = 100;
      rect_explosion.height = 1000;
      sfSprite_setPosition	(explosion, vector_explosion);
      sfSprite_setTexture(explosion, tex_explosion, sfTrue);
      sfSprite_setTextureRect	(explosion, rect_explosion);

      tex_ennemy = sfTexture_createFromFile("./ressources/ennemy.png", NULL);
     if (!tex_ennemy)
          return (84);
      ennemy = sfSprite_create();
      sfSprite_setPosition	(ennemy, ennemy_ini);
      sfSprite_setTexture(ennemy, tex_ennemy, sfTrue);

      ennemy1 = sfSprite_create();
      sfSprite_setPosition	(ennemy1, ennemy1_ini);
      sfSprite_setTexture(ennemy1, tex_ennemy, sfTrue);

      ennemy2 = sfSprite_create();
      sfSprite_setPosition	(ennemy2, ennemy2_ini);
      sfSprite_setTexture(ennemy2, tex_ennemy, sfTrue);

      ennemy3 = sfSprite_create();
      sfSprite_setPosition	(ennemy3, ennemy3_ini);
      sfSprite_setTexture(ennemy3, tex_ennemy, sfTrue);


      tex_samus = sfTexture_createFromFile("./ressources/samus.png", NULL);
     if (!tex_samus)
          return (84);
      samus = sfSprite_create();
      sfIntRect rect_samus;
      rect_samus.top = 350;
      rect_samus.left = 20;
      rect_samus.width = 250;
      rect_samus.height = 250;
      sfSprite_setPosition	(samus, vector);
      sfSprite_setTexture(samus, tex_samus, sfTrue);
      sfSprite_setTextureRect(samus, rect_samus);

      tex_lights = sfTexture_createFromFile("./ressources/lights.png", NULL);
     if (!tex_lights)
          return (84);
      lights = sfSprite_create();
      sfIntRect rect;
      rect.top = 0;
      rect.left = 0;
      rect.width = 1920;
      rect.height = 1080;
      sfSprite_setTexture(lights, tex_lights, sfTrue);
      sfSprite_setTextureRect	(lights, rect);

      tex_life = sfTexture_createFromFile("./ressources/life.png", NULL);
     if (!tex_life)
          return (84);
      life = sfSprite_create();
      sfIntRect rect_life;
      rect_life.top = 0;
      rect_life.left = 0;
      rect_life.width = 250;
      rect_life.height = 100;
      sfSprite_setPosition	(life,pos_life);
      sfSprite_setTexture(life, tex_life, sfTrue);
      sfSprite_setTextureRect(life, rect_life);

      die = sfMusic_createFromFile("./ressources/die.ogg");
        if (!die)
          return (84);

      damage = sfMusic_createFromFile("./ressources/damage.ogg");
        if (!damage)
          return (84);

      shoot = sfMusic_createFromFile("./ressources/shoot.ogg");
        if (!shoot)
          return (84);

  while (sfRenderWindow_isOpen(window)) {
    if (rect_life.width <= 83)
        sfRenderWindow_close(window);

    while (sfRenderWindow_pollEvent(window, &event)) {

      if (sfMouse_isButtonPressed(sfMouseLeft)) {
        sfMusic_setVolume(shoot, 40);
        sfMusic_play(shoot);
      }

      sfRenderWindow_setMouseCursorVisible(window, 0);
      if (sfKeyboard_isKeyPressed (sfKeyEscape))
	        sfRenderWindow_close(window);

      pos = sfMouse_getPositionRenderWindow(window);
      vector_pos.x = pos.x -27;
      vector_pos.y = pos.y -37;
      sfSprite_setPosition(cursor, vector_pos);

      if (sfMouse_isButtonPressed(sfMouseLeft)) {
        if (pos.x >= ennemy_ini.x && pos.x <= ennemy_ini.x + 75 && pos.y >= ennemy_ini.y && pos.y <= ennemy_ini.y + 79) {
          start_explosion = 1;
          sfMusic_play(die);
          vector_explosion.x = ennemy_ini.x;
          vector_explosion.y = ennemy_ini.y;
          ennemy_ini.x = 1050;
          ennemy_ini.y = 1150;
          speed += 1;
          ennemy_offset = 0;
          sfSprite_setPosition(ennemy, ennemy_ini);
        }
      } 

      if (sfMouse_isButtonPressed(sfMouseLeft)) {
        if (pos.x >= ennemy1_ini.x && pos.x <= ennemy1_ini.x + 75 && pos.y >= ennemy1_ini.y && pos.y <= ennemy1_ini.y + 79) {
          start_explosion = 1;
          sfMusic_play(die);
          vector_explosion.x = ennemy1_ini.x;
          vector_explosion.y = ennemy1_ini.y;
          ennemy1_ini.x = 1050;
          ennemy1_ini.y = 1150;
          speed += 1;
          ennemy1_offset = 0;
          sfSprite_setPosition(ennemy1, ennemy1_ini);
        }
      } 

      if (sfMouse_isButtonPressed(sfMouseLeft)) {
        if (pos.x >= ennemy2_ini.x && pos.x <= ennemy2_ini.x + 75 && pos.y >= ennemy2_ini.y && pos.y <= ennemy2_ini.y + 79) {
          start_explosion = 1;
          sfMusic_play(die);
          vector_explosion.x = ennemy2_ini.x;
          vector_explosion.y = ennemy2_ini.y;
          ennemy2_ini.x = 1050;
          ennemy2_ini.y = 1150;
          speed += 1;
          ennemy2_offset = 0;
          sfSprite_setPosition(ennemy2, ennemy2_ini);
        }
      } 

      if (sfMouse_isButtonPressed(sfMouseLeft)) {
        if (pos.x >= ennemy3_ini.x && pos.x <= ennemy3_ini.x + 75 && pos.y >= ennemy3_ini.y && pos.y <= ennemy3_ini.y + 79) {
          start_explosion = 1;
          sfMusic_play(die);
          vector_explosion.x = ennemy3_ini.x;
          vector_explosion.y = ennemy3_ini.y;
          ennemy3_ini.x = 1850;
          ennemy3_ini.y = 1150;
          speed += 1;
          ennemy3_offset = 0;
          sfSprite_setPosition(ennemy3, ennemy3_ini);
        }
      }
    }

    if (ennemy_ini.x >= 850 && ennemy_ini.x <= 1006) {
      if (trigger < 1 && trigger != -500) {
        sfMusic_play(damage);
        trigger ++;
      }
    }

    if (ennemy1_ini.x >= 850 && ennemy1_ini.x <= 1006 && ennemy1_ini.y < 600) {
      if (trigger < 1 && trigger != -500) {
        sfMusic_play(damage);
        trigger ++;
      }
    }
      
    if (ennemy2_ini.x >= 850 && ennemy2_ini.x <= 1006 && ennemy2_ini.y < 600) {
      if (trigger < 1 && trigger != -500) {
        sfMusic_play(damage);
        trigger ++;
      }
    }

    if (ennemy3_ini.x >= 850 && ennemy3_ini.x <= 1006) {
      if (trigger < 1 && trigger != -500) {
        sfMusic_play(damage);
        trigger ++;
      }
    }

    if (sfClock_getElapsedTime(lights_animation).microseconds > 350000) {
      if (rect.left >= 5760)
          rect.left = 0;
      else
          rect.left += 1920;
      sfClock_restart(lights_animation);
    }

    if (sfClock_getElapsedTime(samus_animation).microseconds > 100000) {
      if (pos.x > 960 && pos.x > 1050 && pos.y > 480) {
        //droite
        rect_samus.left = 972;
        rect_samus.top = 100;
      }
      else if (pos.x > 960 && pos.x > 1050 && pos.y < 480) {
        //diagonale droite
        rect_samus.left = 1700;
        rect_samus.top = 365;
      }
      else if (pos.x < 2820 && pos.x < 860 && pos.y > 480) {
      //gauche
        rect_samus.left = 470;
        rect_samus.top = 100;
      }
      else if (pos.x < 2820 && pos.x < 860 && pos.y < 480) {
      //diagonale gauche
        rect_samus.left = -20;
        rect_samus.top = 365;
      }
      else if (pos.y < 480 && pos.y < 480) {
      //verticale
        rect_samus.left = 510;
        rect_samus.top = 700;
      }
      sfClock_restart(samus_animation);
    }

    if (sfClock_getElapsedTime(ennemy_move).microseconds > 60000) {
      if (ennemy_offset == 10) {
        if (ennemy_ini.x > 2000) {
          trigger = 0;
          ennemy_offset = 0;
          ennemy_ini.x = 470;
          ennemy_ini.y = 85;
        }
        else {
        ennemy_ini.x += 15 + speed;
        ennemy_ini.y += 15 + speed;
        }
      }
      if (ennemy_offset < 10)
        ennemy_offset++;
      if (trigger == 1) {
        if (rect_life.width > 0) {
          rect_life.width -= 83;
          trigger = -500;
        }
      }
      sfSprite_setTextureRect	(life, rect_life);
      sfSprite_setPosition(ennemy, ennemy_ini);
      sfClock_restart(ennemy_move);
    }

    if (sfClock_getElapsedTime(ennemy1_move).microseconds > 60000) {
      if (ennemy1_offset == 10) {
        if (ennemy1_ini.x < -1300) {
          trigger = 0;
          ennemy1_offset = 0;
          ennemy1_ini.x = 1375;
          ennemy1_ini.y = 90;
        }
        else {
        ennemy1_ini.x -= 15 + speed;
        ennemy1_ini.y += 15 + speed;
        }
      }
      if (ennemy1_offset < 10)
        ennemy1_offset++;
      if (trigger == 1) {
        if (rect_life.width > 0) {
          rect_life.width -= 83;
          trigger = -500;
        }
      }
      sfSprite_setTextureRect	(life, rect_life);
      sfSprite_setPosition(ennemy1, ennemy1_ini);
      sfClock_restart(ennemy1_move);
    }

    if (sfClock_getElapsedTime(ennemy2_move).microseconds > 60000) {
      if (ennemy2_offset == 10) {
        if (ennemy2_ini.x < -900) {
          trigger = 0;
          ennemy2_offset = 0;
          ennemy2_ini.x = 1550;
          ennemy2_ini.y = 90;
        }
        else {
        ennemy2_ini.x -= 15 + speed;
        ennemy2_ini.y += 10 + speed;
        }
      }
      if (ennemy2_offset < 10)
        ennemy2_offset++;
      if (trigger == 1) {
        if (rect_life.width > 0) {
          rect_life.width -= 83;
          trigger = -500;
        }
      }
      sfSprite_setTextureRect	(life, rect_life);
      sfSprite_setPosition(ennemy2, ennemy2_ini);
      sfClock_restart(ennemy2_move);
    }
    
    if (sfClock_getElapsedTime(ennemy3_move).microseconds > 60000) {
      if (ennemy3_offset == 10) {
        if (ennemy3_ini.x > 2300) {
          trigger = 0;
          ennemy3_offset = 0;
          ennemy3_ini.x = 285;
          ennemy3_ini.y = 85;
        }
        else {
        ennemy3_ini.x += 15 + speed;
        ennemy3_ini.y += 10 + speed;
        }
      }
      if (ennemy3_offset < 10)
        ennemy3_offset++;
      if (trigger == 1) {
        if (rect_life.width > 0) {
          rect_life.width -= 83;
          trigger = -500;
        }
      }
      sfSprite_setTextureRect	(life, rect_life);
      sfSprite_setPosition(ennemy3, ennemy3_ini);
      sfClock_restart(ennemy3_move);
    }

    if (sfClock_getElapsedTime(cursor_animation).microseconds > 100000) {
      if (rect_cursor.left > 176)
        rect_cursor.left = 0;
      else
        rect_cursor.left += 66;
      sfClock_restart(cursor_animation);
      sfSprite_setTextureRect	(cursor, rect_cursor);	
    }

    if (sfClock_getElapsedTime(explosion_animation).microseconds > 100000) {
      if (start_explosion == 1) {
        if (rect_explosion.left > 600) {
          rect_explosion.left = -100;
          start_explosion = 0;
        }
        else
          rect_explosion.left += 100;
      }
      sfSprite_setPosition(explosion, vector_explosion);
      sfClock_restart(explosion_animation);
      sfSprite_setTextureRect	(explosion, rect_explosion);
    }

    sfSprite_setTextureRect(lights, rect);
    sfSprite_setTextureRect(samus, rect_samus);
    sfRenderWindow_drawSprite(window, sprite, NULL);
    sfRenderWindow_drawSprite(window, lights, NULL);
    sfRenderWindow_drawSprite(window, samus, NULL);
    sfRenderWindow_drawSprite(window, ennemy, NULL);
    sfRenderWindow_drawSprite(window, ennemy1, NULL);
    sfRenderWindow_drawSprite(window, ennemy2, NULL);
    sfRenderWindow_drawSprite(window, ennemy3, NULL);
    sfRenderWindow_drawSprite(window, explosion, NULL);
    sfRenderWindow_drawSprite(window, life, NULL);
    sfRenderWindow_drawSprite(window, cursor, NULL);
    sfRenderWindow_display(window);
  }
  sfMusic_destroy(music);
  sfTexture_destroy(tex_ennemy);
  sfTexture_destroy(tex_samus);
  sfTexture_destroy(tex_lights);
  sfTexture_destroy(tex_explosion);
  sfTexture_destroy(tex_life);
  sfTexture_destroy(tex_cursor);
  return (0);
}

