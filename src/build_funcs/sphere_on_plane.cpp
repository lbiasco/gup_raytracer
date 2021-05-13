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
    occluderPtr->minAmount(kBlack);
    occluderPtr->samplerPtr(new MultiJittered(numSamples));
    _ambientPtr = occluderPtr;

    Vector3D eye(10, 6, 18);
    Pinhole* cameraPtr = new Pinhole(eye, Vector3D(0, 0, 1));
    cameraPtr->LookAt(Vector3D(0, 1, 0));
    cameraPtr->fov(10);
    cameraPtr->ComputeUVW();
    _cameraPtr = cameraPtr;

    Matte* mattePtr1 = new Matte();
    mattePtr1->SetKa(0.75);
    mattePtr1->SetKd(0);
    mattePtr1->SetCd(kYellow);

    Sphere* spherePtr1 = new Sphere(Vector3D(0, 1, 0), 1);
    spherePtr1->material(mattePtr1);
    AddObject(spherePtr1);

    Matte* mattePtr2 = new Matte();
    mattePtr2->SetKa(0.75);
    mattePtr2->SetKd(0);
    mattePtr2->SetCd(kWhite);

    Plane* planePtr1 = new Plane(Vector3D(0), Vector3D(0, 1, 0));
    planePtr1->material(mattePtr2);
    AddObject(planePtr1);
}