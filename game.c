#define _GNU_SOURCE
#include <Ecore.h>
#include <Ecore_Evas.h>
#include <stdio.h>

void _mouse_move(void *data, Evas *e, Evas_Object *obj, void *event_info) {
    Evas_Event_Mouse_Move *move = (Evas_Event_Mouse_Move *)event_info;
    printf("mouse move: %d, %d\n", move->cur.output.x, move->cur.output.y);
}

int
main(void)
{
   Ecore_Evas *ee;
   Evas_Object *bg, *ship;

   ecore_evas_init();

   ee = ecore_evas_new(NULL, 0, 0, 200, 200, NULL);
   ecore_evas_title_set(ee, "Ecore Evas Object Example");
   ecore_evas_show(ee);

   bg = evas_object_rectangle_add(ecore_evas_get(ee));
   evas_object_color_set(bg, 0, 0, 255, 255);
   evas_object_resize(bg, 200, 200);
   evas_object_show(bg);
   ecore_evas_object_associate(ee, bg, ECORE_EVAS_OBJECT_ASSOCIATE_BASE);

   if (bg == ecore_evas_object_associate_get(ee))
     printf("Association worked!\n");

   //evas_object_event_callback_add(bg, EVAS_CALLBACK_MOUSE_MOVE, _mouse_move, NULL);

   ecore_evas_cursor_set(ee, "cursor.png", 0, 10, 10);

   ship = evas_object_image_filled_add(ecore_evas_get(ee));
   evas_object_image_file_set(ship, "ship.png", NULL);
   evas_object_resize(ship, 50, 50);
   evas_object_move(ship, 90, 90);
   evas_object_show(ship);

   int x, y, w, h, img_w, img_h;
   evas_object_geometry_get(ship, &x, &y, &w, &h);
   evas_object_image_size_get(ship, &img_w, &img_h);
   printf("geom: %d %d %d %d %d %d\n", x, y, w, h, img_w, img_h);
   Evas_Map *map = evas_map_new(4);
   evas_map_util_points_populate_from_object(map, ship);
   evas_map_point_image_uv_set(map, 0, 0, 0);
   evas_map_point_image_uv_set(map, 1, img_w, 0);
   evas_map_point_image_uv_set(map, 2, img_w, img_h);
   evas_map_point_image_uv_set(map, 3, 0, img_h);
   evas_map_util_rotate(map, 45, x + (w/2), y + (h/2));
   evas_object_map_set(ship, map);
   evas_object_map_enable_set(ship, EINA_TRUE);
   evas_map_free(map);

   ecore_main_loop_begin();

   ecore_evas_free(ee);
   ecore_evas_shutdown();

   return 0;
}
