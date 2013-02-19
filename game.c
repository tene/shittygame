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
   Evas_Object *bg, *cursor, *obj;
   int layer, x, y;

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

   evas_object_event_callback_add(bg, EVAS_CALLBACK_MOUSE_MOVE, _mouse_move, NULL);

   cursor = evas_object_rectangle_add(ecore_evas_get(ee));
   evas_object_color_set(cursor, 0, 255, 0, 255);
   evas_object_resize(cursor, 5, 10);
   ecore_evas_object_cursor_set(ee, cursor, 0, 1, 1);

   ecore_evas_cursor_get(ee, &obj, &layer, &x, &y);
   if (obj == cursor && layer == 0 && x == 1 && y == 1)
     printf("Set cursor worked!\n");

   ecore_main_loop_begin();

   ecore_evas_free(ee);
   ecore_evas_shutdown();

   return 0;
}
