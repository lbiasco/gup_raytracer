void World::Build(void) {
  int num_samples = 16;

  view_plane_.hres(200);
  view_plane_.vres(200);
  view_plane_.pixel_scale(1.0);
  view_plane_.sampler_ptr(new MultiJittered(num_samples));
  view_plane_.gamma(1.0);

  Point3D cam_eye(0, -100, 0);
  Point3D cam_lookat(0, 0, 0);
  camera_ptr_ = new Pinhole(cam_eye, cam_lookat, 120);
  camera_ptr_->ComputeUVW();

  tracer_ptr_ = new MultipleObjects(this); 

  bg_color_ = kWhite;

  // use access functions to set centre and radius
  Sphere* sphere_ptr = new Sphere;
  sphere_ptr->center(0.0);
  sphere_ptr->radius(85);
  sphere_ptr->color(1, 0, 0);  // red
  AddObject(sphere_ptr);

  sphere_ptr = new Sphere;
  sphere_ptr->center(0.0);
  sphere_ptr->radius(75);
  sphere_ptr->color(0, 0, 1);  // red
  AddObject(sphere_ptr);
}
