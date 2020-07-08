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
  background_color_ = kWhite;

  // use access functions to set centre and radius
  Sphere* sphere_ptr = new Sphere;
  sphere_ptr->SetCenter(0.0);
  sphere_ptr->SetRadius(85);
  sphere_ptr->SetColor(1, 0, 0);  // red
  AddObject(sphere_ptr);	
}
