void World::Build(void) {
  int num_samples = 16;

  view_plane_.hres(200);
  view_plane_.vres(200);
  view_plane_.pixel_scale(1.0);
  view_plane_.sampler_ptr(new MultiJittered(num_samples));
  view_plane_.gamma(1.0);

  Point3D cam_eye(0, 0, 100);
  Point3D cam_lookat(0, 0, 0);
  
  //Pinhole *ptr = new Pinhole(cam_eye, cam_lookat, 120);
  //ptr->zoom(1);

  //Fisheye *ptr = new Fisheye(cam_eye, cam_lookat);
  //ptr->SetFov(360);
  
  Spherical *ptr = new Spherical(cam_eye, cam_lookat);
  ptr->SetHFov(360);
  ptr->SetVFov(180);

  camera_ptr_ = ptr;
  camera_ptr_->ComputeUVW();

  tracer_ptr_ = new MultipleObjects(this); 
  bg_color_ = RGBColor(kBlack);

  // use access functions to set centre and radius
  Sphere* sphere_ptr = new Sphere;
  sphere_ptr->center(0, -25, 0);
  sphere_ptr->radius(80);
  sphere_ptr->color(1, 0, 0);  // red
  AddObject(sphere_ptr);

  // use constructor to set centre and radius 
  sphere_ptr = new Sphere(Point3D(0, 30, 0), 60);
  sphere_ptr->color(1, 1, 0);  // yellow
  AddObject(sphere_ptr);

  Plane* plane_ptr = new Plane(Point3D(0), Vector3D(0, 1, 1));
  plane_ptr->color(0.0, 0.3, 0.0); // dark green
  AddObject(plane_ptr);
}
