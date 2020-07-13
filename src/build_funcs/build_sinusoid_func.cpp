void World::Build(void) {
  int num_samples = 16;

  view_plane_.hres(512);
  view_plane_.vres(512);
  view_plane_.pixel_scale(0.040);
  view_plane_.sampler_ptr(new MultiJittered(num_samples));
  view_plane_.gamma(1.0);

  // Doesn't work with Pinhole due to using ray origin as x, y coords...
  Point3D cam_eye(0, 0, 100);
  Point3D cam_lookat(0, 0, 0);
  Pinhole *ptr = new Pinhole(cam_eye, cam_lookat);
  ptr->zoom(1);
  camera_ptr_ = ptr;

  bg_color_ = kWhite;

  auto ray_func = [](Ray ray) {
    double f = 0.5 * (1 + sin(ray.origin().x * ray.origin().x * ray.origin().y * ray.origin().y));
    return RGBColor(f);
  };
  Function *func_tracer = new Function(this);
  func_tracer->SetFunction(ray_func);

  tracer_ptr_ = func_tracer;
}
