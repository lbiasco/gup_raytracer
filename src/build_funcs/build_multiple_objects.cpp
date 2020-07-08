void World::Build(void) {
  int num_samples = 16;

  vp_.SetHRes(200);
  vp_.SetVRes(200);
  vp_.SetPixelSize(1.0);

  vp_.SetSampler(new MultiJittered(num_samples));
  vp_.SetGamma(1.0);

  Point3D cam_eye(0, 0, 100);
  Point3D cam_lookat(0, 0, 0);
  float cam_d = 10;
  Pinhole *ptr = new Pinhole(cam_eye, cam_lookat, cam_d);
  ptr->zoom_ = 3;
  camera_ptr_ = ptr;

  tracer_ptr_ = new MultipleObjects(this); 
  background_color_ = RGBColor(kBlack);

  // use access functions to set centre and radius
  Sphere* sphere_ptr = new Sphere;
  sphere_ptr->SetCenter(0, -25, 0);
  sphere_ptr->SetRadius(80);
  sphere_ptr->SetColor(1, 0, 0);  // red
  AddObject(sphere_ptr);

  // use constructor to set centre and radius 
  sphere_ptr = new Sphere(Point3D(0, 30, 0), 60);
  sphere_ptr->SetColor(1, 1, 0);  // yellow
  AddObject(sphere_ptr);

  Plane* plane_ptr = new Plane(Point3D(0), Normal(0, 1, 1));
  plane_ptr->SetColor(0.0, 0.3, 0.0); // dark green
  AddObject(plane_ptr);
}
