void World::Build(void) {
  int num_samples = 16;

  view_plane_.hres(200);
  view_plane_.vres(200);
  view_plane_.pixel_scale(1.0);
  view_plane_.sampler_ptr(new MultiJittered(num_samples));
  view_plane_.gamma(1.0);

  Point3D cam_eye(0, 0, 100);
  Point3D cam_lookat(0, 0, 0);
  float cam_d = 10;
  Pinhole *ptr = new Pinhole(cam_eye, cam_lookat, cam_d);
  ptr->zoom_ = 1;
  camera_ptr_ = ptr;

  tracer_ptr_ = new MultipleObjects(this); 
  bg_color_ = kWhite;

  // use access functions to set centre and radius
  Plane* plane_ptr = new Plane;
  plane_ptr->point(Point3D(0, 1, 0));
  plane_ptr->normal(Vector3D(0, 1, 0));
  plane_ptr->color(1, 0, 0);  // red
  AddObject(plane_ptr);
}
