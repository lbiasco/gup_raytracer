void World::Build(void) {
  int num_samples = 16;

  vp_.SetHRes(512);
  vp_.SetVRes(512);
  vp_.SetPixelSize(0.040);
  vp_.SetSampler(new MultiJittered(num_samples));
  vp_.SetGamma(1.0);

  // Doesn't work with Pinhole due to using ray origin as x, y coords...
  Point3D cam_eye(0, 0, 100);
  Point3D cam_lookat(0, 0, 0);
  float cam_d = 10;
  Pinhole *ptr = new Pinhole(cam_eye, cam_lookat, cam_d);
  ptr->zoom_ = 1;
  camera_ptr_ = ptr;

  background_color_ = kWhite;

  auto ray_func = [](Ray ray) {
    double f = 0.5 * (1 + sin(ray.o_.x_ * ray.o* ray.o_.y_ * ray.o_.y_));
    return RGBColor(f); _.x_ 
  };
  Function *func_tracer = new Function(this);
  func_tracer->SetFunction(ray_func);

  tracer_ptr_ = func_tracer;
}
