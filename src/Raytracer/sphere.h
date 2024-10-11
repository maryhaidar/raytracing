#ifndef SPHERE_H
#define SPHERE_H

#include "hittable.h"

class sphere : public hittable {
    public:
        // Stationary sphere
        sphere(const point3& static_centre, double radius, shared_ptr<material> mat)
          : centre(static_centre, vec3(0,0,0)), radius(std::fmax(0,radius)), mat(mat) {}

        // Moving sphere
        sphere(const point3& centre1, const point3& centre2, double radius, 
               shared_ptr<material> mat)
          : centre(centre1, centre2 - centre1), radius(std::fmax(0,radius)), mat(mat) {}

        bool hit(const ray& r, interval ray_t, hit_record& rec) const override {
            point3 current_centre = centre.at(r.time());
            vec3 oc = current_centre - r.origin();
            auto a = r.direction().length_squared();
            auto h = dot(r.direction(), oc);
            auto c = oc.length_squared() - radius*radius;

            auto discriminant = h*h - a*c;
            if (discriminant < 0)
                return false;

            auto sqrtd = std::sqrt(discriminant);

            // Find the nearest root that lies in the acceptable range.
            auto root = (h - sqrtd) / a;
            if (!ray_t.surrounds(root)) {
                root = (h + sqrtd) / a;
                if (!ray_t.surrounds(root)) 
                    return false;
            }

            rec.t = root;
            rec.p = r.at(rec.t);
            vec3 outward_normal = (rec.p - current_centre) / radius;
            rec.set_face_normal(r, outward_normal);
            rec.mat = mat;

            return true;
        }

        private:
            ray centre;
            double radius;
            shared_ptr<material> mat;
};

#endif