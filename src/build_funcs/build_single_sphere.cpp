void World::Build(void) {
  int numSamples = 16;

  _viewPlane.hres(200);
  _viewPlane.vres(200);
  _viewPlane.pixelScale(1.0);
  _viewPlane.samplerPtr(new MultiJittered(numSamples));
  _viewPlane.gamma(1.0);

  Point3D camEye(0, 0, 100);
  Point3D camLookat(0, 0, 0);
  Pinhole* ptr = new Pinhole(camEye, camLookat, 120);
  ptr->zoom(1);
  _cameraPtr = ptr;
  _cameraPtr->ComputeUVW();

  _tracerPtr = new MultipleObjects(this); 
  _bgColor = kWhite;

  // use access functions to set centre and radius
  Sphere* spherePtr = new Sphere;
  spherePtr->center(0.0);
  spherePtr->radius(85);
  spherePtr->color(1, 0, 0);  // red
  AddObject(spherePtr);	
}
