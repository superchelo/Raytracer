#pragma once
#ifndef CAMERA_H
#define CAMERA_H

#include "hittable.h"

class camera {
public:
    double aspect_ratio = 1.0;  // Ratio of image width over height
    int    image_width = 100;  // Rendered image width in pixel count
    int    samples_per_pixel = 16;   // Count of random samples for each pixel
	int    samples_per_pixel_sqrd = 4;   // Count of random samples for each pixel
    void render(const hittable& world) {
        initialize();

        std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

        for (int j = 0; j < image_height; j++) {
            //std::clog << "\rScanlines remaining: " << (image_height - j) << ' ' << std::flush;
            for (int i = 0; i < image_width; i++) {
                color pixel_color(0, 0, 0);
                for (int sample_X = 0; sample_X < samples_per_pixel_sqrd; sample_X++) {
                    for (int sample_Y = 0; sample_Y < samples_per_pixel_sqrd; sample_Y++) {
                        ray r = get_ray(i, j, sample_X, sample_Y);
                        pixel_color += ray_color(r, world);
                    }
                }
                write_color(std::cout, pixel_samples_scale * pixel_color);
            }
        }

        //std::clog << "\rDone.                 \n";
    }

private:
    /* Private Camera Variables Here */
    int    image_height;   // Rendered image height
    point3 center;         // Camera center
    point3 pixel00_loc;    // Location of pixel 0, 0
    vec3   pixel_delta_u;  // Offset to pixel to the right
    vec3   pixel_delta_v;  // Offset to pixel below
    double pixel_samples_scale;  // Color scale factor for a sum of pixel samples
    double pixel_offsets[4] = { -0.375, -0.125, 0.125, 0.375};

    void initialize() {
        image_height = int(image_width / aspect_ratio);
        image_height = (image_height < 1) ? 1 : image_height;

        center = point3(0, 0, 0);
        pixel_samples_scale = 1.0 / samples_per_pixel;

        // Determine viewport dimensions.
        auto focal_length = 1.0;
        auto viewport_height = 2.0;
        auto viewport_width = viewport_height * (double(image_width) / image_height);

        // Calculate the vectors across the horizontal and down the vertical viewport edges.
        auto viewport_u = vec3(viewport_width, 0, 0);
        auto viewport_v = vec3(0, -viewport_height, 0);

        // Calculate the horizontal and vertical delta vectors from pixel to pixel.
        pixel_delta_u = viewport_u / image_width;
        pixel_delta_v = viewport_v / image_height;

        // Calculate the location of the upper left pixel.
        auto viewport_upper_left =
            center - vec3(0, 0, focal_length) - viewport_u / 2 - viewport_v / 2;
        pixel00_loc = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);
    }
    ray get_ray(int i, int j, int sample_X, int sample_Y) const {
        // Construct a camera ray originating from the origin and directed at randomly sampled
        // point around the pixel location i, j.

		auto pixel_sample = pixel00_loc + ((pixel_offsets[sample_X] + i) * pixel_delta_u) + ((pixel_offsets[sample_Y]+j) * pixel_delta_v);
            
        auto ray_origin = center;
        auto ray_direction = pixel_sample - ray_origin;

        return ray(ray_origin, ray_direction);
    }
    color ray_color(const ray& r, const hittable& world) const {
        hit_record rec;

        if (world.hit(r, interval(0, infinity), rec)) {
            return 0.5 * (rec.normal + color(1, 1, 1));
        }

        vec3 unit_direction = unit_vector(r.direction());
        auto a = 0.5 * (unit_direction.y() + 1.0);
        return (1.0 - a) * color(1.0, 1.0, 1.0) + a * color(0.5, 0.7, 1.0);
    }
};
#endif