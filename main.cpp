#include "constants.h"
#include "hittable.h"
#include "hittable_list.h"
#include "sphere.h"
#include "camera.h"
#include <time.h>
#include <chrono>

int main() {
    uint64_t initTime = timeSinceEpochMillisec();
   
    hittable_list world;

    world.add(make_shared<sphere>(point3(0, 0, -1), 0.5));
    world.add(make_shared<sphere>(point3(0, -100.5, -1), 100));

    camera cam;

    cam.aspect_ratio = 16.0 / 9.0;
    cam.image_width = 400;
    cam.samples_per_pixel = 16;
    cam.render(world);

    uint64_t endTime = timeSinceEpochMillisec();

    double timeTaken = (double)(endTime - initTime)/1000.0;
	std::clog << "Time taken: " << timeTaken << " Seconds\n";
	return 0;
}