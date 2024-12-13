# v1.0.0 (2024-10-09)

* Initial release.
* Output file format changed from PPM to BMP.
* Camera orientation now specified by a direction vector instead of a point.
* Instead of always scattering light, the raytracer now scatters with a fixed 
  probability p and an attenuation albedo/p.

# v1.1.0 (2024-12-13)

* Implemented motion blur by incorporating shutter speed and ray time into
  the rendering process.
* Added a basic `animated_transform` class to handle linear interpolation of 
  object positions over time, enabling simple animation.