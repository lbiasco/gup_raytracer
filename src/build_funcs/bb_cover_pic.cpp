// This builds the cover image for Chapter 3: Bare Bones Ray Tracing

void World::Build(void) {
    int numSamples = 16;

    _viewPlane.hres(400);
    _viewPlane.vres(400);
    //_viewPlane.pixelScale(1);
    _viewPlane.samplerPtr(new MultiJittered(numSamples));
    _viewPlane.gamma(1.0);

    Ambient* ambientPtr = new Ambient();
    ambientPtr->ls(0.0);
    _ambientPtr = ambientPtr;

    //PointLight* pointPtr = new PointLight(Vector3D(100, 50, 150));
    //pointPtr->ls(3.0);
    //pointPtr->attenuation(0.0);
    //pointPtr->createsShadows(true);
    //AddLight(pointPtr);

    Directional* dirPtr = new Directional(Vector3D(-1, 0.5, -1));
    AddLight(dirPtr);

    Vector3D camEye(0, 0, 100);
    Vector3D viewDir(0, 0, -1);
    //Pinhole* ptr = new Pinhole(camEye, viewDir, 60);
    
    ThinLens* ptr = new ThinLens(camEye, viewDir);
    ptr->focalLength(80);
    ptr->lensRadius(0.2);
    ptr->samplerPtr(new MultiJittered(numSamples));
    
    ptr->fov(60);
    ptr->zoom(1);

    //Fisheye* ptr = new Fisheye(camEye, viewDir);
    //ptr->SetFov(120);
    _cameraPtr = ptr;
    
    //_cameraPtr->rotateV(-20);
    //_cameraPtr->translateW(-60);
    _cameraPtr->ComputeUVW();

    _bgColor = RGBColor(0.0);
    _tracerPtr = new RayCast(this);  

    // colours
    RGBColor yellow(1, 1, 0);               // yellow
    RGBColor brown(0.71, 0.40, 0.16);       // brown
    RGBColor darkGreen(0.0, 0.41, 0.41);   // darkGreen
    RGBColor orange(1, 0.75, 0);            // orange
    RGBColor green(0, 0.6, 0.3);            // green
    RGBColor lightGreen(0.65, 1, 0.30);    // light green
    RGBColor darkYellow(0.61, 0.61, 0);    // dark yellow
    RGBColor lightPurple(0.65, 0.3, 1);    // light purple
    RGBColor darkPurple(0.5, 0, 1);        // dark purple
    RGBColor darkRed(0.5, 0, 0);

    // spheres
    Sphere*	spherePtr1 = new Sphere(Vector3D(5, 3, 0), 30);
    spherePtr1->castsShadows(true);
    Glossy* glossyPtr = new Glossy(0.25, 0.6, 0.2, 3, yellow);
    glossyPtr->SetCs(darkPurple);
    spherePtr1->materialPtr(glossyPtr);
    //spherePtr1->materialPtr(new Glossy(0.25, 0.6, 0.2, 3, yellow));
    //((Glossy*)spherePtr1->materialPtr())->SetCs(green);
    AddObject(spherePtr1);

    Lambertian* ambient = new Lambertian(0.5, brown);
    Lambertian* diffuse = new Lambertian(0.3, brown);
    Phong* specular = new Phong(0.1, 0, brown);
    Plastic* plasticPtr = new Plastic(ambient, diffuse, specular);
    Sphere*	spherePtr2 = new Sphere(Vector3D(45, -7, -60), 20); 
    spherePtr2->materialPtr(plasticPtr);
    AddObject(spherePtr2);
        
    Sphere*	spherePtr3 = new Sphere(Vector3D(40, 43, -100), 17); 
    spherePtr3->materialPtr(new Glossy(0.25, 0.6, 0.2, 3, darkGreen));
    AddObject(spherePtr3);

    glossyPtr = new Glossy(0.25, 0.6, 0.2, 3, orange);
    glossyPtr->receivesShadows(true);
    Sphere*	spherePtr4 = new Sphere(Vector3D(-20, 28, -15), 20); 
    spherePtr4->materialPtr(glossyPtr);
    AddObject(spherePtr4);

    Sphere*	spherePtr5 = new Sphere(Vector3D(-25, -7, -35), 27);
    spherePtr5->materialPtr(new Glossy(0.25, 0.6, 0.2, 3, green));
    AddObject(spherePtr5);

    Sphere*	spherePtr6 = new Sphere(Vector3D(20, -27, -35), 25); 
    spherePtr6->materialPtr(new Glossy(0.25, 0.6, 0.2, 3, lightGreen));
    AddObject(spherePtr6);

    Sphere*	spherePtr7 = new Sphere(Vector3D(35, 18, -35), 22); 
    spherePtr7->materialPtr(new Glossy(0.25, 0.6, 0.2, 3, green));
    AddObject(spherePtr7);

    Sphere*	spherePtr8 = new Sphere(Vector3D(-57, -17, -50), 15);  
    spherePtr8->materialPtr(new Glossy(0.25, 0.6, 0.2, 3, brown));
    AddObject(spherePtr8);

    Sphere*	spherePtr9 = new Sphere(Vector3D(-47, 16, -80), 23); 
    spherePtr9->materialPtr(new Glossy(0.25, 0.6, 0.2, 3, lightGreen));
    AddObject(spherePtr9);
        
    Sphere*	spherePtr10 = new Sphere(Vector3D(-15, -32, -60), 22); 
    spherePtr10->materialPtr(new Glossy(0.25, 0.6, 0.2, 3, darkGreen));
    AddObject(spherePtr10);

    Sphere*	spherePtr11 = new Sphere(Vector3D(-35, -37, -80), 22); 
    spherePtr11->materialPtr(new Glossy(0.25, 0.6, 0.2, 3, darkYellow));
    AddObject(spherePtr11);

    Sphere*	spherePtr12 = new Sphere(Vector3D(10, 43, -80), 22); 
    spherePtr12->materialPtr(new Glossy(0.25, 0.6, 0.2, 3, darkYellow));
    AddObject(spherePtr12);
        
    Sphere*	spherePtr13 = new Sphere(Vector3D(30, -7, -80), 10); 
    spherePtr13->materialPtr(new Glossy(0.25, 0.6, 0.2, 3, darkYellow));
    AddObject(spherePtr13);
        
    Sphere*	spherePtr14 = new Sphere(Vector3D(-40, 48, -110), 18); 
    spherePtr14->materialPtr(new Glossy(0.25, 0.6, 0.2, 3, darkGreen));
    AddObject(spherePtr14);
        
    Sphere*	spherePtr15 = new Sphere(Vector3D(-10, 53, -120), 18); 
    spherePtr15->materialPtr(new Glossy(0.25, 0.6, 0.2, 3, brown));
    AddObject(spherePtr15);

    Sphere*	spherePtr16 = new Sphere(Vector3D(-55, -52, -100), 10); 
    spherePtr16->materialPtr(new Glossy(0.25, 0.6, 0.2, 3, lightPurple));
    AddObject(spherePtr16);

    Sphere*	spherePtr17 = new Sphere(Vector3D(5, -52, -100), 15);
    spherePtr17->materialPtr(new Glossy(0.25, 0.6, 0.2, 3, brown));
    AddObject(spherePtr17);

    Sphere*	spherePtr18 = new Sphere(Vector3D(-20, -57, -120), 15); 
    spherePtr18->materialPtr(new Glossy(0.25, 0.6, 0.2, 3, darkPurple));
    AddObject(spherePtr18);

    Sphere*	spherePtr19 = new Sphere(Vector3D(55, -27, -100), 17); 
    spherePtr19->materialPtr(new Glossy(0.25, 0.6, 0.2, 3, darkGreen));
    AddObject(spherePtr19);

    Sphere*	spherePtr20 = new Sphere(Vector3D(50, -47, -120), 15); 
    spherePtr20->materialPtr(new Glossy(0.25, 0.6, 0.2, 3, brown));
    AddObject(spherePtr20);
        
    Sphere*	spherePtr21 = new Sphere(Vector3D(70, -42, -150), 10); 
    spherePtr21->materialPtr(new Glossy(0.25, 0.6, 0.2, 3, lightPurple));
    AddObject(spherePtr21);

    Sphere*	spherePtr22 = new Sphere(Vector3D(5, 73, -130), 12); 
    spherePtr22->materialPtr(new Glossy(0.25, 0.6, 0.2, 3, lightPurple));
    AddObject(spherePtr22);

    Sphere*	spherePtr23 = new Sphere(Vector3D(66, 21, -130), 13);
    spherePtr23->materialPtr(new Glossy(0.25, 0.6, 0.2, 3, darkPurple));
    AddObject(spherePtr23);	
        
    Sphere*	spherePtr24 = new Sphere(Vector3D(72, -12, -140), 12);
    spherePtr24->materialPtr(new Glossy(0.25, 0.6, 0.2, 3, lightPurple));
    AddObject(spherePtr24);

    Sphere*	spherePtr25 = new Sphere(Vector3D(64, 5, -160), 11);
    spherePtr25->materialPtr(new Glossy(0.25, 0.6, 0.2, 3, green));
    AddObject(spherePtr25);
        
    Sphere*	spherePtr26 = new Sphere(Vector3D(55, 38, -160), 12);
    spherePtr26->materialPtr(new Glossy(0.25, 0.6, 0.2, 3, lightPurple));
    AddObject(spherePtr26);

    Sphere*	spherePtr27 = new Sphere(Vector3D(-73, -2, -160), 12);
    spherePtr27->materialPtr(new Glossy(0.25, 0.6, 0.2, 3, lightPurple));
    AddObject(spherePtr27);
        
    Sphere*	spherePtr28 = new Sphere(Vector3D(30, -62, -140), 15); 
    spherePtr28->materialPtr(new Glossy(0.25, 0.6, 0.2, 3, darkPurple));
    AddObject(spherePtr28);

    Sphere*	spherePtr29 = new Sphere(Vector3D(25, 63, -140), 15); 
    spherePtr29->materialPtr(new Glossy(0.25, 0.6, 0.2, 3, darkPurple));
    AddObject(spherePtr29);

    Sphere*	spherePtr30 = new Sphere(Vector3D(-60, 46, -140), 15);  
    spherePtr30->materialPtr(new Glossy(0.25, 0.6, 0.2, 3, darkPurple));
    AddObject(spherePtr30);

    Sphere*	spherePtr31 = new Sphere(Vector3D(-30, 68, -130), 12); 
    spherePtr31->materialPtr(new Glossy(0.25, 0.6, 0.2, 3, lightPurple));
    AddObject(spherePtr31);

    Sphere*	spherePtr32 = new Sphere(Vector3D(58, 56, -180), 11);   
    spherePtr32->materialPtr(new Glossy(0.25, 0.6, 0.2, 3, green));
    AddObject(spherePtr32);

    Sphere*	spherePtr33 = new Sphere(Vector3D(-63, -39, -180), 11); 
    spherePtr33->materialPtr(new Glossy(0.25, 0.6, 0.2, 3, green));
    AddObject(spherePtr33);

    Sphere*	spherePtr34 = new Sphere(Vector3D(46, 68, -200), 10);
    spherePtr34->materialPtr(new Glossy(0.25, 0.6, 0.2, 3, lightPurple));
    AddObject(spherePtr34);

    Sphere*	spherePtr35 = new Sphere(Vector3D(-3, -72, -130), 12); 
    spherePtr35->materialPtr(new Glossy(0.25, 0.6, 0.2, 3, lightPurple));
    AddObject(spherePtr35);

    //Plane* planePtr = new Plane(Vector3D(0, 0, -250), Vector3D(0, 0, 1));
    //planePtr->materialPtr(new Matte(0.5, 1.5, darkRed));
    //AddObject(planePtr);
}

