#define _GNU_SOURCE
#include <Ecore.h>
#include <Ecore_Evas.h>
#include <stdio.h>
#include <math.h>

typedef struct ship {
    double x, y, dx, dy, angle;
    int w, h;
    Evas_Object *obj;
} Ship;

static Ship _new_ship(Evas *evas, char *img, float x, float y, int w, int h) {
   Ship ship = {x, y, 0, 0, 0, w, h, evas_object_image_filled_add(evas)};
   evas_object_image_file_set(ship.obj, img, NULL);
   evas_object_resize(ship.obj, w, h);
   evas_object_move(ship.obj, x - (w/2), y - (h/2));
   evas_object_show(ship.obj);

   return ship;
}

static double accel = 5;
static double frametime = 1.0/30.0;
static struct {
    int x, y;
} cursor;

static void _mouse_move(void *data, Evas *e, Evas_Object *obj, void *event_info) {
    Evas_Event_Mouse_Move *move = (Evas_Event_Mouse_Move *)event_info;
    cursor.x = move->cur.output.x;
    cursor.y = move->cur.output.y;
}

static void _on_keydown(void *data, Evas *e, Evas_Object *o, void *event_info) {
    Evas_Event_Key_Down *key = event_info;
    Ship *ship = data;
    printf("move: %c\n", key->keyname[0]);
    switch (key->keyname[0]) {
        case 'w':
            ship->dy -= accel;
            break;
        case 'a':
            ship->dx -= accel;
            break;
        case 's':
            ship->dy += accel;
            break;
        case 'd':
            ship->dx += accel;
            break;
        default:
            break;
    }
}

static Eina_Bool _move_ship(void *data) {
    Ship *ship = (Ship *)data;
    ship->x += ship->dx * frametime;
    ship->y += ship->dy * frametime;
    int x = (int)ship->x;
    int y = (int)ship->y;
    //printf("moving ship to: %d, %d\n", x, y);
    evas_object_move(ship->obj, x - (ship->w/2), y - (ship->h/2));
    ship->angle = 90 + (atan2(cursor.y - y, cursor.x - x) * 180/M_PI);

    int img_w, img_h;
    evas_object_image_size_get(ship->obj, &img_w, &img_h);
 
    Evas_Map *map = evas_map_new(4);
    evas_map_util_points_populate_from_object(map, ship->obj);
    evas_map_point_image_uv_set(map, 0, 0, 0);
    evas_map_point_image_uv_set(map, 1, img_w, 0);
    evas_map_point_image_uv_set(map, 2, img_w, img_h);
    evas_map_point_image_uv_set(map, 3, 0, img_h);
    evas_map_smooth_set(map, EINA_TRUE);
    evas_map_util_rotate(map, ship->angle, x, y);
    evas_object_map_set(ship->obj, map);
    evas_object_map_enable_set(ship->obj, EINA_TRUE);
    evas_map_free(map);
    return EINA_TRUE;
}

int
main(void)
{
   Ecore_Evas *ee;
   Evas_Object *bg;

   ecore_evas_init();

   ee = ecore_evas_new(NULL, 0, 0, 200, 200, NULL);
   ecore_evas_title_set(ee, "Ecore Evas Object Example");
   ecore_evas_show(ee);

   bg = evas_object_rectangle_add(ecore_evas_get(ee));
   evas_object_color_set(bg, 0, 0, 255, 255);
   evas_object_resize(bg, 200, 200);
   evas_object_show(bg);
   ecore_evas_object_associate(ee, bg, ECORE_EVAS_OBJECT_ASSOCIATE_BASE);
   evas_object_focus_set(bg, EINA_TRUE);


   ecore_evas_cursor_set(ee, "cursor.png", 0, 10, 10);

   Ship ship = _new_ship(ecore_evas_get(ee), "ship.png", 90, 90, 50, 70);

   ecore_animator_frametime_set(frametime);
   ecore_animator_add(_move_ship, &ship);
   evas_object_event_callback_add(bg, EVAS_CALLBACK_KEY_DOWN, _on_keydown, &ship);
   evas_object_event_callback_add(bg, EVAS_CALLBACK_MOUSE_MOVE, _mouse_move, &ship);

   ecore_main_loop_begin();

   ecore_evas_free(ee);
   ecore_evas_shutdown();

   return 0;
}
