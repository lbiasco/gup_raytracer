void World::Build(void) {
    int numSamples = 16;

    _viewPlane.hres(400);
    _viewPlane.vres(400);
    _viewPlane.pixelScale(1.0);
    _viewPlane.gamma(1.0);
    _viewPlane.samplerPtr(new MultiJittered(numSamples));

    _bgColor = kBlack;
    _tracerPtr = new RayCast(this);

    Ambient* ambientPtr = new Ambient();
    ambientPtr->ls(1.0);
    _ambientPtr = ambientPtr;

    Vector3D camEye(0, 0, 500);
    Vector3D camLookat(-5, 0, 0);
    Pinhole* pinholePtr = new Pinhole(camEye, camLookat, 10);
    _cameraPtr = pinholePtr;
    _cameraPtr->ComputeUVW();

    PointLight* pointPtr = new PointLight(Vector3D(100, 50, 150));
    pointPtr->ls(3.0);
    AddLight(pointPtr);

    Matte* mattePtr = new Matte();
    mattePtr->SetKa(0.25);
    mattePtr->SetKd(2.65);
    mattePtr->SetCd(RGBColor(1, 1, 0));
    Sphere* spherePtr = new Sphere(Vector3D(-15, -15, -15), 27);
    spherePtr->material(mattePtr);
    AddObject(spherePtr);

    mattePtr = new Matte();
    mattePtr->SetKa(0.25);
    mattePtr->SetKd(2.65);
    mattePtr->SetCd(RGBColor(1, 0.5, 0.25));
    spherePtr = new Sphere(Vector3D(15, 15, 15), 27);
    spherePtr->material(mattePtr);
    AddObject(spherePtr);
}
