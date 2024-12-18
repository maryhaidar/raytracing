#include "rtutility.h"

#include "camera.h"
#include "hittable.h"
#include "hittable_list.h"
#include "material.h"
#include "sphere.h"


int main(int argc, char* argv[]) {
    hittable_list world;

    // Camera
    camera cam;

    cam.aspect_ratio      = 16.0 / 9.0;
    cam.image_width       = 400;
    cam.samples_per_pixel = 100;
    cam.max_depth         = 50;

    cam.vfov     = 20;
    cam.lookfrom = point3(13,2,3);
    cam.lookdir  = vec3(-4.5,-0.65,-1);
    cam.vup      = vec3(0,1,0);

    cam.defocus_angle = 0.6;
    cam.focus_dist    = 13.0;
    cam.shutter_speed = 1.0 / 15.0;
    cam.total_frames = 24;
    cam.fps = 24;

    auto ground_material = make_shared<lambertian>(colour(0.5, 0.5, 0.5), 0.8);
    world.add(make_shared<sphere>(point3(0,-1000,0), 1000, ground_material));

    auto material1 = make_shared<dielectric>(1.5);
    world.add(make_shared<sphere>(point3(0, 1, 0), 1.0, material1));

    auto material2 = make_shared<lambertian>(colour(0.4, 0.2, 0.1), 0.6);
    world.add(make_shared<sphere>(point3(-4, 1, 0), 1.0, material2));

    auto material3 = make_shared<metal>(colour(0.7, 0.6, 0.5), 0.0);
    world.add(make_shared<sphere>(point3(4, 1, 0), 1.0, material3));

    for (int a = -11; a < 11; a++) {
        for (int b = -11; b < 11; b++) {
            auto choose_mat = random_double();
            point3 centre(a + 0.9*random_double(), 0.2, b + 0.9*random_double());

            if ((centre - point3(4, 0.2, 0)).length() > 0.9) {
                shared_ptr<material> sphere_material;

                if (choose_mat < 0.8) {
                    // diffuse
                    auto albedo = colour::random() * colour::random();
                    sphere_material = make_shared<lambertian>(albedo, 0.5); 
                    point3 centre2 = centre + vec3(0, random_double(0, 0.5) + 0.5 * sin(centre.x() * pi), 0);
                    animated_transform animated_transform(centre, centre2, 0.0, 1.0);
                    world.add(make_shared<sphere>(animated_transform, 0.2, sphere_material)); 
                } else if (choose_mat < 0.95) {
                    // metal
                    auto albedo = colour::random(0.5, 1);
                    auto fuzz = random_double(0, 0.5);
                    sphere_material = make_shared<metal>(albedo, fuzz);
                    world.add(make_shared<sphere>(centre, 0.2, sphere_material));
                } else {
                    // glass
                    sphere_material = make_shared<dielectric>(1.5);
                    world.add(make_shared<sphere>(centre, 0.2, sphere_material));
                }
            }
        }
    }

    for (int frame = 0; frame < cam.total_frames; frame++) {
        double frame_time = frame * (1.0 / cam.fps);
        cam.render(world, argc, argv, frame, frame_time);
    }
}