#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <signal.h>
#include <wayland-client.h>
#include "idle-inhibit-unstable-v1.h"

struct wl_display *display = NULL;
struct wl_compositor *compositor = NULL;
struct wl_surface *surface = NULL;
struct zwp_idle_inhibit_manager_v1 *inhibit_manager = NULL;
struct zwp_idle_inhibitor_v1 *inhibitor = NULL;

void global_registry_handler(void *data,
                             struct wl_registry *registry,
                             uint32_t id,
                             const char *interface,
                             uint32_t version) {
  if (strcmp(interface, "wl_compositor") == 0) {
    compositor = wl_registry_bind(registry, id, &wl_compositor_interface, 6);
    surface = wl_compositor_create_surface(compositor);
  } else if (strcmp(interface, "zwp_idle_inhibit_manager_v1") == 0) {
    inhibit_manager = wl_registry_bind(registry, id, &zwp_idle_inhibit_manager_v1_interface, 1);
  }
}

const struct wl_registry_listener registry_listener = {
  global_registry_handler,
  NULL
};

void cleanup(void) {
  zwp_idle_inhibitor_v1_destroy(inhibitor);
  zwp_idle_inhibit_manager_v1_destroy(inhibit_manager);
  wl_surface_destroy(surface);
  wl_compositor_destroy(compositor);
  
  wl_display_disconnect(display);
}

void graceful_exit(int) {
  cleanup();
  exit(0);
}

int main(void) {
  display = wl_display_connect(NULL);
  if (display == NULL) {
    fprintf(stderr, "Failed to connect to wayland display");
    return 1;
  }

  struct wl_registry *registry = wl_display_get_registry(display);
  wl_registry_add_listener(registry, &registry_listener, NULL);

  wl_display_dispatch(display);
  wl_display_roundtrip(display);

  signal(SIGTERM, graceful_exit);
  signal(SIGINT, graceful_exit);

  if (inhibit_manager == NULL) {
    fprintf(stderr, "The compositor doesn't support the idle_inhibit_unstable_v1 protocol");
    cleanup();
    return 1;
  }

  inhibitor = zwp_idle_inhibit_manager_v1_create_inhibitor(inhibit_manager, surface);

  while (wl_display_dispatch(display));
  
  cleanup();

  return 0;
}
