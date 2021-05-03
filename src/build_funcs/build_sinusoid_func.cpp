void World::Build(void) {
  int numSamples = 16;

  _viewPlane.hres(512);
  _viewPlane.vres(512);
  _viewPlane.pixelScale(0.040);
  _viewPlane.samplerPtr(new MultiJittered(numSamples));
  _viewPlane.gamma(1.0);

  // Doesn't work with Pinhole due to using ray origin as x, y coords...
  Point3D camEye(0, 0, 100);
  Point3D camLookat(0, 0, 0);
  Pinhole* ptr = new Pinhole(camEye, camLookat);
  ptr->zoom(1);
  _cameraPtr = ptr;
  _cameraPtr->ComputeUVW();

  _bgColor = kWhite;

  auto rayFunc = [](Ray ray) {
    double f = 0.5 * (1 + sin(ray.origin().x * ray.origin().x * ray.origin().y * ray.origin().y));
    return RGBColor(f);
  };
  Function* funcTracer = new Function(this);
  funcTracer->SetFunction(rayFunc);

  _tracerPtr = funcTracer;
}
