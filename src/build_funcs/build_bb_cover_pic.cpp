// This builds the cover image for Chapter 3: Bare Bones Ray Tracing

void World::Build(void) {
    int numSamples = 16;

    _viewPlane.hres(400);
    _viewPlane.vres(400);
    //_viewPlane.pixelScale(1);
    _viewPlane.samplerPtr(new MultiJittered(numSamples));
    _viewPlane.gamma(1.0);

    Point3D camEye(0, 0, 100);
    Vector3D viewDir(0, 0, -1);
    //Pinhole* ptr = new Pinhole(camEye, viewDir, 60);
    
    ThinLens* ptr = new ThinLens(camEye, viewDir, 60);
    ptr->focalLength(80);
    ptr->lensRadius(0.2);
    ptr->samplerPtr(new MultiJittered(numSamples));
    
    //ptr->fov(60);
    //ptr->zoom(1);

    //Fisheye* ptr = new Fisheye(camEye, viewDir);
    //ptr->SetFov(120);
    _cameraPtr = ptr;
    
    //_cameraPtr->rotateV(-20);
    //_cameraPtr->translateW(-60);
    _cameraPtr->ComputeUVW();

    _bgColor = RGBColor(0.0);
    _tracerPtr = new MultipleObjects(this);  

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

    // spheres
    Sphere*	spherePtr1 = new Sphere(Point3D(5, 3, 0), 30);
    spherePtr1->color(yellow);
    AddObject(spherePtr1);

    Sphere*	spherePtr2 = new Sphere(Point3D(45, -7, -60), 20); 
    spherePtr2->color(brown);
    AddObject(spherePtr2);
        
    Sphere*	spherePtr3 = new Sphere(Point3D(40, 43, -100), 17); 
    spherePtr3->color(darkGreen);
    AddObject(spherePtr3);

    Sphere*	spherePtr4 = new Sphere(Point3D(-20, 28, -15), 20); 
    spherePtr4->color(orange);
    AddObject(spherePtr4);

    Sphere*	spherePtr5 = new Sphere(Point3D(-25, -7, -35), 27);
    spherePtr5->color(green);
    AddObject(spherePtr5);

    Sphere*	spherePtr6 = new Sphere(Point3D(20, -27, -35), 25); 
    spherePtr6->color(lightGreen);
    AddObject(spherePtr6);

    Sphere*	spherePtr7 = new Sphere(Point3D(35, 18, -35), 22); 
    spherePtr7->color(green);
    AddObject(spherePtr7);

    Sphere*	spherePtr8 = new Sphere(Point3D(-57, -17, -50), 15);  
    spherePtr8->color(brown);
    AddObject(spherePtr8);

    Sphere*	spherePtr9 = new Sphere(Point3D(-47, 16, -80), 23); 
    spherePtr9->color(lightGreen);
    AddObject(spherePtr9);
        
    Sphere*	spherePtr10 = new Sphere(Point3D(-15, -32, -60), 22); 
    spherePtr10->color(darkGreen);
    AddObject(spherePtr10);

    Sphere*	spherePtr11 = new Sphere(Point3D(-35, -37, -80), 22); 
    spherePtr11->color(darkYellow);
    AddObject(spherePtr11);

    Sphere*	spherePtr12 = new Sphere(Point3D(10, 43, -80), 22); 
    spherePtr12->color(darkYellow);
    AddObject(spherePtr12);
        
    Sphere*	spherePtr13 = new Sphere(Point3D(30, -7, -80), 10); 
    spherePtr13->color(darkYellow);
    AddObject(spherePtr13);
        
    Sphere*	spherePtr14 = new Sphere(Point3D(-40, 48, -110), 18); 
    spherePtr14->color(darkGreen);
    AddObject(spherePtr14);
        
    Sphere*	spherePtr15 = new Sphere(Point3D(-10, 53, -120), 18); 
    spherePtr15->color(brown);
    AddObject(spherePtr15);

    Sphere*	spherePtr16 = new Sphere(Point3D(-55, -52, -100), 10); 
    spherePtr16->color(lightPurple);
    AddObject(spherePtr16);

    Sphere*	spherePtr17 = new Sphere(Point3D(5, -52, -100), 15);
    spherePtr17->color(brown);
    AddObject(spherePtr17);

    Sphere*	spherePtr18 = new Sphere(Point3D(-20, -57, -120), 15); 
    spherePtr18->color(darkPurple);
    AddObject(spherePtr18);

    Sphere*	spherePtr19 = new Sphere(Point3D(55, -27, -100), 17); 
    spherePtr19->color(darkGreen);
    AddObject(spherePtr19);

    Sphere*	spherePtr20 = new Sphere(Point3D(50, -47, -120), 15); 
    spherePtr20->color(brown);
    AddObject(spherePtr20);
        
    Sphere*	spherePtr21 = new Sphere(Point3D(70, -42, -150), 10); 
    spherePtr21->color(lightPurple);
    AddObject(spherePtr21);

    Sphere*	spherePtr22 = new Sphere(Point3D(5, 73, -130), 12); 
    spherePtr22->color(lightPurple);
    AddObject(spherePtr22);

    Sphere*	spherePtr23 = new Sphere(Point3D(66, 21, -130), 13);
    spherePtr23->color(darkPurple);
    AddObject(spherePtr23);	
        
    Sphere*	spherePtr24 = new Sphere(Point3D(72, -12, -140), 12);
    spherePtr24->color(lightPurple);
    AddObject(spherePtr24);

    Sphere*	spherePtr25 = new Sphere(Point3D(64, 5, -160), 11);
    spherePtr25->color(green);
    AddObject(spherePtr25);
        
    Sphere*	spherePtr26 = new Sphere(Point3D(55, 38, -160), 12);
    spherePtr26->color(lightPurple);
    AddObject(spherePtr26);

    Sphere*	spherePtr27 = new Sphere(Point3D(-73, -2, -160), 12);
    spherePtr27->color(lightPurple);
    AddObject(spherePtr27);
        
    Sphere*	spherePtr28 = new Sphere(Point3D(30, -62, -140), 15); 
    spherePtr28->color(darkPurple);
    AddObject(spherePtr28);

    Sphere*	spherePtr29 = new Sphere(Point3D(25, 63, -140), 15); 
    spherePtr29->color(darkPurple);
    AddObject(spherePtr29);

    Sphere*	spherePtr30 = new Sphere(Point3D(-60, 46, -140), 15);  
    spherePtr30->color(darkPurple);
    AddObject(spherePtr30);

    Sphere*	spherePtr31 = new Sphere(Point3D(-30, 68, -130), 12); 
    spherePtr31->color(lightPurple);
    AddObject(spherePtr31);

    Sphere*	spherePtr32 = new Sphere(Point3D(58, 56, -180), 11);   
    spherePtr32->color(green);
    AddObject(spherePtr32);

    Sphere*	spherePtr33 = new Sphere(Point3D(-63, -39, -180), 11); 
    spherePtr33->color(green);
    AddObject(spherePtr33);

    Sphere*	spherePtr34 = new Sphere(Point3D(46, 68, -200), 10);
    spherePtr34->color(lightPurple);
    AddObject(spherePtr34);

    Sphere*	spherePtr35 = new Sphere(Point3D(-3, -72, -130), 12); 
    spherePtr35->color(lightPurple);
    AddObject(spherePtr35);
}

