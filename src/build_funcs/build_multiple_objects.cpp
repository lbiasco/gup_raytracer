void World::Build(void) {
  int numSamples = 16;

  _viewPlane.hres(200);
  _viewPlane.vres(200);
  _viewPlane.pixelScale(1.0);
  _viewPlane.samplerPtr(new MultiJittered(numSamples));
  _viewPlane.gamma(1.0);

  Point3D camEye(0, 0, 100);
  Point3D camLookat(0, 0, 0);
  
  //Pinhole* ptr = new Pinhole(camEye, camLookat, 120);
  //ptr->zoom(1);

  //Fisheye* ptr = new Fisheye(camEye, camLookat);
  //ptr->SetFov(360);
  
  Spherical* ptr = new Spherical(camEye, camLookat);
  ptr->SetHFov(360);
  ptr->SetVFov(180);

  _cameraPtr = ptr;
  _cameraPtr->ComputeUVW();

  _tracerPtr = new MultipleObjects(this); 
  _bgColor = RGBColor(kBlack);

  // use access functions to set centre and radius
  Sphere* spherePtr = new Sphere;
  spherePtr->center(0, -25, 0);
  spherePtr->radius(80);
  spherePtr->color(1, 0, 0);  // red
  AddObject(spherePtr);

  // use constructor to set centre and radius 
  spherePtr = new Sphere(Point3D(0, 30, 0), 60);
  spherePtr->color(1, 1, 0);  // yellow
  AddObject(spherePtr);

  Plane* planePtr = new Plane(Point3D(0), Vector3D(0, 1, 1));
  planePtr->color(0.0, 0.3, 0.0); // dark green
  AddObject(planePtr);
}
