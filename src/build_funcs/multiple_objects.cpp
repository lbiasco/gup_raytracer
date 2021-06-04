void World::Build(void) {
    int numSamples = 16;

    _viewPlane.hres(200);
    _viewPlane.vres(200);
    _viewPlane.pixelScale(1.0);
    _viewPlane.gamma(1.0);
    _viewPlane.samplerPtr(new MultiJittered(numSamples));

    _bgColor = kBlack;
    _tracerPtr = new RayCast(this);

    Ambient* ambientPtr = new Ambient();
    ambientPtr->ls(1.0);
    _ambientPtr = ambientPtr;

    PointLight* pointPtr = new PointLight(Vector3D(100, 50, 150));
    pointPtr->ls(3.0);
    AddLight(pointPtr);

    Vector3D camEye(0, 0, 300);
    Vector3D camLookat(0, 0, 0);

    double offset = Camera::ComputeStereoHalfSeparationFromAngle(5, camEye.Distance(camLookat));

    Pinhole* ptr = new Pinhole(camEye, Vector3D(0), 120);
    ptr->LookAt(camLookat);
    ptr->zoom(1);
    ptr->apertureOffsetX(offset);

    //ThinLens* ptr = new ThinLens(camEye, camLookat);
    //ptr->zoom(1);
    //ptr->fov(120);
    //ptr->focalLength(20);
    //ptr->lensRadius(5);
    //ptr->samplerPtr(new MultiJittered(numSamples));
    //ptr->apertureOffsetX(-offset);

    //Fisheye* ptr = new Fisheye(camEye, camLookat);
    //ptr->SetFov(360);
    
    //Spherical* ptr = new Spherical(camEye, camLookat);
    //ptr->SetHFov(360);
    //ptr->SetVFov(180);

    _cameraPtr = ptr;
    _cameraPtr->ComputeUVW();

    Matte* mattePtr = new Matte();
    mattePtr->SetKa(0.5);
    mattePtr->SetKd(1.5);
    mattePtr->SetCd(RGBColor(1, 0, 0));
    // use access functions to set centre and radius
    Sphere* spherePtr = new Sphere;
    spherePtr->center(0, -25, 0);
    spherePtr->radius(80);
    spherePtr->materialPtr(mattePtr); 
    AddObject(spherePtr);

    mattePtr = new Matte(*mattePtr);
    mattePtr->SetCd(RGBColor(1, 1, 0));
    // use constructor to set centre and radius 
    spherePtr = new Sphere(Vector3D(0, 30, 0), 60);
    spherePtr->materialPtr(mattePtr);  // yellow
    AddObject(spherePtr);

    mattePtr = new Matte(*mattePtr);
    mattePtr->SetCd(RGBColor(0, 1, 0));
    Plane* planePtr = new Plane(Vector3D(0), Vector3D(0, 1, 1));
    planePtr->materialPtr(mattePtr);
    AddObject(planePtr);
}
