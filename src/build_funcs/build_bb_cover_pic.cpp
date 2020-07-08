// This builds the cover image for Chapter 3: Bare Bones Ray Tracing

void World::Build(void) {
  int num_samples = 16;

  vp_.SetHRes(400);
  vp_.SetVRes(400);
  vp_.SetPixelSize(0.5);

  vp_.SetSampler(new MultiJittered(num_samples));
  vp_.SetGamma(1.0);

  Point3D cam_eye(0, 0, 100);
  Point3D cam_lookat(0, 0, 0);
  float cam_d = 10;
  Pinhole *ptr = new Pinhole(cam_eye, cam_lookat, cam_d);
  ptr->zoom_ = 20;
  camera_ptr_ = ptr;

  background_color_ = RGBColor(0.0);
  tracer_ptr_ = new MultipleObjects(this);  

  // colours
  RGBColor yellow(1, 1, 0);               // yellow
  RGBColor brown(0.71, 0.40, 0.16);       // brown
  RGBColor dark_green(0.0, 0.41, 0.41);   // dark_green
  RGBColor orange(1, 0.75, 0);            // orange
  RGBColor green(0, 0.6, 0.3);            // green
  RGBColor light_green(0.65, 1, 0.30);    // light green
  RGBColor dark_yellow(0.61, 0.61, 0);    // dark yellow
  RGBColor light_purple(0.65, 0.3, 1);    // light purple
  RGBColor dark_purple(0.5, 0, 1);        // dark purple

  // spheres
  Sphere*	sphere_ptr1 = new Sphere(Point3D(5, 3, 0), 30);
  sphere_ptr1->SetColor(yellow);
  AddObject(sphere_ptr1);

  Sphere*	sphere_ptr2 = new Sphere(Point3D(45, -7, -60), 20); 
  sphere_ptr2->SetColor(brown);
  AddObject(sphere_ptr2);
    
  Sphere*	sphere_ptr3 = new Sphere(Point3D(40, 43, -100), 17); 
  sphere_ptr3->SetColor(dark_green);
  AddObject(sphere_ptr3);

  Sphere*	sphere_ptr4 = new Sphere(Point3D(-20, 28, -15), 20); 
  sphere_ptr4->SetColor(orange);
  AddObject(sphere_ptr4);

  Sphere*	sphere_ptr5 = new Sphere(Point3D(-25, -7, -35), 27);
  sphere_ptr5->SetColor(green);
  AddObject(sphere_ptr5);

  Sphere*	sphere_ptr6 = new Sphere(Point3D(20, -27, -35), 25); 
  sphere_ptr6->SetColor(light_green);
  AddObject(sphere_ptr6);

  Sphere*	sphere_ptr7 = new Sphere(Point3D(35, 18, -35), 22); 
  sphere_ptr7->SetColor(green);
  AddObject(sphere_ptr7);

  Sphere*	sphere_ptr8 = new Sphere(Point3D(-57, -17, -50), 15);  
  sphere_ptr8->SetColor(brown);
  AddObject(sphere_ptr8);

  Sphere*	sphere_ptr9 = new Sphere(Point3D(-47, 16, -80), 23); 
  sphere_ptr9->SetColor(light_green);
  AddObject(sphere_ptr9);
    
  Sphere*	sphere_ptr10 = new Sphere(Point3D(-15, -32, -60), 22); 
  sphere_ptr10->SetColor(dark_green);
  AddObject(sphere_ptr10);

  Sphere*	sphere_ptr11 = new Sphere(Point3D(-35, -37, -80), 22); 
  sphere_ptr11->SetColor(dark_yellow);
  AddObject(sphere_ptr11);

  Sphere*	sphere_ptr12 = new Sphere(Point3D(10, 43, -80), 22); 
  sphere_ptr12->SetColor(dark_yellow);
  AddObject(sphere_ptr12);
      
  Sphere*	sphere_ptr13 = new Sphere(Point3D(30, -7, -80), 10); 
  sphere_ptr13->SetColor(dark_yellow);
  AddObject(sphere_ptr13);
    
  Sphere*	sphere_ptr14 = new Sphere(Point3D(-40, 48, -110), 18); 
  sphere_ptr14->SetColor(dark_green);
  AddObject(sphere_ptr14);
    
  Sphere*	sphere_ptr15 = new Sphere(Point3D(-10, 53, -120), 18); 
  sphere_ptr15->SetColor(brown);
  AddObject(sphere_ptr15);

  Sphere*	sphere_ptr16 = new Sphere(Point3D(-55, -52, -100), 10); 
  sphere_ptr16->SetColor(light_purple);
  AddObject(sphere_ptr16);

  Sphere*	sphere_ptr17 = new Sphere(Point3D(5, -52, -100), 15);
  sphere_ptr17->SetColor(brown);
  AddObject(sphere_ptr17);

  Sphere*	sphere_ptr18 = new Sphere(Point3D(-20, -57, -120), 15); 
  sphere_ptr18->SetColor(dark_purple);
  AddObject(sphere_ptr18);

  Sphere*	sphere_ptr19 = new Sphere(Point3D(55, -27, -100), 17); 
  sphere_ptr19->SetColor(dark_green);
  AddObject(sphere_ptr19);

  Sphere*	sphere_ptr20 = new Sphere(Point3D(50, -47, -120), 15); 
  sphere_ptr20->SetColor(brown);
  AddObject(sphere_ptr20);
    
  Sphere*	sphere_ptr21 = new Sphere(Point3D(70, -42, -150), 10); 
  sphere_ptr21->SetColor(light_purple);
  AddObject(sphere_ptr21);

  Sphere*	sphere_ptr22 = new Sphere(Point3D(5, 73, -130), 12); 
  sphere_ptr22->SetColor(light_purple);
  AddObject(sphere_ptr22);

  Sphere*	sphere_ptr23 = new Sphere(Point3D(66, 21, -130), 13);
  sphere_ptr23->SetColor(dark_purple);
  AddObject(sphere_ptr23);	
    
  Sphere*	sphere_ptr24 = new Sphere(Point3D(72, -12, -140), 12);
  sphere_ptr24->SetColor(light_purple);
  AddObject(sphere_ptr24);

  Sphere*	sphere_ptr25 = new Sphere(Point3D(64, 5, -160), 11);
  sphere_ptr25->SetColor(green);
  AddObject(sphere_ptr25);
    
  Sphere*	sphere_ptr26 = new Sphere(Point3D(55, 38, -160), 12);
  sphere_ptr26->SetColor(light_purple);
  AddObject(sphere_ptr26);

  Sphere*	sphere_ptr27 = new Sphere(Point3D(-73, -2, -160), 12);
  sphere_ptr27->SetColor(light_purple);
  AddObject(sphere_ptr27);
    
  Sphere*	sphere_ptr28 = new Sphere(Point3D(30, -62, -140), 15); 
  sphere_ptr28->SetColor(dark_purple);
  AddObject(sphere_ptr28);

  Sphere*	sphere_ptr29 = new Sphere(Point3D(25, 63, -140), 15); 
  sphere_ptr29->SetColor(dark_purple);
  AddObject(sphere_ptr29);

  Sphere*	sphere_ptr30 = new Sphere(Point3D(-60, 46, -140), 15);  
  sphere_ptr30->SetColor(dark_purple);
  AddObject(sphere_ptr30);

  Sphere*	sphere_ptr31 = new Sphere(Point3D(-30, 68, -130), 12); 
  sphere_ptr31->SetColor(light_purple);
  AddObject(sphere_ptr31);

  Sphere*	sphere_ptr32 = new Sphere(Point3D(58, 56, -180), 11);   
  sphere_ptr32->SetColor(green);
  AddObject(sphere_ptr32);

  Sphere*	sphere_ptr33 = new Sphere(Point3D(-63, -39, -180), 11); 
  sphere_ptr33->SetColor(green);
  AddObject(sphere_ptr33);

  Sphere*	sphere_ptr34 = new Sphere(Point3D(46, 68, -200), 10);
  sphere_ptr34->SetColor(light_purple);
  AddObject(sphere_ptr34);

  Sphere*	sphere_ptr35 = new Sphere(Point3D(-3, -72, -130), 12); 
  sphere_ptr35->SetColor(light_purple);
  AddObject(sphere_ptr35);
}

