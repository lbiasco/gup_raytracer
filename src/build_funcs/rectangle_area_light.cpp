void World::Build() {
    int numSamples = 16;

    _viewPlane.hres(400);
    _viewPlane.vres(400);
    _viewPlane.samplerPtr(new MultiJittered(numSamples));

    _tracerPtr = new RayCast(this);

    AmbientOccluder* occluderPtr = new AmbientOccluder();
    occluderPtr->createsShadows(true);
    occluderPtr->ls(1.0);
    occluderPtr->color(kWhite);
    occluderPtr->minAmount(0);
    occluderPtr->samplerPtr(new MultiJittered(numSamples));
    _ambientPtr = occluderPtr;

    Directional* dirPtr = new Directional(Vector3D(1, 0.5, -5));
    dirPtr->ls(5.0);
    AddLight(dirPtr);

    Vector3D eye(10, 6, 18);
    //Vector3D eye(0, 1, 18);
    Pinhole* cameraPtr = new Pinhole(eye, Vector3D(0, 0, 1));
    cameraPtr->LookAt(Vector3D(0, 1, 0));
    cameraPtr->fov(10);
    cameraPtr->ComputeUVW();
    _cameraPtr = cameraPtr;

    Matte* mattePtr1 = new Matte();
    mattePtr1->SetKa(0.2);
    mattePtr1->SetKd(0.6);
    mattePtr1->SetCd(kYellow);

    Sphere* spherePtr1 = new Sphere(Vector3D(0, 1, 0), 1);
    spherePtr1->materialPtr(mattePtr1);
    AddObject(spherePtr1);

    Matte* mattePtr2 = new Matte();
    mattePtr2->SetKa(0.2);
    mattePtr2->SetKd(0.6);
    mattePtr2->SetCd(kWhite);


    Rect* rectPtr1 = new Rect(Vector3D(-1.5, -0.5, -3), Vector3D(0, 3, 0), Vector3D(3, 0, 0));
    rectPtr1->flipNormal(true);
    rectPtr1->materialPtr(mattePtr2);
    AddObject(rectPtr1);

    //Plane* planePtr1 = new Plane(Vector3D(-1.5, -0.5, -3), Vector3D(0, 0, 1));
    //planePtr1->materialPtr(mattePtr2);
    //AddObject(planePtr1);
}