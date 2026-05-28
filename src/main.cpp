#include <iostream>
#include <fstream>
#include "vec3.h"
#include "color.h"
#include "ray.h"
#include "hittable_list.h" 
#include "sphere.h"

color ray_color(const ray& r, const hittable& world) {
    hit_record rec;
    // Search for hits between 0.001 (to avoid floating point acne) and infinity
    if (world.hit(r, 0.001, 1000.0, rec)) {
        // Map normal [-1, 1] to color [0, 1]
        return 0.5 * (rec.normal + color(1, 1, 1));
    }

    // Sky gradient background
    vec3 unit_direction = unit_vector(r.direction());
    auto a = 0.5 * (unit_direction.y() + 1.0);
    return (1.0 - a) * color(1.0, 1.0, 1.0) + a * color(0.5, 0.7, 1.0);
}

int main() {
    // Image configuration
    const int image_width = 256;
    const int image_height = 256;
    
    // Viewport configuration
    const double viewport_height = 30.0;
    const double viewport_width = 30.0;
    const double viewport_x_location = 25.0;
    
    const double pixel_height = viewport_height / image_height;
    const double pixel_width = viewport_width / image_width;

    point3 camera(0.0, 0.0, 0.0);
    point3 viewportTL(viewport_x_location, viewport_height/2, -viewport_width/2);

    // World configuration
    hittable_list world;
    world.add(std::make_shared<sphere>(point3(5.0, 0.0, 0.0), 2.0));        // Main sphere
    world.add(std::make_shared<sphere>(point3(5.0, -102.0, 0.0), 100.0));   // Ground sphere

    // File Output
    std::ofstream output_file{"image.ppm", std::ios::out | std::ios::binary};
    if (!output_file) {
        std::cerr << "Error: Could not open file for writing.\n";
        return EXIT_FAILURE;
    }

    output_file << "P3\n" << image_width << ' ' << image_height << "\n255\n";

    // Render loop
    for (int j = 0; j < image_height; j++) {
        std::clog << "\rScanlines remaining: " << (image_height - j) << ' ' << std::flush;
        for (int i = 0; i < image_width; i++) {
            
            double pixelCenterY = viewportTL.y() - j * pixel_height - pixel_height/2;
            double pixelCenterZ = viewportTL.z() + i * pixel_width + pixel_width/2;
            
            ray rayToPixel(camera, point3(viewport_x_location, pixelCenterY, pixelCenterZ) - camera);
            color pixel_color = ray_color(rayToPixel, world);

            write_color(output_file, pixel_color);
        }
    }
    
    std::clog << "\rDone.                 \n";
    output_file.close();

    return EXIT_SUCCESS;
}