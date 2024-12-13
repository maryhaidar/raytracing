#ifndef TRANSFORM_H
#define TRANSFORM_H

class animated_transform {
    public:
        animated_transform() {}
        animated_transform(const point3& start_pos, const point3& end_pos, double start_time, double end_time)
         : start_pos(start_pos), end_pos(end_pos), start_time(start_time), end_time(end_time)
        {
            if (start_pos != end_pos) actually_animated = true;
        }

        bool is_animated() const { return actually_animated; }

        point3 apply_inverse(const point3& p, double time) const {
            if (!actually_animated) return start_pos;
            return interpolate(time);
        }

    private:
        point3 interpolate(double time) const {
            // Linear interpolation between start_pos and end_pos
            double t = (time - start_time) / (end_time - start_time);
            t = clamp(t, 0.0, 1.0);
            return (1.0 - t) * start_pos + t * end_pos;
        }

        point3 start_pos, end_pos;
        double start_time, end_time;
        bool actually_animated = false;
};

#endif